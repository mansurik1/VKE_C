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

print_header "RUN cppcheck"
check_log "cppcheck --enable=all --inconclusive --error-exitcode=1 --suppress=missingIncludeSystem -Iflight_lib flight_lib tests main.c" "\(information\)"

print_header "RUN clang-tidy"
check_log "clang-tidy flight_lib/flight.c main.c -extra-arg=-std=c99 -warnings-as-errors=* -- -Iflight_lib" "Error (?:reading|while processing)"
check_log "clang-tidy tests/test_flight.cpp -warnings-as-errors=* -- -Iflight_lib" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint --extensions=c,cc,h flight_lib/flight.c flight_lib/flight.h tests/test_flight.cc main.c" "Can't open for reading"

print_header "LINTING COMPLETED SUCCESSFULLY!"