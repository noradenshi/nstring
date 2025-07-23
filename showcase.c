#include <stdio.h>
#include <stdlib.h>
#include "nstring.h"

int main(void)
{
    struct string *strings[3];

    strings[0] = string_strnew("Hello");
    strings[1] = string_strnew("world");
    strings[2] = string_clone(strings[0]);

    string_strappend(&strings[2], " ");
    string_append(&strings[2], strings[1]);

    for (int i=0; i<3; i++) {
        string_println(strings[i]);
    }

    printf("string_find(s2, s1) = %d\n", string_find(strings[2], strings[1]));

    for (int i=0; i<3; i++) {
        free(strings[i]);
    }

    return EXIT_SUCCESS;
}
