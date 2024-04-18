#include <stdio.h>
#include <string.h>
#define WIDTH 8
#define HEIGHT 5

typedef char Letter[WIDTH * HEIGHT + 1 /* ヌル終端 */];

Letter A =
    "    ___ "
    "   /   |"
    "  / /| |"
    " / ___ |"
    "/_/  |_|";

Letter I =
    "    ____"
    "   /  _/"
    "   / /  "
    " _/ /   "
    "/___/   ";

Letter T =
    "  ______"
    " /_  __/"
    "  / /   "
    " / /    "
    "/_/     ";

void displayAA(char *letters[], int letterLength)
{
    for (int h = 0; h < HEIGHT; h++)
    {
        char rows[WIDTH * letterLength + 1 /* ヌル終端 */];

        for (int letterIdx = 0; letterIdx < letterLength; letterIdx++)
        {
            char *letter = letters[letterIdx];
            for (int w = 0; w < WIDTH; w++)
            {
                rows[letterIdx * WIDTH + w] = letter[h * WIDTH + w];
            }
        }
        rows[WIDTH * letterLength] = '\0';
        printf("%s\n", rows);
    }
}

int main()
{
    char *it[] = {I, T};
    displayAA(it, sizeof(it) / sizeof(it[0])); // -> IT

    char *ait[] = {A, I, T};
    displayAA(ait, sizeof(ait) / sizeof(ait[0])); // -> AIT

    char *tooHot[] = {A, T, T, I, T, T, I};
    displayAA(tooHot, sizeof(tooHot) / sizeof(tooHot[0])); // -> ATTIITI

    return 0;
}
