const std = @import("std");
const Allocator = std.mem.Allocator;
const Utf8Iterator = std.unicode.Utf8Iterator;

const Self = @This();
const Token = @import("tokens.zig").Token;
const Element = @import("ww_dom").Element;
const Parser = @import("Parser.zig");

const State = enum {
    data,
    tag_open,
    markup_declaration_open,
    end_tag_open,
    comment_start,
    char_ref,
    doctype,
    bogus_comment,
    before_doctype_name,
    doctype_name,
    after_doctype_name,
};

const ParseError = enum {
    non_void_html_element_start_tag_with_trailing_solidus,
    end_tag_with_attributes,
    end_tag_with_trailing_solidus,
    unexpected_null,
    eof_before_tag_name,
    unexpected_question_mark_instead_of_tag_name,
    invalid_first_char_of_tag_name,
    incorrectly_opened_comment,
    missing_whitespace_before_doctype_name,
    eof_in_doctype,
    missing_doctype_name,
};

const TokenizerError = error{
    no_parser,
    unexpected_eof,
};

state: State = .data,
allocator: Allocator,
tokens: std.ArrayList(Token),
return_state: ?State = null,
open_stack: std.ArrayList(Element),
temp_buf: std.ArrayList(u8),
pointer: usize = 0,
parser: ?*Parser = null,
errors: std.ArrayList(ParseError),
should_reconsume: bool = false,
token: ?Token = null,
iter: Utf8Iterator,
last: ?u21 = null,

pub fn init(allocator: Allocator) Self {
    return Self{
        .allocator = allocator,
        .tokens = std.ArrayList(Token).init(allocator),
        .open_stack = std.ArrayList(Element).init(allocator),
        .temp_buf = std.ArrayList(u8).init(allocator),
        .errors = std.ArrayList(ParseError).init(allocator),
        .iter = .{
            .bytes = &.{},
            .i = 0,
        },
    };
}

pub fn deinit(self: *Self) void {
    self.tokens.deinit();
    self.open_stack.deinit();
    self.temp_buf.deinit();
    self.errors.deinit();
    self.allocator.free(self.iter.bytes);

    if (self.token) |*tok| {
        tok.deinit();
    }
}

pub fn pairParser(self: *Self, parser: *Parser) void {
    parser.pairTokenizer(self);
    self.parser = parser;
}

pub fn addChunk(self: *Self, chunk: []const u8) !void {
    self.iter.bytes = try std.mem.concat(self.allocator, u8, &[_][]const u8{ self.iter.bytes, chunk });
}

pub fn run(self: *Self) !?Token {
    if (self.parser) |parser| {
        if (parser.pause) {
            return null;
        }

        return try self.step();
    } else {
        return TokenizerError.no_parser;
    }
}

fn dataState(self: *Self) !bool {
    if (self.consumeNext()) |char| {
        switch (char) {
            '&' => {
                self.return_state = .data;
                self.state = .char_ref;
            },
            '<' => self.state = .tag_open,
            0 => {
                try self.parseError(.unexpected_null);
                try self.emitCharToken(char);
                return true;
            },
            else => {
                try self.emitCharToken(char);
                return true;
            },
        }
    } else {
        try self.emitEof();
        return true;
    }

    return false;
}

fn tagOpen(self: *Self) !bool {
    if (self.consumeNext()) |char| {
        switch (char) {
            '!' => self.state = .markup_declaration_open,
            '/' => self.state = .end_tag_open,
            '?' => {
                try self.parseError(.unexpected_question_mark_instead_of_tag_name);
            },
            'A'...'z' => {
                self.token = Token.newStart(self.allocator);
            },
            0 => {
                try self.parseError(.unexpected_null);
                try self.emitCharToken(char);
                return true;
            },
            else => {
                try self.parseError(.invalid_first_char_of_tag_name);
                self.should_reconsume = true;
                try self.emitCharToken('<');
                return true;
            },
        }
    } else {
        try self.parseError(.eof_before_tag_name);
        try self.emitEof();
        return true;
    }

    return false;
}

fn markupDeclOpen(self: *Self) !bool {
    if (std.mem.eql(u8, self.iter.peek(2), "--")) {
        self.state = .comment_start;
        self.token = Token.newComment(self.allocator);
        _ = self.iter.nextCodepoint();
        _ = self.iter.nextCodepoint();
    } else if (std.ascii.eqlIgnoreCase("DOCTYPE", self.iter.peek(7))) {
        self.state = .doctype;
        try self.consumeNextCount(7);
    } else if (std.ascii.eqlIgnoreCase("[CDATA[", self.iter.peek(7))) {
        // TODO once we have nodes and a parser
        unreachable;
    } else {
        try self.parseError(.incorrectly_opened_comment);
        self.state = .bogus_comment;
        self.token = Token.newComment(self.allocator);
    }

    return false;
}

fn doctype(self: *Self) !bool {
    if (self.consumeNext()) |char| {
        switch (char) {
            '\t', ' ', 0x0A, 0x0C => self.state = .before_doctype_name,
            '>' => {
                self.should_reconsume = true;
                self.state = .before_doctype_name;
            },
            else => {
                try self.parseError(.missing_whitespace_before_doctype_name);
                self.should_reconsume = true;
                self.state = .before_doctype_name;
            },
        }
    } else {
        try self.parseError(.eof_in_doctype);
        try self.emitToken(Token.newDoctypeQuirks(self.allocator));
        try self.emitEof();
        return true;
    }

    return false;
}

fn beforeDoctypeName(self: *Self) !bool {
    if (self.consumeNext()) |char| {
        switch (char) {
            '\t', ' ', 0x0a, 0x0c => {},
            0 => {
                try self.parseError(.unexpected_null);
                self.token = try Token.newDoctypeName(self.allocator, "\u{FFFD}");
                self.state = .doctype_name;
            },
            '>' => {
                try self.parseError(.missing_doctype_name);
                try self.emitToken(Token.newDoctypeQuirks(self.allocator));
                return true;
            },
            else => {
                var buf: [4]u8 = undefined;
                const written = try std.unicode.utf8Encode(char, &buf);
                const name = buf[0..written];
                self.token = try Token.newDoctypeName(self.allocator, name);
                self.state = .doctype_name;
            },
        }
    }

    return false;
}

fn doctypeName(self: *Self) !bool {
    if (self.consumeNext()) |char| {
        switch (char) {
            ' ', '\t', '\n', 0x0c => self.state = .after_doctype_name,
            '>' => {
                self.state = .data;
                try self.emitToken(self.token.?);
                return true;
            },
            0 => {
                try self.parseError(.unexpected_null);
                try self.token.?.appendCodepointToName(std.unicode.replacement_character);
            },
            else => {
                var buf: [4]u8 = undefined;
                const written = try std.unicode.utf8Encode(char, &buf);
                const str = buf[0..written];
                if (str.len == 1 and std.ascii.isUpper(str[0])) {
                    try self.token.?.appendCodepointToName(std.ascii.toLower(str[0]));
                } else {
                    try self.token.?.appendToName(str);
                }
            },
        }
    } else {
        try self.parseError(.eof_in_doctype);
        try self.token.?.setQuirks();
        try self.emitToken(self.token.?);
        try self.emitEof();
        return true;
    }

    return false;
}

fn parseError(self: *Self, err: ParseError) !void {
    try self.errors.append(err);
}

fn consumeNext(self: *Self) ?u21 {
    if (self.should_reconsume) {
        self.should_reconsume = false;
        return self.last;
    }

    const next = self.iter.nextCodepoint();
    self.last = next;
    return next;
}

fn consumeNextCount(self: *Self, count: usize) !void {
    var i: usize = 0;
    while (i < count) : (i += 1) {
        if (self.consumeNext() == null) {
            // This method should only be called when we've verified that the next
            // several characters match some string, so this branch should never hit.
            @branchHint(.cold);
            return TokenizerError.unexpected_eof;
        }
    }
}

fn step(self: *Self) !?Token {
    if (self.tokens.items.len > 0) {
        return self.tokens.pop();
    }

    while (true) {
        const emitted = switch (self.state) {
            .data => try self.dataState(),
            .tag_open => try self.tagOpen(),
            .markup_declaration_open => try self.markupDeclOpen(),
            .doctype => try self.doctype(),
            .before_doctype_name => try self.beforeDoctypeName(),
            .doctype_name => try self.doctypeName(),
            else => {
                const msg = std.fmt.allocPrint(self.allocator, "need to add support for {}", .{self.state}) catch unreachable;
                @panic(msg);
            },
        };
        if (emitted) {
            return self.tokens.pop();
        }
    }

    return null;
}

fn emitToken(self: *Self, token: Token) !void {
    try self.tokens.append(token);
}

fn emitCharToken(self: *Self, codepoint: u21) !void {
    const tok = Token{
        .char = .{ .content = codepoint },
    };
    try self.emitToken(tok);
}

fn emitEof(self: *Self) !void {
    const tok = Token.newEof();
    try self.emitToken(tok);
}
