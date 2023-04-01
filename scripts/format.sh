#!/bin/sh

find src -iname "*.c" -o -iname "*.h" | xargs clang-format -i
