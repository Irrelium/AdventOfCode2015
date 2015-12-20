#include <stdio.h>
#include <stdlib.h>

#define IN_FILE "input.txt"

int parse_line(int *array, char *line);
int ribbon_amount(int *box_dims);

int main(int argc, char *argv[])
{
    char line[20];
    int current_line = 0;
    FILE *in_file;
    int box_dims[3];
    int total_length; // of ribbon

    in_file = fopen(IN_FILE, "r");
    if (in_file == NULL) {
        fprintf(stderr, "File could not be opened!");
        exit(1);
    }

    while (fgets(line, sizeof(line), in_file) != NULL) {
        current_line++;
        if (parse_line(box_dims, line) != 0) {
            fprintf(stderr, "Error parsing line %d!\n", current_line);
            exit(1);
        }
        total_length += ribbon_amount(box_dims);
    }
    fclose(in_file);

    printf("%d\n", total_length);

    return 0;
}

// Parse a line of a format such as "4x23x1" into an array containing 4, 23,
// and 1. Returns success value.
int parse_line(int *array, char *line)
{
    char *next_dim = line;
    char *pos = line;
    int i;

    for (i = 0; i < 3; i++) {
        // Split the string on an 'x' character
        while ((*pos != 'x') && (*pos != '\0')) {
            pos++;
        }
        *pos = '\0';
        pos++;

        if (!sscanf(next_dim, "%d", &array[i])) {
            return 1;
        }
        next_dim = pos;
    }

    return 0;
}

// Calculate the amount of ribbon needed to wrap a box
int ribbon_amount(int *box_dims)
{
    int perimeter_sections[3]; // perimeters of different sections of the box
    int smallest_perimeter;
    int total_ribbon = 0; // length
    int i;

    perimeter_sections[0] = 2 * (box_dims[0] + box_dims[1]);
    perimeter_sections[1] = 2 * (box_dims[0] + box_dims[2]);
    perimeter_sections[2] = 2 * (box_dims[1] + box_dims[2]);

    smallest_perimeter = perimeter_sections[0];
    for (i = 1; i < 3; i++) {
        if (perimeter_sections[i] < smallest_perimeter) {
            smallest_perimeter = perimeter_sections[i];
        }
    }

    // Total ribbon needed is the shortest distance around the box…
    total_ribbon += smallest_perimeter;
    // …plus a length equal to the cubic feet of the volume of the present
    total_ribbon += box_dims[0] * box_dims[1] * box_dims[2];

    return total_ribbon;
}
