#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"

int main(void) {
    printf("Please enter the number of flights -> ");
    unsigned number_of_flights = 0;
    int error = ZERO;

    if ((error = safe_unsigned_input(stdin, stdout, &number_of_flights)) != NO_ERROR) {
        return error;
    }

    Flight *flights = NULL;
    if ((error = allocate_flights_memory(&flights, number_of_flights)) != NO_ERROR) {
        return error;
    }

    for (size_t i = 0; i < number_of_flights; ++i) {
        printf("\nPlease enter the flight code of the flight number %zu -> ", i + 1);
        if ((error = safe_string_input(stdin, stdout, &(flights[i].flight_code), NULL)) != NO_ERROR) {
            free_flights_memory(flights, number_of_flights);
            return error;
        }
        printf("Please enter the departure airport code of the flight number %zu -> ", i + 1);
        if ((error = safe_string_input(stdin, stdout, &(flights[i].departure_airport_code), NULL)) != NO_ERROR) {
            free_flights_memory(flights, number_of_flights);
            return error;
        }
        printf("Please enter the arrival airport code of the flight number %zu -> ", i + 1);
        if ((error = safe_string_input(stdin, stdout, &(flights[i].arrival_airport_code), NULL)) != NO_ERROR) {
            free_flights_memory(flights, number_of_flights);
            return error;
        }
        printf("Please enter the duration of the flight number %zu (in minutes) -> ", i + 1);
        if ((error = safe_unsigned_input(stdin, stdout, &(flights[i].flight_duration))) != NO_ERROR) {
            free_flights_memory(flights, number_of_flights);
            return error;
        }
        printf("Please enter the flight_cost of the flight number %zu (in USD) -> ", i + 1);
        if ((error = safe_float_input(stdin, stdout, &(flights[i].flight_cost))) != NO_ERROR) {
            free_flights_memory(flights, number_of_flights);
            return error;
        }
    }

    printf("\nNow the program will find the least time-consuming air ticket and most advantageous air ticket\n");
    printf("according to the codes of the airports of departure and arrival you will enter below.\n");

    char* dep_airport = NULL;
    char* arr_airport = NULL;

    printf("\nPlease enter the departure airport code -> ");
    if ((error = safe_string_input(stdin, stdout, &dep_airport, NULL)) != NO_ERROR) {
        free_flights_memory(flights, number_of_flights);
        return error;
    }
    printf("Please enter the arrival airport code -> ");
    if ((error = safe_string_input(stdin, stdout, &arr_airport, NULL)) != NO_ERROR) {
        free(dep_airport);
        free_flights_memory(flights, number_of_flights);
        return error;
    }

    size_t minimal_duration_flight_index = 0;
    size_t minimal_cost_flight_index = 0;
    if (find_best_flights(dep_airport, arr_airport, flights, number_of_flights, &minimal_duration_flight_index,
                          &minimal_cost_flight_index) == NOT_FOUND_ERROR) {
        printf("\nPair of specified airports has not been found.");
        
        free(dep_airport);
        free(arr_airport);
        free_flights_memory(flights, number_of_flights);
        return NOT_FOUND_ERROR;
    }

    printf("\nLeast time-consuming air ticket:\n");
    print_flight(stdout, flights, minimal_duration_flight_index);

    printf("\nMost advantageous air ticket:\n");
    print_flight(stdout, flights, minimal_cost_flight_index);
    
    free(dep_airport);
    free(arr_airport);
    free_flights_memory(flights, number_of_flights);

    return NO_ERROR
}
