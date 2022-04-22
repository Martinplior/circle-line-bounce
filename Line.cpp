#ifndef LINE_CPP_
#define LINE_CPP_
#include "top.h"

Line create_Line(double A, double B, double C) {
	Line line = (Line)malloc(sizeof(Line_def));
	if (line == NULL) {
		return NULL;
	}
	double temp = sqrt(A * A + B * B);
	line->n = create_vector_2(A / temp, B / temp);
	if (line->n == NULL) {
		free(line);
		return NULL;
	}
	line->A = A;
	line->B = B;
	line->C = C;
	return line;
}

Line create_Line_2dots(double x1, double y1, double x2, double y2) {
	return create_Line(y1 - y2, x2 - x1, x1 * y2 - x2 * y1);
}

Line create_Line_LineSegment(LineSegment lineSeg) {
	return create_Line_2dots(lineSeg.x1, lineSeg.y1, lineSeg.x2, lineSeg.y2);
}
#endif // LINE_CPP_