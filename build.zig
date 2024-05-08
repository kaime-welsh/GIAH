const std = @import("std");
const raylibSDK = @import("third-party/raylib/src/build.zig");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});
    const raylib = try raylibSDK.addRaylib(b, target, optimize, .{ .raygui = true });

    const exe = b.addExecutable(.{
        .name = "giah",
        .target = target,
        .optimize = optimize,
    });

    exe.addIncludePath(b.path("include"));
    exe.addIncludePath(b.path("third-party/raylib/src"));

    // Add C source files
    const flags = .{"-std=c++20"};
    exe.addCSourceFile(.{ .file = b.path("src/Main.cpp"), .flags = &flags });
    exe.addCSourceFile(.{ .file = b.path("src/TileMap.cpp"), .flags = &flags });
    exe.addCSourceFile(.{ .file = b.path("src/Scenes/GameScene.cpp"), .flags = &flags });
    exe.addCSourceFile(.{ .file = b.path("src/Entities/Player.cpp"), .flags = &flags });

    // Link Libraries
    exe.linkLibC();
    exe.linkSystemLibrary("c++");
    exe.linkLibrary(raylib);

    b.installArtifact(exe);

    const install = b.getInstallStep();
    const install_data = b.addInstallDirectory(.{ .source_dir = b.path("res"), .install_dir = .{ .prefix = {} }, .install_subdir = "res" });
    install.dependOn(&install_data.step);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
