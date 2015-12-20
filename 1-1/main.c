#include <stdio.h>

#define IN_FILE "input.txt"

int main(int argc, char *argv[])
{
    FILE *in_file;
    char ch;
    int floor = 0; // santa's current floor

    in_file = fopen(IN_FILE, "r");
    do {
        ch = fgetc(in_file);
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
    } while (ch != EOF);

    printf("%d\n", floor);

    return 0;
}
