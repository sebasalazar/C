#!/bin/bash

CARPETA="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd ${CARPETA}
make clean || exit 1
make || exit 1

./dist/integral "x**1" 1 10
./dist/integral "4x**2 + 1" 1 10
./dist/integral "x**3 + 25x**1"  1 10
./dist/integral "x**5 + 3" 1 10
./dist/integral "x**2 + 4x**1" 1 10
./dist/integral "13x**13 + 7x**7 + 5x**5 + 3x**3 +1" 1 10

