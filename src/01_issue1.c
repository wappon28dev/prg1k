#include <stdio.h>
#include <string.h>
#define WIDTH 8
#define HEIGHT 5

typedef char Letter[WIDTH * HEIGHT + 1];

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

void display(char *letters[], int letterLength)
{
    for (int h = 0; h < HEIGHT; h++)
    {
        char rows[               //
            WIDTH * letterLength //
            + 1                  // for null terminator
        ];

        for (int i = 0; i < letterLength; i++)
        {
            char *letter = letters[i];
            for (int w = 0; w < WIDTH; w++)
            {
                rows[i * WIDTH + w] = letter[h * WIDTH + w];
            }
        }
        rows[WIDTH * letterLength] = '\0';
        printf("%s\n", rows);
    }
}

int main()
{
    char *it[] = {I, T};
    int itLength = sizeof(it) / sizeof(it[0]);
    display(it, itLength);

    char *ait[] = {A, I, T};
    int aitLength = sizeof(ait) / sizeof(ait[0]);
    display(ait, aitLength);

    char *tooHot[] = {A, T, T, I, T, T, I};
    int tooHotLength = sizeof(tooHot) / sizeof(tooHot[0]);
    display(tooHot, tooHotLength);

    return 0;
}
