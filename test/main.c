#include <stdio.h>
#include "vector.h"

int main()
{
	vector* vec = vector_init();
	vec->push(vec,"Hello World");
  	vec->push_front(vec, "I'm the first"); // no you'r not
  	vec->remove(vec, 0);
	for (int i = 0; i < vec->length; i++)
	{
		printf("%s\n", vec->buffer[i]);
	}
	vector_clean(vec);
	return 0;
}