#include <gtest/gtest.h>

#include <string>

extern "C" {
#include "flight.h"
}

TEST(Notification, FORMAT_ERROR) {
  char right_output[] =
      "Entered string format is incorrect.\nPlease retype it -> ";

  char test_output[sizeof(right_output)];
  FILE* output_file = fmemopen(test_output, sizeof(right_output), "w");

  display_notification(output_file, FORMAT_ERROR);
  fclose(output_file);

  ASSERT_EQ(strcmp(test_output, right_output), 0)
      << "Program's output is incorrect";
}

TEST(Notification, MEMORY_ALLOCATION_ERROR) {
  char right_output[] =
      "\nError occurred while trying to allocate memory.\nPlease clear your "
      "RAM and run the program again.";

  char test_output[sizeof(right_output)];
  FILE* output_file = fmemopen(test_output, sizeof(right_output), "w");

  display_notification(output_file, MEMORY_ALLOCATION_ERROR);
  fclose(output_file);

  ASSERT_EQ(strcmp(test_output, right_output), 0)
      << "Program's output is incorrect";
}

TEST(Notification, OTHER_ERROR) {
  const int SOME_OTHER_ERROR = 5;

  char right_output[] = "The error has occurred.";

  char test_output[sizeof(right_output)];
  FILE* output_file = fmemopen(test_output, sizeof(right_output), "w");

  display_notification(output_file, SOME_OTHER_ERROR);
  fclose(output_file);

  ASSERT_EQ(strcmp(test_output, right_output), 0)
      << "Program's output is incorrect";
}

TEST(Buffer_grow, Length_check) {
  const int OLD_LENGTH = 5;
  const int NEW_LENGTH = 3;

  char* buffer = NULL;
  if ((buffer = (char*)malloc(sizeof(char) * OLD_LENGTH)) == NULL) {
    FAIL() << "Memory allocation error";
  }

  EXPECT_EQ(grow_buffer(&buffer, OLD_LENGTH, NEW_LENGTH),
            MEMORY_ALLOCATION_ERROR)
      << "Length check doesn't work";
  free(buffer);
}

TEST(Buffer_grow, Copy_check) {
  const int OLD_LENGTH = 3;
  const int NEW_LENGTH = 5;

  char* buffer = NULL;
  if ((buffer = (char*)malloc(sizeof(char) * OLD_LENGTH)) == NULL) {
    FAIL() << "Memory allocation error";
  }

  for (size_t i = 0; i < OLD_LENGTH; ++i) {
    buffer[i] = (char)(i + '1');
  }

  EXPECT_EQ(grow_buffer(&buffer, OLD_LENGTH, NEW_LENGTH), NO_ERROR)
      << "Memory allocation error";

  bool failure_flag = false;
  for (size_t i = 0; i < OLD_LENGTH; ++i) {
    if (buffer[i] != (char)(i + '1')) {
      failure_flag = true;
      break;
    }
  }

  if (failure_flag) {
    ADD_FAILURE() << "Old data is not correct";
  }

  free(buffer);
}

TEST(Get_string, Without_reallocation) {
  char input_string[] = "123\n";
  char right_string[] = "123";
  FILE* input_file = fmemopen(input_string, sizeof(input_string), "r");

  char* test_output = NULL;
  get_string(input_file, &test_output, NULL, '\n');

  EXPECT_EQ(strcmp(test_output, right_string), 0);
  free(test_output);
}

TEST(Whole_program, two_flights) {
  char* right_output = new char[1253];
  memcpy(
      right_output,
      "Please enter the number of flights -> \nPlease enter the flight code of "
      "the flight number 1 -> Please enter the departure airport code of the "
      "flight number 1 -> Please enter the arrival airport code of the flight "
      "number 1 -> Please enter the duration of the flight number 1 (in "
      "minutes) -> Please enter the flight_cost of the flight number 1 (in "
      "USD) -> \nPlease enter the flight code of the flight number 2 -> Please "
      "enter the departure airport code of the flight number 2 -> Please enter "
      "the arrival airport code of the flight number 2 -> Please enter the "
      "duration of the flight number 2 (in minutes) -> Please enter the "
      "flight_cost of the flight number 2 (in USD) -> \nNow the program will "
      "find the least time-consuming air ticket and most advantageous air "
      "ticket\naccording to the codes of the airports of departure and arrival "
      "you will enter below.\n\nPlease enter the departure airport code -> "
      "Please enter the arrival airport code -> \nLeast time-consuming air "
      "ticket:\nFlight code: ABC13\nDeparture airport code: SVO\nArrival "
      "airport code: VKO\nFlight duration: 75 minutes\nFlight cost: "
      "$234.500000\n\nMost advantageous air ticket:\nFlight code: "
      "CAB14\nDeparture airport code: SVO\nArrival airport code: VKO\nFlight "
      "duration: 95 minutes\nFlight cost: $113.454002\n",
      sizeof(char) * 1253);

  char input[] =
      "2\nABC13\nSVO\nVKO\n75\n234.5\nCAB14\nSVO\nVKO\n95\n113.454\nSVO\nVKO\n";

  FILE* input_file = fmemopen(input, sizeof(input), "r");

  char* test_output = new char[1253];
  FILE* output_file = fmemopen(test_output, sizeof(char) * 1253, "w");

  execute_program(input_file, output_file);

  putc('\0', output_file);

  fclose(input_file);
  fclose(output_file);

  EXPECT_EQ(strcmp(test_output, right_output), 0);

  delete[] right_output;
  delete[] test_output;
}
