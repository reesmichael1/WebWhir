const std = @import("std");

const ww = @import("webwhir");

pub fn main() !void {
    try ww.run("<!DOCTYPE html>");
}
