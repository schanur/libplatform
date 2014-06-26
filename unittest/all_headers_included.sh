#! /bin/bash

if [ -f src/all.h ]; then
    for HEADER in src/*.h; do    
        if [ $(basename ${HEADER}) == "all.h" ]; then
            continue
        fi
        if [ ! $(grep $(basename ${HEADER}) src/all.h) ]; then
            echo ${HEADER} is not included in all.h
            exit 1
        fi
    done
    exit 0
fi
exit 1
