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
check_log "cppcheck --enable=all --inconclusive --error-exitcode=1 -Iflight_lib -I . --suppress=missingIncludeSystem flight_lib *.c" "\(information\)"

print_header "RUN clang-tidy"
check_log "clang-tidy flight_lib/*.c *.c flight_lib/*.h -warnings-as-errors=* -extra-arg=-std=c99 -- -Iflight_lib" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint --extensions=c flight_lib/*.c *.c flight_lib/*.h" "Can't open for reading"

print_header "LINTING COMPLETED SUCCESSFULLY!"