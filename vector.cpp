#ifndef VECTOR_CPP_
#define VECTOR_CPP_
#include "top.h"

vector_2 create_vector_2(double x, double y) {
	vector_2 vector = (vector_2)malloc(sizeof(vector_2_def));
	if (vector == NULL) {
		return NULL;
	}
	vector->x = x;
	vector->y = y;
	return vector;
}

double dotproduct_vector_2(vector_2 v1, vector_2 v2) {
	return v1->x * v2->x + v1->y * v2->y;
}

#endif // VECTOR_CPP_