#include <gtest/gtest.h>

extern "C" {
#include "flight.h"
}

TEST(Notification, FORMAT_ERROR) {
    char right_output[] = "Entered string format is incorrect.\nPlease retype it -> ";

    char test_output[sizeof(right_output)];
    FILE* output_file = fmemopen(test_output, sizeof(right_output), "w");

    display_notification(output_file, FORMAT_ERROR);
    fclose(output_file);

    EXPECT_EQ(strcmp(test_output, right_output), 0);
}

TEST(Notification, MEMORY_ALLOCATION_ERROR) {
    char right_output[] = "\nError occurred while trying to allocate memory.\nPlease clear your RAM and run the program again.";

    char test_output[sizeof(right_output)];
    FILE* output_file = fmemopen(test_output, sizeof(right_output), "w");

    display_notification(output_file, MEMORY_ALLOCATION_ERROR);
    fclose(output_file);

//    char* a = (char*)malloc(5);

    EXPECT_EQ(strcmp(test_output, right_output), 0);
}

TEST(Whole_program, 1) {
    char right_output[] = "Please enter the number of flights -> \nPlease enter the flight code of the flight number 1 -> Please enter the departure airport code of the flight number 1 -> Please enter the arrival airport code of the flight number 1 -> Please enter the duration of the flight number 1 (in minutes) -> Please enter the flight_cost of the flight number 1 (in USD) -> \nPlease enter the flight code of the flight number 2 -> Please enter the departure airport code of the flight number 2 -> Please enter the arrival airport code of the flight number 2 -> Please enter the duration of the flight number 2 (in minutes) -> Please enter the flight_cost of the flight number 2 (in USD) -> \nNow the program will find the least time-consuming air ticket and most advantageous air ticket\naccording to the codes of the airports of departure and arrival you will enter below.\n\nPlease enter the departure airport code -> Please enter the arrival airport code -> \nLeast time-consuming air ticket:\nFlight code: ABC13\nDeparture airport code: SVO\nArrival airport code: VKO\nFlight duration: 75 minutes\nFlight cost: $234.500000\n\nMost advantageous air ticket:\nFlight code: CAB14\nDeparture airport code: SVO\nArrival airport code: VKO\nFlight duration: 95 minutes\nFlight cost: $113.454002\n";
    char input[] = "2\nABC13\nSVO\nVKO\n75\n234.5\nCAB14\nSVO\nVKO\n95\n113.454\nSVO\nVKO\n";

    char test_output[sizeof(right_output)];
    FILE* output_file = fmemopen(test_output, sizeof(right_output), "w");
    FILE* input_file = fmemopen(input, sizeof(input), "r");

    execute_program(input_file, output_file);

    fclose(input_file);
    fclose(output_file);

    EXPECT_EQ(strcmp(test_output, right_output), 0);
}