#include "nstring.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ALLOCATE

struct string *string_new(const size_t capacity) {
    struct string *s = malloc(sizeof(struct string) + capacity + 1);
    if (s == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }

    s->capacity = capacity;
    s->length = 0;
    s->buf[0] = 0;

    return s;
}

struct string *string_strnnew(const char *const str, const size_t length) {
    if (!str) {
        perror("Attempt to create a NULL string");
        return NULL;
    }

    struct string *s = string_new(length);
    s->length = length;

    memcpy(s->buf, str, s->length);
    s->buf[s->length] = 0;

    return s;
}

struct string *string_strnew(const char *const str) {
    if (!str) {
        perror("Attempt to create a NULL string");
        return NULL;
    }

    return string_strnnew(str, strlen(str));
}

struct string *string_clone(const struct string *const str) {
    if (!str) {
        perror("Attempt to create a NULL string");
        return NULL;
    }

    struct string *s = string_new(str->length);
    s->length = str->length;

    memcpy(s->buf, str->buf, s->length);
    s->buf[s->length] = 0;

    return s;
}

// MODIFY

bool string_strnappend(struct string **dest, const char *src, const size_t length) {
    if (!dest || !src || !*dest)
        return false;

    if ((*dest)->capacity >= (*dest)->length + length + 1) {
        memcpy(&((*dest)->buf[(*dest)->length]), src, length);

        (*dest)->length += length;
        (*dest)->buf[(*dest)->length] = 0;

        return true;
    }

    if ((*dest)->length > SIZE_MAX - length - 1)
        return false;

    const size_t buffer_size = (*dest)->length + length + 1;

    struct string *str = realloc(*dest, sizeof(struct string) + buffer_size);

    if (str == NULL) {
        perror("Failed to reallocate memory");
        return false;
    }

    *dest = str;

    memcpy(&((*dest)->buf[(*dest)->length]), src, length);

    (*dest)->capacity = buffer_size;
    (*dest)->length += length;
    (*dest)->buf[(*dest)->length] = 0;

    return true;
}

bool string_append(struct string **dest, const struct string *src) {
    if (!src)
        return false;

    return string_strnappend(dest, src->buf, src->length);
}

bool string_strappend(struct string **dest, const char *src) {
    if (!src)
        return false;

    return string_strnappend(dest, src, strlen(src));
}

bool string_shrink(struct string *const str, const size_t length) {
    if (!str || str->length < length)
        return false;

    str->length -= length;
    str->buf[str->length] = 0;

    return true;
}

// PRINT

void string_print(const struct string *const str) {
    if (!str)
        return;

    printf("%s", str->buf);
}

void string_println(const struct string *const str) {
    if (!str)
        return;

    printf("%s\n", str->buf);
}

// COMPARE

int string_compare(const struct string *const str_a,
                   const struct string *const str_b) {
    if (!str_a || !str_b) {
        perror("NULL arguments in string_compare()");
        return 0;
    }

    if (str_a->length != str_b->length) {
        return str_a->length - str_b->length;
    }

    for (size_t i = 0; i < str_a->length; i++) {
        if (str_a->buf[i] != str_b->buf[i])
            return str_a->buf[i] - str_b->buf[i];
    }

    return 0;
}

bool string_equals(const struct string *const str_a,
                   const struct string *const str_b) {

    if (!str_a || !str_b) {
        perror("NULL arguments in string_compare()");
        return false;
    }

    if (str_a->length != str_b->length) {
        return false;
    }

    for (size_t i = 0; i < str_a->length; i++) {
        if (str_a->buf[i] != str_b->buf[i])
            return false;
    }

    return true;
}

int string_nfind(const struct string *const str, const char *const needle,
                 const size_t n) {

    if (!str || !needle) {
        perror("NULL arguments in string_nfind()");
        return -1;
    }

    if (n == 0 || str->length < n)
        return -1;

    for (size_t i = 0; i <= str->length - n; i++) {
        size_t j = 0;
        for (; j < n; j++) {
            if (str->buf[i + j] != needle[j])
                break;
        }

        if (j == n)
            return i;
    }

    return -1;
}

int string_find(const struct string *const str, const struct string *const needle) {
    if (!str || !needle) {
        perror("NULL arguments in string_find()");
        return -1;
    }

    return string_nfind(str, needle->buf, needle->length);
}

int string_strfind(const struct string *const str, const char *const needle) {
    if (!str || !needle) {
        perror("NULL arguments in string_strfind()");
        return -1;
    }

    return string_nfind(str, needle, strlen(needle));
}
