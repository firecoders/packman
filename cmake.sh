#!/bin/bash

# if any command fails, bash will exit with a non-zero exit code
set -e

case $1 in
    "setup")
        cmake -H. -Bbuild
        ;;
    "debug")
        cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Debug
        ;;
    "clean")
        echo "removing build/ and packman executable"
        rm -rf build packman
        ;;
    "run")
        ./packman
        ;;
    *)
        make -C build $1
        ;;
esac

if [ $# -gt 1 ]
    then
        shift
        ./cmake.sh $*
fi
