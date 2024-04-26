#!/bin/sh


find src -iname "*.[ch]" | xargs clang-tidy --config-file .clang-tidy
find tests -iname "*.[ch]" | xargs clang-tidy --config-file .clang-tidy
