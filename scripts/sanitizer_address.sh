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

print_header "RUN sanitizers"
check_log "g++ -Wall -g -pthread -fsanitize=address,undefined,leak -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error -lgtest -lgtest_main -lpthread -lgcov -Iflight_lib -Lbuild/flight_lib tests/test_flight.cpp" "undefined reference"

print_header "SANITIZERS SUCCESS"