#!/bin/bash

mkdir -p build;
cmake -B build/ -S .;
ln -s build/compile_commands.json .
