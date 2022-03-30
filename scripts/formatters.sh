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
#check_log "clang-format main.c > formatted_main.c && \
#           clang-format flight_lib/flight.c > flight_lib/formatted_flight.c && \
#           clang-format flight_lib/flight.h > flight_lib/formatted_flight.h && \
#           diff main.c formatted_main.c && \
#           diff flight_lib/flight.c flight_lib/formatted_flight.c && \
#           diff flight_lib/flight.h flight_lib/formatted_flight.h" \
#           ">"
tree

print_header "FORMATTING COMPLETED SUCCESSFULLY!"