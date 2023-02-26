/*
 * fpn_utils.c Floating Point Number Extractor Utility file
 * 
 * 2023 Sami Nofal
 *
 */
#include "fpn_utils.h"

/*
    validate_input_string
    Helper function to validate input entered by user
    
    Input:
        char*
    Output:
        int (error code)
*/
int validate_input_string(char * input) {
  unsigned long i = 0;
  for (i = 0; i < strlen(input); i++) {
    if (!isdigit(input[i]) && input[i] != '.' && input[i] != '-' && input[i] != '+') {
      printf("Error: Invalid character found in input\n");
      return ERROR;
    }
  }
  return SUCCESS;
}

/*
    validate_num_within_range
    Helper function to validate num is withing floating point range
    
    Input:
        char*
    Output:
        int (error code)
*/
int validate_num_within_range(float num) {

  if (num == HUGE_VALF || num == -HUGE_VALF) {
    printf("Error: Value out of range for float\n");
    return ERROR;
  }
  return SUCCESS;
}

char * read_input() {
  char * buffer = NULL;
  size_t len = 0;
  ssize_t nread = getline( & buffer, & len, stdin);
  if (nread == -1) {
    perror("getline failed to read input");
    exit(EXIT_FAILURE);
  }
  // Remove newline character at the end of the line
  buffer[strcspn(buffer, "\n")] = '\0';
  return buffer;
}

/*
    get_float_point_number
    Helper function to get floating point number from user
    
    Input:
        float*
    Output:
        int (error code)
*/
int get_float_point_number(float * num, func_input_reader_def) {

  char * end_pointer = NULL;
  float value = 0;
  char * input = NULL;
  int err_code = SUCCESS;
  printf("Enter a 32-bit floating point number: ");
  input = func_input_reader();

  if (strspn(input, " \t\n") == strlen(input)) {
    perror("Error: Input is empty\n");
    err_code = ERROR;
    goto cleanup_and_return;
  }

  if (validate_input_string(input) == ERROR) {
    err_code = ERROR;
    goto cleanup_and_return;
  };

  value = strtof(input, & end_pointer);

  if ( * end_pointer != '\0') {
    perror("Error: Invalid input value\n");
    err_code = ERROR;
    goto cleanup_and_return;

  }

  if (validate_num_within_range(value) == ERROR) {
    err_code = ERROR;
    goto cleanup_and_return;
  }

  if (err_code == SUCCESS) {
    *num = value;
  }

  cleanup_and_return:
    free(input);
    return err_code;
}

/*
    print_bit
    Helper function to print a single bit of 32 bit number
    
    Input:
        uint32_t
        int
    Output:
        void
*/
void print_bit(uint32_t num, int pos) {
  printf("%d", (num & (1 << pos)) ? 1 : 0);
}

/*
    print_float_bits
    Function to print the bits of a 32-bit floating point number.
    The function assumes a valid floating point number has been provided.

      Input:
        float
      Output:
        void

*/
void print_float_bits(float num) {

  uint32_t * float_as_uint = (uint32_t * ) & num;
  uint32_t sign = ( * float_as_uint >> 31) & 1;
  uint32_t exponent = ( * float_as_uint >> 23) & 0xff;
  uint32_t mantissa = * float_as_uint & 0x7fffff;

  printf("   %u ", sign);

  for (int i = 7; i >= 0; i--) {
    print_bit(exponent, i);
  }

  printf(" ");
  for (int i = 22; i >= 0; i--) {
    print_bit(mantissa, i);
  }

  printf("\n");
}

/*
    print_header
    Function to print the header of the result
*/
void print_header() {
  char * header = "\nSign Exponent Mantissa\n";
  printf("%s", header);
}