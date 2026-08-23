# gazelle:build_file_name BUILD,BUILD.bazel

load("@buildifier_prebuilt//:rules.bzl", "buildifier")
load("@gazelle//:def.bzl", "gazelle", "gazelle_binary")
load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")
load("@rules_multirun//:defs.bzl", "multirun")
load("@rules_shell//shell:sh_binary.bzl", "sh_binary")

gazelle_binary(
    name = "gazelle_cc",
    languages = [
        "@gazelle//language/proto",
        "@gazelle_cc//language/cc",
    ],
)

gazelle(
    name = "gazelle_internal",
    gazelle = ":gazelle_cc",
)

refresh_compile_commands(
    name = "refresh_compile_commands",
    targets = {"//...": ""},
)

buildifier(
    name = "buildifier",
    lint_mode = "fix",
)

multirun(
    name = "gazelle",
    commands = [
        ":gazelle_internal",
        ":refresh_compile_commands",
        ":buildifier",
        ":clang_format",
    ],
    jobs = 0,
)

sh_binary(
    name = "clang_format",
    srcs = ["tools/clang_format.sh"],
)
