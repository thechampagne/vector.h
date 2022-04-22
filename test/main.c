#include <stdio.h>
#include "vector.h"

int main()
{
	vector* vec = vector_init();
	vec->push(vec,"Hello World");
	for (int i = 0; i < vec->length; i++)
	{
		printf("%s\n", vec->buffer[i]);
	}
	vector_clean(vec);
	return 0;
}