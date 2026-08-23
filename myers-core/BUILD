# gazelle:ignore
# gazelle:exclude src
# gazelle:exclude include

load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "myers-core",
    srcs = glob(["src/**/*.cpp"]),
    hdrs = glob(["include/**/*.h"]),
    includes = ["include"],
    visibility = ["//visibility:public"],
)
