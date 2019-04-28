#include "../includes/ant_engine.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint-gcc.h>
#include <string.h>

int
getSizeOf(char *arr)
{

    char* arr_ptr = &arr[0];
    int size = strlen(arr_ptr);

    int i = 0;
    int bars = 0;
    while (arr[i] != '\0') {
        if (arr[i] == '|'){
            bars++;
        }
        i++;
    }

    return  size - bars;
}

void
make(const char* p1, char* p2){

    int i = 0;
    int j = 0;
    while (p1[i] != '\0') {
        if (p1[i] != '|'){
            printf("%c", p1[i]);
            p2[j] = p1[i];
            j++;
        }
        i++;
    }
}

void*
paint(void *ant, void *grid, void *palette, void *rules,  uint32_t iterations)
{
  panic ("Implement me!");
  return grid;
}

char*
make_rules(char* spec)
{
    char* rules = malloc(getSizeOf(spec));

    make(spec, rules);

    return rules;
}

char*
make_palette(char* colours)
{
  char* palette = malloc(getSizeOf(colours));

  make(colours, palette);

  return palette;
}
