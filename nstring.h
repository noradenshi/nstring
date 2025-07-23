#ifndef NSTRING_H
#define NSTRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

struct string {

    // Maximum string length including the NULL terminator
    size_t capacity;

    // Length of the string buffer not including the NULL terminator
    size_t length;

    // c-style string, ended with a NULL terminator
    char buf[];
};

// ALLOCATE

struct string *string_strnnew(const char *str, const size_t length);
struct string *string_strnew(const char *str);
struct string *string_new(const size_t length);
struct string *string_clone(const struct string *str);

// struct string *string_getline(FILE *stream);

// MODIFY

bool string_append(struct string **dest, const struct string *src);
bool string_strappend(struct string **dest, const char *src);
bool string_strnappend(struct string **dest, const char *src, const size_t length);
bool string_shrink(struct string *str, const size_t length);

// PRINT

void string_print(const struct string *str);
void string_println(const struct string *str);

// COMPARE

int string_find(const struct string *str, const struct string *needle);
int string_nfind(const struct string *str, const char *needle, const size_t n);
int string_strfind(const struct string *str, const char *needle);
int string_compare(const struct string *str_a, const struct string *str_b);
bool string_equals(const struct string *str_a, const struct string *str_b);

#endif
