/*
 * fpn_main.c Floating Point Number Extracter Test File
 * 
 * 2023 Sami Nofal
 *
 */
#include "fpn_utils.h"

#include <assert.h>

/*
    test_validate_input_string
    Function to test validate_input_string method 
*/
void test_validate_input_string() {
  char * pos_valid_input = "+15.32";
  char * neg_valid_input = "-15.32";
  char * invalid_input = "AAAA";
  char * invalid_input_mix = "24r.AAA";

  assert(validate_input_string(pos_valid_input) == SUCCESS);
  assert(validate_input_string(neg_valid_input) == SUCCESS);
  assert(validate_input_string(invalid_input) == ERROR);
  assert(validate_input_string(invalid_input_mix) == ERROR);
}

/*
    test_validate_num_within_range
    Function to test test_validate_num_within_range method
*/
void test_validate_num_within_range() {

  float overflow_number = HUGE_VALF;
  float neg_overflow_number = -HUGE_VALF;
  float valid_number = FLT_MAX;
  float valid_number_small = 14.424;

  assert(validate_num_within_range(overflow_number) == ERROR);
  assert(validate_num_within_range(neg_overflow_number) == ERROR);
  assert(validate_num_within_range(valid_number * 10) == ERROR); // Overflow Case
  assert(validate_num_within_range(valid_number) == SUCCESS);
  assert(validate_num_within_range(valid_number_small) == SUCCESS);

}

char * SIMUTLATED_VALID_INPUT[5] = {
  "15.32",
  "14425.32",
  "2425",
  "0",
  "0.044"
};
float SIMUTLATED_VALID_FLOAT[5] = {
  15.32,
  14425.32,
  2425,
  0,
  0.044
};
char * SIMUTLATED_INVALID_INPUT[5] = {
  "15...",
  "-feafe",
  "00...03332",
  "0..0",
  ""
};

int idx = 0;
/* 
    read_input_stub_valid 
    Stub function to simulate valid user input 
    NOTE: get_float_point_number is expected to free allocated memory
*/
char * read_input_stub_valid() {
  size_t max_size_of_string = sizeof(char) * 50;
  char * line = (char * ) malloc(max_size_of_string);
  snprintf(line, max_size_of_string, "%s", SIMUTLATED_VALID_INPUT[idx]);
  printf("%s", line);
  return line;
}

/* 
    read_input_stub_invalid 
    Stub function to simulate invalid user input 
    NOTE: get_float_point_number is expected to free allocated memory
*/
char * read_input_stub_invalid() {
  size_t max_size_of_string = sizeof(char) * 50;
  char * line = (char * ) malloc(max_size_of_string);
  snprintf(line, max_size_of_string, "%s", SIMUTLATED_INVALID_INPUT[idx]);
  return line;
}
/*
    test_get_float_point_number
    Runs get_float_point_number on different types of input and verifies that the function handles valid
    and invalid cases
*/
void test_get_float_point_number() {
  float output_val = 0;
  for (idx = 0; idx < 5; idx++) {
    assert(get_float_point_number( &output_val, read_input_stub_valid) == SUCCESS);
    assert(SIMUTLATED_VALID_FLOAT[idx] == output_val);
  }
  for (idx = 0; idx < 5; idx++) {
    assert(get_float_point_number( &output_val, read_input_stub_invalid) == ERROR);
  }
}

#define BUFFER_SIZE 1024
/* 
    test_print_float_bits
    Test case to verify that the output of the program is as expected
*/
void test_print_float_bits() {
  char buffer[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);
  FILE * mem_stream = fmemopen(buffer, BUFFER_SIZE, "w");
  if (mem_stream == NULL) {
    perror("fmemopen failed");
    exit(1);
  }
  stdout = mem_stream;
  print_float_bits(15.32);
  stdout = fdopen(1, "w");
  assert(strstr(buffer, "0 10000010 11101010001111010111000") != NULL);
}
/* 
    test_print_header
    Test case to verify that the output header of the program is as expected
*/
void test_print_header() {
  char buffer[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);
  FILE * mem_stream = fmemopen(buffer, BUFFER_SIZE, "w");
  if (mem_stream == NULL) {
    perror("fmemopen failed");
    exit(1);
  }
  stdout = mem_stream;
  print_header();
  stdout = fdopen(1, "w");
  assert(strstr(buffer, "Sign Exponent Mantissa") != NULL);
}

#define NUMBER_OF_TESTS 5
/* 
    Test case Driver
*/
int main() {
  void( * test_func_p[NUMBER_OF_TESTS])() = {
    &test_validate_input_string,
    &test_validate_num_within_range,
    &test_get_float_point_number,
    &test_print_float_bits,
    &test_print_header,
  };

  for (int i = 0; i < NUMBER_OF_TESTS; i++) {
    ( *test_func_p[i])();
    printf("Successfully executed test case number: %d\n", i);
  }

}