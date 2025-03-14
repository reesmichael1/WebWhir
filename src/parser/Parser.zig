const std = @import("std");
const Allocator = std.mem.Allocator;

const Self = @This();
const Tokenizer = @import("Tokenizer.zig");

pause: bool = false,
allocator: Allocator,
tokenizer: ?*Tokenizer,

pub fn init(allocator: Allocator) Self {
    return .{
        .allocator = allocator,
        .tokenizer = null,
    };
}

pub fn deinit(self: *Self) void {
    _ = self;
    return;
}

pub fn pairTokenizer(self: *Self, tokenizer: *Tokenizer) void {
    self.tokenizer = tokenizer;
}

test "external" {
    try std.testing.expect(true);
}
