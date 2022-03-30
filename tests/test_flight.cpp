#include <gtest/gtest.h>

extern "C" {
#include "flight.h"
}

TEST(Notification, FORMAT_ERROR) {
    char right_string[] = "Entered string format is incorrect.\nPlease retype it -> ";

    char test_string[sizeof(right_string)];
    FILE* output_file = fmemopen(test_string, sizeof(right_string), "w");

    display_notification(output_file, FORMAT_ERROR);
    fflush(output_file);

    EXPECT_EQ(strcmp(test_string, right_string), 0);

    fclose(output_file);
}

TEST(Notification, MEMORY_ALLOCATION_ERROR) {
    char right_string[] = "\nError occurred while trying to allocate memory.\nPlease clear your RAM and run the program again.";

    char test_string[sizeof(right_string)];
    FILE* output_file = fmemopen(test_string, sizeof(right_string), "w");

    display_notification(output_file, MEMORY_ALLOCATION_ERROR);
    fflush(output_file);

    EXPECT_EQ(strcmp(test_string, right_string), 0);

    int *a = (int*)malloc(1);

    fclose(output_file);
}