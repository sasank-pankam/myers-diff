# gazelle:ignore

load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@rules_multirun//:defs.bzl", "command")

cc_binary(
    name = "myers-diff",
    srcs = ["main.cpp"],
    deps = [
        "//myers-core",
        "//myers-utils",
    ],
)


command(
        name = "run_vector",
        command = ":myers-diff",
        arguments = [
                "1",
        ],
)


command(
        name = "run_files",
        command = ":myers-diff",
        arguments = [
                "0",
        ],
)
