#include "flight.h"

int main(void) {
  int return_code = execute_program(stdin, stdout);
  display_notification(stdout, return_code);

  return return_code;
}
