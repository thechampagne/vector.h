/*
 * Copyright (c) 2022 XXIV
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include <string.h>

typedef struct vector vector;

struct vector {
    char **buffer;
    size_t length;

    int (*push)(vector *, char *);

    int (*push_front)(vector *, char *);

    int (*is_empty)(vector *);
};

/**
 * Push element to the vector
 *
 * @param self pointer to the vector
 * @param s string
 * @return 0 on success and non zero value on failure
 */
int _push(vector *self, char *s) {
    if (self->length == 0) {
        self->buffer = (char **) malloc(sizeof(char *));
        if (self->buffer == NULL) {
            return -1;
        }
        self->buffer[self->length] = (char *) malloc((strlen(s) + 1) * sizeof(char));
        if (self->buffer[self->length] == NULL) {
            return -1;
        }
        strncpy(self->buffer[self->length], s, strlen(s));
        self->length += 1;
    } else {
        self->buffer = (char **) realloc(self->buffer, (self->length + 1) * sizeof(char *));
        if (self->buffer == NULL) {
            return -1;
        }
        self->buffer[self->length] = (char *) malloc((strlen(s) + 1) * sizeof(char));
        if (self->buffer[self->length] == NULL) {
            return -1;
        }
        strncpy(self->buffer[self->length], s, strlen(s));
        self->length += 1;
    }
    return 0;
}

/**
 * Push element to the first of the vector
 *
 * @param self pointer to the vector
 * @param s string
 * @return 0 on success and non zero value on failure
 */
int _push_front(vector *self, char *s) {
    if (self->length == 0) {
        self->buffer = (char **) malloc(sizeof(char *));
        if (self->buffer == NULL) {
            return -1;
        }
        self->buffer[self->length] = (char *) malloc((strlen(s) + 1) * sizeof(char));
        if (self->buffer[self->length] == NULL) {
            return -1;
        }
        strncpy(self->buffer[self->length], s, strlen(s));
        self->length += 1;
    } else {
        char **new_buff = (char **) malloc((self->length + 1) * sizeof(char *));
        if (new_buff == NULL) {
            return -1;
        }
        new_buff[0] = (char *) malloc((strlen(s) + 1) * sizeof(char));
        if (new_buff[0] == NULL) {
            return -1;
        }
        strncpy(new_buff[0], s, strlen(s));
        memcpy(new_buff + 1, self->buffer, self->length * sizeof(char *));
        free(self->buffer);
        self->buffer = new_buff;
        self->length += 1;
    }
    return 0;
}

/**
 * Check if the vector is empty
 *
 * @param self pointer to the vector
 * @return 1 if it's empty and 0 if it's not
 */
int _is_empty(vector *self) {
    if (self->length != 0) {
        return 0;
    }
    return 1;
}

/**
 * function to clean the memory after using the vector
 *
 * @param self pointer to the vector
 */
void vector_clean(vector *self) {
    if (self != NULL) {
        if (self->buffer != NULL) {
            for (int i = 0; i < self->length; i++) {
                if (self->buffer[i] != NULL) {
                    free(self->buffer[i]);
                }
            }
            free(self->buffer);
        }
        free(self);
    }
}

/**
 * function to create vector of strings
 *
 * @param self pointer to the vector
 * @return vector
 */
vector *vector_init() {
    vector *self = (vector *) malloc(sizeof(vector));
    if (self == NULL) {
        return NULL;
    }
    self->push = &_push;
    self->push_front = &_push_front;
    self->is_empty = &_is_empty;
    return self;
}

#endif // __VECTOR_H__