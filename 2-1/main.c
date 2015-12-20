#include <stdio.h>
#include <stdlib.h>

#define IN_FILE "input.txt"

int parse_line(int *array, char *line);
int paper_amount(int *box_dims);

int main(int argc, char *argv[])
{
    char line[20];
    int current_line = 0;
    FILE *in_file;
    int box_dims[3];
    int total_area; // Total area of wrapping paper to order

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
        total_area += paper_amount(box_dims);
    }
    fclose(in_file);

    printf("%d\n", total_area);

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

// Calculate the amount of paper needed to wrap a box
int paper_amount(int *box_dims)
{
    int area_sections[3]; // areas of different sections of the box
    int smallest_area; // smallest section by area
    int total_area = 0; // total area of the paper
    int i;

    area_sections[0] = box_dims[0] * box_dims[1];
    area_sections[1] = box_dims[0] * box_dims[2];
    area_sections[2] = box_dims[1] * box_dims[2];

    smallest_area = area_sections[0];
    for (i = 0; i < 3; i++) {
        total_area += 2 * area_sections[i];
        if (area_sections[i] < smallest_area) {
            smallest_area = area_sections[i];
        }
    }
    total_area += smallest_area;

    return total_area;
}
