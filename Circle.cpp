#ifndef CIRCLE_CPP_
#define CIRCLE_CPP_
#include "top.h"

Circle create_Circle(double x, double y, double r, double speed, double theta) {
	Circle circle = (Circle)malloc(sizeof(Circle_def));
	if (circle == NULL) {
		return NULL;
	}
	remapTheta(theta);
	circle->e = create_vector_2(cos(theta), sin(theta));
	if (circle->e == NULL) {
		free(circle);
		return NULL;
	}
	circle->theta = theta;
	circle->x = x;
	circle->y = y;
	circle->r = r;
	circle->speed = speed;
	return circle;
}

Circle copy_Circle(Circle circle) {
	return create_Circle(circle->x, circle->y,
		circle->r, circle->speed, circle->theta);
}

Status copyto_Circle(Circle source, Circle& target) {
	if (source == NULL || target == NULL) {
		return FALSE;
	}
	target->x = source->x;
	target->y = source->y;
	target->r = source->r;
	target->speed = source->speed;
	target->theta = source->theta;
	target->e->x = source->e->x;
	target->e->y = source->e->y;
	return TRUE;
}

void destroy_Circle(Circle& circle) {
	if (circle == NULL) {
		return;
	}
	free(circle->e);
	free(circle);
}

Status remapTheta(double& theta) {
	if (theta < 0) {
		do {
			theta += 2 * PI;
		} while (theta < 0);
	}
	else if (theta >= 2 * PI) {
		do {
			theta -= 2 * PI;
		} while (theta >= 2 * PI);
	}
	return TRUE;
}
#endif // CIRCLE_CPP_