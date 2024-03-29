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

#define vector_new(T) \
\
typedef struct vector_##T vector_##T; \
\
struct vector_##T { \
    T *buffer; \
    size_t length; \
\
    int (*push)(vector_##T *, T); \
\
    int (*push_front)(vector_##T *, T); \
\
    int (*remove)(vector_##T*,int); \
\
    int (*is_empty)(vector_##T *); \
}; \
\
int _push_##T(vector_##T *self, T input) { \
    if (self->length == 0) { \
        self->buffer = (T *) malloc(sizeof(T)); \
        if (self->buffer == NULL) { \
            return -1; \
        } \
        self->buffer[self->length] = input; \
        self->length += 1; \
    } else { \
        self->buffer = (T *) realloc(self->buffer, (self->length + 1) * sizeof(T)); \
        if (self->buffer == NULL) { \
            return -1; \
        } \
        self->buffer[self->length] = input; \
        self->length += 1; \
    } \
    return 0; \
} \
\
int _push_front_##T(vector_##T *self, T input) { \
    if (self->length == 0) { \
        self->buffer = (T *) malloc(sizeof(T)); \
        if (self->buffer == NULL) { \
            return -1; \
        } \
        self->buffer[self->length] = input; \
        self->length += 1; \
    } else { \
        T *new_buff = (T *) malloc((self->length + 1) * sizeof(T)); \
        if (new_buff == NULL) { \
            return -1; \
        } \
        new_buff[0] = input; \
        memcpy(new_buff + 1, self->buffer, self->length * sizeof(T)); \
        free(self->buffer); \
        self->buffer = new_buff; \
        self->length += 1; \
    } \
    return 0; \
} \
\
int _remove_##T(vector_##T* self, int index) \
{ \
  if (!(index >= 0 && index < self->length)) \
  { \
    return -1; \
  } \
  T * new_buff = (T*) malloc((self->length - 1) * sizeof(T)); \
  if (new_buff == NULL) \
  { \
    return -1; \
  } \
  int new_buff_i = 0; \
  for (int i = 0; i < self->length; i++) \
  { \
    if (i == index) \
    { \
      continue; \
    } \
    new_buff[new_buff_i] = self->buffer[i]; \
    new_buff_i++; \
  } \
  free(self->buffer); \
  self->buffer = new_buff; \
  self->length -= 1; \
  return 0; \
} \
\
int _is_empty_##T(vector_##T *self) { \
    if (self->length != 0) { \
        return 0; \
    } \
    return 1; \
} \
\
void vector_##T##_clean(vector_##T *self) { \
    if (self != NULL) { \
        if (self->buffer != NULL) { \
            free(self->buffer); \
        } \
        free(self); \
    } \
} \
\
vector_##T *vector_##T##_init() { \
    vector_##T *self = (vector_##T *) malloc(sizeof(vector_##T)); \
    if (self == NULL) { \
        return NULL; \
    } \
    self->push = &_push_##T; \
    self->push_front = &_push_front_##T; \
    self->remove = &_remove_##T; \
    self->is_empty = &_is_empty_##T; \
    return self; \
} \


typedef struct vector vector;

struct vector {
    char **buffer;
    size_t length;

    int (*push)(vector *, char *);

    int (*push_front)(vector *, char *);

    int (*remove)(vector*,int);

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
 * Remove element from the vector
 *
 * @param self pointer to the vector
 * @param index index to remove
 * @return 0 on success and non zero value on failure
 */
int _remove(vector* self, int index)
{
  if (!(index >= 0 && index < self->length))
  {
    return -1;
  }
  char** new_buff = (char**) malloc((self->length - 1) * sizeof(char*));
  if (new_buff == NULL)
  {
    return -1;
  }
  int new_buff_i = 0;
  for (int i = 0; i < self->length; i++)
  {
    if (i == index)
    {
      continue;
    }
    new_buff[new_buff_i] = (char*) malloc((strlen(self->buffer[i]) + 1) * sizeof(char));
    strncpy(new_buff[new_buff_i], self->buffer[i], strlen(self->buffer[i]));
    new_buff_i++;
  }
  for (int i = 0; i < self->length; i++)
  {
    free(self->buffer[i]);
  }
  free(self->buffer);
  self->buffer = new_buff;
  self->length -= 1;
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
    self->remove = &_remove;
    self->is_empty = &_is_empty;
    return self;
}

#endif // __VECTOR_H__