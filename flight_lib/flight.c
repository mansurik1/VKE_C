#include "flight.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_notification(FILE *output_file, int error) {
  fflush(stdout);

  switch (error) {
    case FORMAT_ERROR:
      fprintf(output_file, "Entered string format is incorrect.\n");
      fprintf(output_file, "Please retype it -> ");
      break;
    case MEMORY_ALLOCATION_ERROR:
      fprintf(output_file,
              "\nError occurred while trying to allocate memory.\n");
      fprintf(output_file, "Please clear your RAM and run the program again.");
      break;
    default:
      fprintf(output_file, "The error has occurred.");
      break;
  }
}

int grow_buffer(char **buffer, size_t old_length, size_t new_length) {
  if (new_length <= old_length) {
    return MEMORY_ALLOCATION_ERROR;
  }
  // Allocating new buffer with check
  char *new_buffer = NULL;
  if ((new_buffer = (char *)malloc(sizeof(char) * new_length)) == NULL) {
    return MEMORY_ALLOCATION_ERROR;
  }

  if (old_length > 0) {
    // Copying data from the old buffer to the new one
    memcpy(new_buffer, *buffer, old_length * sizeof(char));
    // Freeing the old memory
    free(*buffer);
  }

  // Setting new pointer
  *buffer = new_buffer;

  return NO_ERROR;
}

int get_string(FILE *input_file, char **string, size_t *sending_length,
               char delimiter) {
  //  Initial allocation with check
  if (grow_buffer(string, ZERO, DEFAULT_INITIAL_LENGTH) ==
      MEMORY_ALLOCATION_ERROR) {
    return MEMORY_ALLOCATION_ERROR;
  }
  size_t buffer_length = DEFAULT_INITIAL_LENGTH;

  size_t string_length = 0;

  char current_char = (char)fgetc(input_file);
  while (current_char != delimiter) {
    (*string)[string_length] = current_char;
    ++string_length;

    if (string_length == buffer_length) {
      if (grow_buffer(string, buffer_length, buffer_length * 2) ==
          MEMORY_ALLOCATION_ERROR) {
        free(*string);
        return MEMORY_ALLOCATION_ERROR;
      }
      buffer_length *= 2;
    }

    current_char = (char)fgetc(input_file);
  }

  (*string)[string_length] = '\0';

  if (sending_length != NULL) {
    *sending_length = string_length;
  }

  return NO_ERROR;
}

int safe_string_input(FILE *input_file, char **string, size_t *sending_length) {
  if (input_file == NULL || string == NULL) {
    return PASSED_ARGUMENTS_ERROR;
  }

  if (get_string(input_file, string, sending_length, '\n') ==
      MEMORY_ALLOCATION_ERROR) {
    return MEMORY_ALLOCATION_ERROR;
  }

  return NO_ERROR;
}

int safe_unsigned_convert(char *string, size_t string_length, unsigned *num) {
  char *ending = NULL;
  long long ll_num = ZERO;
  errno = ZERO;

  ll_num = strtoll(string, &ending, 10);

  if ((size_t)(ending - string) != string_length || errno == ERANGE ||
      ll_num < 1 || ll_num > UINT_MAX) {
    return FORMAT_ERROR;
  }

  *num = (unsigned)ll_num;
  return NO_ERROR;
}

int safe_float_convert(char *string, size_t string_length, float *num) {
  char *ending = NULL;
  float f_num = ZERO;
  errno = ZERO;

  f_num = strtof(string, &ending);

  if ((size_t)(ending - string) != string_length || errno == ERANGE ||
      f_num <= 0.0f) {
    return FORMAT_ERROR;
  }

  *num = f_num;
  return NO_ERROR;
}

int safe_unsigned_input(FILE *input_file, unsigned *num) {
  *num = 0;

  char *string = NULL;
  size_t string_length = 0;

  int error = safe_string_input(input_file, &string, &string_length);
  if (error != NO_ERROR) {
    return error;
  }

  while (safe_unsigned_convert(string, string_length, num) == FORMAT_ERROR) {
    free(string);
    error = safe_string_input(input_file, &string, &string_length);
    if (error != NO_ERROR) {
      return error;
    }
  }

  free(string);
  return NO_ERROR;
}

int safe_float_input(FILE *input_file, float *num) {
  *num = 0;

  char *string = NULL;
  size_t string_length = 0;

  int error = safe_string_input(input_file, &string, &string_length);
  if (error != NO_ERROR) {
    return error;
  }

  while (safe_float_convert(string, string_length, num) == FORMAT_ERROR) {
    free(string);
    error = safe_string_input(input_file, &string, &string_length);
    if (error != NO_ERROR) {
      return error;
    }
  }

  free(string);
  return NO_ERROR;
}

int allocate_flights_memory(Flight **flights, size_t flights_length) {
  if ((*flights = (Flight *)malloc(sizeof(Flight) * flights_length)) == NULL) {
    return MEMORY_ALLOCATION_ERROR;
  }
  for (size_t i = 0; i < flights_length; ++i) {
    (*flights)[i].arrival_airport_code = NULL;
    (*flights)[i].departure_airport_code = NULL;
    (*flights)[i].flight_code = NULL;
  }

  return NO_ERROR;
}

int find_best_flights(char *dep_airport, char *arr_airport, Flight *flights,
                      size_t flights_length,
                      size_t *minimal_duration_flight_index,
                      size_t *minimal_cost_flight_index) {
  unsigned minimal_duration = 0;
  float minimal_cost = 0.0f;
  int matches = 0;

  for (size_t i = 0; i < flights_length; ++i) {
    if (strcmp(flights[i].departure_airport_code, dep_airport) == 0 &&
        strcmp(flights[i].arrival_airport_code, arr_airport) == 0) {
      if (matches == 0) {
        minimal_duration = flights[i].flight_duration;
        *minimal_duration_flight_index = i;
        minimal_cost = flights[i].flight_cost;
        *minimal_cost_flight_index = i;
      } else {
        if (flights[i].flight_duration < minimal_duration) {
          minimal_duration = flights[i].flight_duration;
          *minimal_duration_flight_index = i;
        }
        if (flights[i].flight_cost < minimal_cost) {
          minimal_cost = flights[i].flight_cost;
          *minimal_cost_flight_index = i;
        }
      }
      ++matches;
    }
  }

  if (matches > 0) {
    return NO_ERROR;
  } else {
    return NOT_FOUND_ERROR;
  }
}

void print_flight(FILE *output_file, Flight *flights, size_t index) {
  fprintf(output_file, "Flight code: %s\n", flights[index].flight_code);
  fprintf(output_file, "Departure airport code: %s\n",
          flights[index].departure_airport_code);
  fprintf(output_file, "Arrival airport code: %s\n",
          flights[index].arrival_airport_code);
  fprintf(output_file, "Flight duration: %u minutes\n",
          flights[index].flight_duration);
  fprintf(output_file, "Flight cost: $%f\n", flights[index].flight_cost);
}

void free_flights_memory(Flight *flights, size_t flights_length) {
  for (size_t i = 0; i < flights_length; ++i) {
    free(flights[i].flight_code);
    free(flights[i].departure_airport_code);
    free(flights[i].arrival_airport_code);
  }
  free(flights);
}

int execute_program(FILE *input_file, FILE *output_file) {
  fprintf(output_file, "Please enter the number of flights -> ");
  unsigned number_of_flights = 0;
  int error = ZERO;

  if ((error = safe_unsigned_input(input_file, &number_of_flights)) !=
      NO_ERROR) {
    return error;
  }

  Flight *flights = NULL;
  if ((error = allocate_flights_memory(&flights, number_of_flights)) !=
      NO_ERROR) {
    return error;
  }
  // bad code
  //    char* bad = (char*)malloc(5);
  //    bad[128] = 'f';
  // bad code

  for (size_t i = 0; i < number_of_flights; ++i) {
    fprintf(output_file,
            "\nPlease enter the flight code of the flight number %zu -> ",
            i + 1);
    if ((error = safe_string_input(input_file, &(flights[i].flight_code),
                                   NULL)) != NO_ERROR) {
      free_flights_memory(flights, number_of_flights);
      return error;
    }
    fprintf(
        output_file,
        "Please enter the departure airport code of the flight number %zu -> ",
        i + 1);
    if ((error = safe_string_input(
             input_file, &(flights[i].departure_airport_code), NULL)) !=
        NO_ERROR) {
      free_flights_memory(flights, number_of_flights);
      return error;
    }
    fprintf(
        output_file,
        "Please enter the arrival airport code of the flight number %zu -> ",
        i + 1);
    if ((error = safe_string_input(input_file,
                                   &(flights[i].arrival_airport_code), NULL)) !=
        NO_ERROR) {
      free_flights_memory(flights, number_of_flights);
      return error;
    }
    fprintf(
        output_file,
        "Please enter the duration of the flight number %zu (in minutes) -> ",
        i + 1);
    if ((error = safe_unsigned_input(
             input_file, &(flights[i].flight_duration))) != NO_ERROR) {
      free_flights_memory(flights, number_of_flights);
      return error;
    }
    fprintf(
        output_file,
        "Please enter the flight_cost of the flight number %zu (in USD) -> ",
        i + 1);
    if ((error = safe_float_input(input_file, &(flights[i].flight_cost))) !=
        NO_ERROR) {
      free_flights_memory(flights, number_of_flights);
      return error;
    }
  }

  fprintf(output_file,
          "\nNow the program will find the least time-consuming air ticket and "
          "most advantageous air ticket\naccording to the codes of the "
          "airports of departure and arrival you "
          "will enter below.\n");

  char *dep_airport = NULL;
  char *arr_airport = NULL;

  fprintf(output_file, "\nPlease enter the departure airport code -> ");
  if ((error = safe_string_input(input_file, &dep_airport, NULL)) != NO_ERROR) {
    free_flights_memory(flights, number_of_flights);
    return error;
  }
  fprintf(output_file, "Please enter the arrival airport code -> ");
  if ((error = safe_string_input(input_file, &arr_airport, NULL)) != NO_ERROR) {
    free(dep_airport);
    free_flights_memory(flights, number_of_flights);
    return error;
  }

  size_t minimal_duration_flight_index = 0;
  size_t minimal_cost_flight_index = 0;
  if (find_best_flights(dep_airport, arr_airport, flights, number_of_flights,
                        &minimal_duration_flight_index,
                        &minimal_cost_flight_index) == NOT_FOUND_ERROR) {
    fprintf(output_file, "\nPair of specified airports has not been found.");
    free(dep_airport);
    free(arr_airport);
    free_flights_memory(flights, number_of_flights);
    return NOT_FOUND_ERROR;
  }

  fprintf(output_file, "\nLeast time-consuming air ticket:\n");
  print_flight(output_file, flights, minimal_duration_flight_index);

  fprintf(output_file, "\nMost advantageous air ticket:\n");
  print_flight(output_file, flights, minimal_cost_flight_index);
  free(dep_airport);
  free(arr_airport);
  free_flights_memory(flights, number_of_flights);

  return NO_ERROR;
}
