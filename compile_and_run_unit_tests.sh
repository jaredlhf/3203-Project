#!/usr/bin/env bash



if [ $1 = "-a" ]
then
    if [ -z $2 ]
    then
        echo "Missing relative source file path from build directory"
        exit 1
    fi

    if [ -z $3 ]
    then
        echo "Missing relative query file path from build directory"
        exit 1
    fi

    if [ -z $4 ]
    then
        echo "Missing output file"
        exit 1
    fi
    cd Team25 && cd Code25 && cd build
    cmake .. && make -j4
    src/autotester/autotester $2 $3 $4
elif [ $1 = "-u" ]
then
    cd Team25 && cd Code25 && cd build
    cmake .. && make -j4
    src/unit_testing/unit_testing
else
    echo "invalid flag, exiting.."
    exit 1
fi




