/*
 * fpn_main.c Floating Point Number Extractor
 * 
 * 2023 Sami Nofal
 *
 */

#include "fpn_utils.h"

int main() {
  float num = 0;
  if (get_float_point_number( &num, &read_input) == ERROR) {
    exit(EXIT_FAILURE);
  }
  print_header();
  print_float_bits(num);

  return 0;
}