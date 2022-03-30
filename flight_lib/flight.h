#ifndef FLIGHT_LIB_FLIGHT_H_
#define FLIGHT_LIB_FLIGHT_H_

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void display_notification(FILE *, int);
int grow_buffer(char **, size_t, size_t);
int get_string(FILE *, char **, size_t *, char);
int safe_string_input(FILE *, FILE *, char **, size_t *);
int safe_unsigned_convert(char *, size_t, unsigned *);
int safe_float_convert(char *, size_t, float *);
int safe_unsigned_input(FILE *, FILE *, unsigned *);
int safe_float_input(FILE *, FILE *, float *);
int allocate_flights_memory(Flight **, size_t);
int find_best_flights(char *, char *, Flight *, size_t, size_t *, size_t *);
void print_flight(FILE *, Flight *, size_t);
void free_flights_memory(Flight *, size_t);

#endif // FLIGHT_LIB_FLIGHT_H_
