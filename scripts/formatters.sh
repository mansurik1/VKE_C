#!/usr/bin/env bash

set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

print_header "RUN clang-format"

clang-format main.c --style=Google > formatted_main.c
check_log "diff main.c formatted_main.c" ">"

cd tests

clang-format test_flight.cc --style=Google > formatted_test_flight.cc
check_log "diff test_flight.cc formatted_test_flight.cc" ">"

cd ../flight_lib

clang-format flight.c --style=Google > formatted_flight.c
check_log "diff flight.c formatted_flight.c" ">"

clang-format flight.h --style=Google > formatted_flight.h
check_log "diff flight.h formatted_flight.h" ">"

print_header "FORMATTING COMPLETED SUCCESSFULLY!"