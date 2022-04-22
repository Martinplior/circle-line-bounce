#ifndef BOUNCE_CPP_
#define BOUNCE_CPP_
#include "top.h"

char sgn(double x) {
	if (x < 0) {
		return -1;
	}
	return 1;
}

Status isCollided_Circle_Line(Circle circle, Line line) {
	// temp1=|Ax0+By0+C|
	double temp1 = line->A * circle->x
		+ line->B * circle->y + line->C;
	if (temp1 < 0) {
		temp1 = -temp1;
	}
	// temp2=r*sqrt(A^2+B^2)
	double temp2 = circle->r * sqrt(line->A * line->A
		+ line->B * line->B);
	// |Ax0+By0+C|<=r*sqrt(A^2+B^2)
	if (temp1 <= temp2) {
		return TRUE;
	}
	return FALSE;
}

Status isAcross_Circle_Line(Circle circle, Circle nextCircle, Line line) {
	double A = circle->y - nextCircle->y;
	double B = nextCircle->x - circle->x;
	double C = circle->x * nextCircle->y - nextCircle->x * circle->y;
	double detD = A * line->B - line->A * B;
	if (detD == 0) {
		return FALSE;
	}
	double detDx = B * line->C - line->B * C;
	double detDy = line->A * C - A * line->C;
	double Lx = detD * MIN2(circle->x, nextCircle->x);
	double Rx = detD * MAX2(circle->x, nextCircle->x);
	double Dy = detD * MIN2(circle->y, nextCircle->y);
	double Uy = detD * MAX2(circle->y, nextCircle->y);
	if (Lx <= detDx && detDx <= Rx && Dy <= detDy && detDy <= Uy) {
		return TRUE;
	}
	return FALSE;
}

Status isCollidedOrAcross(Circle circle, Circle nextCircle, Line line) {
	if (TRUE == isCollided_Circle_Line(nextCircle, line)
		|| TRUE == isAcross_Circle_Line(circle, nextCircle, line)) {
		return TRUE;
	}
	return FALSE;
}

void gotoNext_Circle(Circle& circle, double time) {
	circle->x += time * circle->speed * circle->e->x;
	circle->y += time * circle->speed * circle->e->y;
}

double time_gotoLine_Circle(Circle circle, Line line) {
	// P=Ax0+By0+C
	double P = line->A * circle->x + line->B * circle->y + line->C;
	// Q=speed*(A*cosθ+B*sinθ)
	double Q = circle->speed * (line->A * cos(circle->theta)
		+ line->B * sin(circle->theta));
	// R=r*sqrt(A^2+B^2)
	double R = circle->r * sqrt(line->A * line->A + line->B * line->B);
	return -(P + sgn(Q) * R) / Q;
}

Status setDirectionOfReflection_remapped(Circle& circle, Line line) {
	if (circle == NULL) {
		return FALSE;
	}
	circle->theta = PI - circle->theta + 2 * sgn(line->n->y)
		* acos(line->n->x);
	remapTheta(circle->theta);
	circle->e->x = cos(circle->theta);
	circle->e->y = sin(circle->theta);
	return TRUE;
}

double gotoClosestLine_Circle(Circle& circle, Circle nextCircle,
	Line* lineList, int lineListLength, double totalTime) {
	if (lineListLength <= 0) {
		return totalTime;
	}
	// 源圆到line[0]的时间
	double minTime = time_gotoLine_Circle(circle, lineList[0]);
	double temp = 0;
	int lineIndex = 0;
	// 如果不止一条直线，选择到达时间最短的一条
	if (lineListLength > 1) {
		for (int i = 1; i < lineListLength; i++) {
			temp = time_gotoLine_Circle(circle, lineList[i]);
			if (temp < minTime) {
				minTime = temp;
				lineIndex = i;
			}
		}
	}
	// 源圆以速度方向前进minTime
	gotoNext_Circle(circle, minTime);
	// 改变源圆方向
	setDirectionOfReflection_remapped(circle, lineList[lineIndex]);
	// 返回剩余时间
	return totalTime - minTime;
}
#endif // BOUNCE_CPP_