#include <stdio.h>

#define IN_FILE "input.txt"

int main(int argc, char *argv[])
{
    FILE *in_file;
    char ch;
    int floor = 0; // santa's current floor
    int char_pos = 0; // current character position

    in_file = fopen(IN_FILE, "r");
    do {
        ch = fgetc(in_file);
        char_pos++;
        switch (ch) {
            case '(':
                floor++;
                break;
            case ')':
                floor--;
                break;
            default:
                break;
        }

        if (floor < 0) { // if santa is in the basement
            printf("Basement entered at at character %d.\n", char_pos);
            return 0;
        }
    } while (ch != EOF);

    printf("Santa never entered the basement.\n");
    return 1;
}
