/*
 * fpn_main.h Floating Point Number Extractor header file
 *
 * 2023 Sami Nofal
 *
 */
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SUCCESS 0
#define ERROR 1

/*
    function input reader define
*/
#define func_input_reader_def char *(*func_input_reader)()

/*
    validate_input_string
*/
int validate_input_string(char *input);

/*
    validate_num_within_range
*/
int validate_num_within_range(float num);

/*
    read_input
*/
char *read_input();

/*
    get_float_point_number
*/
int get_float_point_number(float *num, func_input_reader_def);

/*
    print_bit
*/
void print_bit(uint32_t num, int pos);

/*
    print_float_bits

*/
void print_float_bits(float num);

/*
    print_header
*/
void print_header();
