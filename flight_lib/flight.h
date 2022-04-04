#ifndef _HW1_FLIGHT_LIB_FLIGHT_H_
#define _HW1_FLIGHT_LIB_FLIGHT_H_

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_INITIAL_LENGTH 6
#define ZERO 0

enum Errors {
  NO_ERROR = 0,
  FORMAT_ERROR,
  MEMORY_ALLOCATION_ERROR,
  PASSED_ARGUMENTS_ERROR,
  NOT_FOUND_ERROR
};

typedef struct {
  //  Flight code must contain from 3 to 6 symbols
  //  with mask: "XXD(DDD)", where XX – letters, every D – figure
  char *flight_code;
  //  Departure and arrival airports are described
  //  by their three-letters code
  char *departure_airport_code;
  char *arrival_airport_code;
  //  Flight duration in minutes
  unsigned flight_duration;
  //  Flight cost in US dollars
  float flight_cost;
} Flight;

int execute_program(FILE *, FILE *);
void display_notification(FILE *, int);
int grow_buffer(char **, size_t, size_t);
int get_string(FILE *, char **, size_t *, char);

#endif  // _HW1_FLIGHT_LIB_FLIGHT_H_
