
#ifndef MORSE_H
#define MORSE_H

#include <stdio.h>

void print_help();
void print_programmer_info();
int encode(const char *input, FILE *output, int use_slash_wordspacer);
int decode(const char *input, FILE *output);

#endif // MORSE_H
