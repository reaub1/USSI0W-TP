#!/bin/bash

echo "test 1" > test1.txt

.././my_sh -c "cat test1.txt > test2.txt"

if [ "$(cat test1.txt)" = "$(cat test2.txt)" ]; then
    echo "test 1: OK"
else
    echo "test 1: KO"
fi
