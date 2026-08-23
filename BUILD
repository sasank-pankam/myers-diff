# gazelle:build_file_name BUILD,BUILD.bazel

load("@gazelle//:def.bzl", "gazelle", "gazelle_binary")

gazelle_binary(
    name = "gazelle_cc",
    languages = [
        "@gazelle//language/proto",
        "@gazelle_cc//language/cc",
    ],
)

gazelle(
    name = "gazelle",
    gazelle = ":gazelle_cc",
)

load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

refresh_compile_commands(
    name = "refresh_compile_commands",
    targets = {"//...": ""},
)
