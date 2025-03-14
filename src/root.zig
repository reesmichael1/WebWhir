const std = @import("std");
const testing = std.testing;

const ww_parser = @import("ww_parser");
const Tokenizer = ww_parser.Tokenizer;
const Parser = ww_parser.Parser;

pub fn run(html: []const u8) !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    const allocator = gpa.allocator();
    defer if (gpa.deinit() == .leak) {
        @panic("leaked memory!");
    };

    var tokenizer = Tokenizer.init(allocator);
    defer tokenizer.deinit();

    var parser = Parser.init(allocator);
    defer parser.deinit();

    tokenizer.pairParser(&parser);
    try tokenizer.addChunk(html);
    const tok = try tokenizer.run();

    std.debug.assert(tok.?.isDoctype());
}
