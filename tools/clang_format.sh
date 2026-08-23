#!/usr/bin/env bash
set -euo pipefail

cd "${BUILD_WORKSPACE_DIRECTORY}"

find apps myers-core myers-utils \
    \( -name '*.cpp' -o -name '*.h' \) -print0 |
    xargs -0 /usr/bin/clang-format -i --style=file
