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
