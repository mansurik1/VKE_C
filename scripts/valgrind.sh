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

print_header "RUN valgrind"
check_log "valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all build/tests/flight_test" "LEAK SUMMARY"
check_log "valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all build/HW1" "LEAK SUMMARY"

print_header "VALGRIND WORK COMPLETED SUCCESSFULLY!"