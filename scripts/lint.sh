#!/bin/sh


find src -iname "*.[ch]" | xargs clang-tidy --config-file .clang-tidy
