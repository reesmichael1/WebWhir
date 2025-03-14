const std = @import("std");
const Allocator = std.mem.Allocator;
const StrList = std.ArrayList(u8);

const TokenError = error{
    name_in_nondoctype,
    empty_name_in_append,
    quirks_in_nondoctype,
};

pub const Doctype = struct {
    name: ?StrList = null,
    public_id: ?StrList = null,
    system_id: ?StrList = null,
    force_quirks: bool = false,
    allocator: Allocator,
};

pub const Tag = struct {
    name: []const u8,
    attributes: std.StringHashMap([]const u8),
    self_closing: bool = false,
};

pub const Comment = struct {
    content: []const u8,
    allocator: Allocator,
};

pub const Char = struct {
    content: u21,
};

pub const Token = union(enum) {
    doctype: Doctype,
    start: Tag,
    end: Tag,
    comment: Comment,
    char: Char,
    eof,

    const Self = @This();

    pub fn newStart(allocator: Allocator) Self {
        return Self{ .start = .{
            .name = "",
            .attributes = std.StringHashMap([]const u8).init(allocator),
        } };
    }

    pub fn newComment(allocator: Allocator) Self {
        return Self{ .comment = .{ .content = "", .allocator = allocator } };
    }

    pub fn newEof() Self {
        return .eof;
    }

    pub fn newDoctype(allocator: Allocator) Self {
        return Self{ .doctype = .{ .allocator = allocator } };
    }

    pub fn newDoctypeQuirks(allocator: Allocator) Self {
        return Self{ .doctype = .{ .allocator = allocator, .force_quirks = true } };
    }

    pub fn newDoctypeName(allocator: Allocator, name: []const u8) !Self {
        var namel = StrList.init(allocator);
        try namel.appendSlice(name);
        return Self{ .doctype = .{ .allocator = allocator, .name = namel } };
    }

    pub fn appendCodepointToName(self: *Self, char: u21) !void {
        switch (self.*) {
            Token.doctype => |*tok| {
                var buf: [4]u8 = undefined;
                const written = try std.unicode.utf8Encode(char, &buf);
                if (tok.name == null) {
                    tok.name = StrList.init(tok.allocator);
                }

                try tok.name.?.appendSlice(buf[0..written]);
            },
            else => return TokenError.name_in_nondoctype,
        }
    }

    pub fn appendToName(self: *Self, name: []const u8) !void {
        switch (self.*) {
            Token.doctype => |*tok| {
                if (tok.name == null) {
                    @branchHint(.cold);
                    return TokenError.empty_name_in_append;
                }

                try tok.name.?.appendSlice(name);
            },
            else => return TokenError.name_in_nondoctype,
        }
    }

    pub fn setQuirks(self: *Self) !void {
        switch (self.*) {
            Token.doctype => |*tok| tok.force_quirks = true,
            else => return TokenError.quirks_in_nondoctype,
        }
    }

    pub fn isDoctype(self: Self) bool {
        return switch (self) {
            Token.doctype => true,
            else => false,
        };
    }

    pub fn deinit(self: *Self) void {
        switch (self.*) {
            Token.start, Token.end => |*tok| tok.attributes.deinit(),
            Token.comment => |*tok| tok.allocator.free(tok.content),
            Token.doctype => |*tok| {
                if (tok.name) |name| name.deinit();
                if (tok.public_id) |id| id.deinit();
                if (tok.system_id) |id| id.deinit();
            },
            else => {},
        }
    }
};
