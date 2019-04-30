#include "../includes/ant_engine.h"
#include "../includes/ant_constants.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint-gcc.h>
#include <string.h>

typedef enum colour {RED = CR, GREEN = CG, BLUE = CB, YELLOW = CY, BLACK = CN, WHITE = CW} colour_t;
typedef enum orientation {NORTH = ON, SOUTH = OS, EAST = OE, WEST = OW} orientation_t;

typedef struct {
    uint32_t width;
    uint32_t height;
    colour_t **grid;
} square_grid_t;

typedef struct {
    int colour;
    char rule;
} colour_rules;

typedef struct {
    uint32_t x, y;
    orientation_t o;
} ant_t;

colour_rules* colourRules;
int colourRulesLength = 0;

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
    int length = size - bars;

    return  length;
}

void
make(const char* p1, char* p2){

    int i = 0;
    int j = 0;
    while (p1[i] != '\0') {
        if (p1[i] != '|'){
            p2[j] = p1[i];
            j++;
        }
        i++;
    }
}

void
makeColourRules(const char *palette, const char *rules){

    colourRules = malloc(colourRulesLength);
    for(int i=0; i < colourRulesLength; i++){
        char c = palette[i];
        switch(c) {
            case 'R':
                colourRules[i].colour = CR;
                break;
            case 'G':
                colourRules[i].colour = CG;
                break;
            case 'B':
                colourRules[i].colour = CB;
                break;
            case 'Y':
                colourRules[i].colour = CY;
                break;
            case 'N':
                colourRules[i].colour = CN;
                break;
            case 'W':
                colourRules[i].colour = CW;
                break;
            default:
                fprintf(stderr, "Invalid: %c\n", c);
                exit(2);
        }
        colourRules[i].rule = rules[i];
    }
}

char getDirectionFromPreviousColour(int previousColour){

    char direction = 'x';
    for(int i=0; i < colourRulesLength; i++){
        if(previousColour == colourRules[i].colour){
            direction = colourRules[i].rule;
        }
    }
    return direction;
}

void*
paint(void *ant, void *grid, void *palette, void *rules,  uint32_t iterations)
{
    makeColourRules(palette, rules);

    ant_t* artistAnt = ant;
    square_grid_t* squareGrid =  grid;
    int it = 0;
    int actualColour = 1;
    int min = -1;
    int max = squareGrid->width;
    char direction;

    while(it != iterations){

        if(actualColour > colourRulesLength-1){
            actualColour = 0;
        }

        int previousColour = squareGrid->grid[artistAnt->x][artistAnt->y]; //obtengo el color de la celda actual
        direction = getDirectionFromPreviousColour(previousColour); //obtengo regla de la celda actual a partir de su color
        squareGrid->grid[artistAnt->x][artistAnt->y] = colourRules[actualColour].colour; //pinta

        switch(direction) { //se mueve
            case 'L':
                artistAnt->y = artistAnt->y - 1;
                break;
            case 'R':
                artistAnt->y = artistAnt->y + 1;
                break;
            default:
                fprintf(stderr, "Invalid: %c\n", direction);
                exit(2);
        }
        //me fijo si se fue de la grid y la reubico en el lado opuesto
        if(artistAnt->y == min){
            artistAnt->y = squareGrid->width -1;
        }
        if(artistAnt->y == max){
            artistAnt->y = 0;
        }
        actualColour++,
        it++;
    }

    return squareGrid;
}

void*
make_rules(char* spec)
{
    char* rules = malloc(getSizeOf(spec));

    make(spec, rules);

    return rules;
}

void*
make_palette(char* colours)
{
  char* palette = malloc(getSizeOf(colours));
  colourRulesLength = getSizeOf(colours);

  make(colours, palette);

  return palette;
}
