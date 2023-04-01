#!/bin/sh


find . -iname "*.[ch]" | xargs clang-tidy --config-file .clang-tidy
