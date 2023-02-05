#!/usr/bin/env bash

cd .. && cd Code25 && cd build
cmake .. && make -j4
src/unit_testing/unit_testing