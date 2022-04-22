#ifndef THREADS_CPP_
#define THREADS_CPP_
#include "top.h"

void logic(void* arg) {
	arglist_logic* arg1 = (arglist_logic*)arg;
	Circle circle_display = arg1->circle_display;
	Status* changed = arg1->changed;
	Circle circle = arg1->circle;
	Line* lineList = arg1->lineList;
	int lineListLength = arg1->lineListLength;
	Status* active = arg1->active;
	Circle nextCircle = copy_Circle(circle);
	int i = 0;
	Line* buffer = (Line*)malloc(lineListLength * sizeof(Line));
	for (i = 0; i < lineListLength; i++) {
		buffer[i] = NULL;
	}
	int bufferLength = 0;

	double t_start = 0;
	double t = 0;
	double t1 = 0;
	double t0 = clock();
	t_start = clock();
	while (*active == ON) {
		copyto_Circle(circle, nextCircle);
		t = (clock() - t_start) / CLOCKS_PER_SEC;
		t_start = clock();
		gotoNext_Circle(nextCircle, t);
		for (bufferLength = 0;;) {
			for (i = 0; i < lineListLength; i++) {
				if (TRUE == isCollidedOrAcross(circle, nextCircle, lineList[i])) {
					// 将可能发生碰撞的直线放入buffer
					buffer[bufferLength++] = lineList[i];
				}
			}
			if (bufferLength > 0) {
				// 源圆circle来到最近的直线
				t = gotoClosestLine_Circle(circle, nextCircle, buffer, bufferLength, t);
				// 探路圆nextCircle来到下一位置
				copyto_Circle(circle, nextCircle);
				gotoNext_Circle(nextCircle, t);
				bufferLength = 0;
			}
			else {
				// 无碰撞，结束循环
				break;
			}
		}
		// 源圆circle最终来到探路圆nextCircle位置
		copyto_Circle(nextCircle, circle);
		if (FALSE == *changed) {
			copyto_Circle(circle, circle_display);
			*changed = TRUE;
		}
		// 帧率控制
		t1 = clock();
		t = ONE_SEC / FPS_logic - (t1 - t0);
		if (t >= 1) {
			Sleep((int)t);
		}
		t0 = t1;
	}
	_endthread();
}

void display(void* arg) {
	arglist_display* arg1 = (arglist_display*)arg;
	Circle circle_display = arg1->circle_display;
	LineSegment* lineSegList = arg1->lineSegList;
	int lineSegListLength = arg1->linSegListLength;
	Status* changed = arg1->changed;
	Status* active = arg1->active;
	Circle circle_copy = copy_Circle(circle_display);
	int i = 0;
	double t = 0;
	double t1 = 0;
	double t0 = clock();
	while (*active == ON) {
		if (TRUE == *changed) {
			copyto_Circle(circle_display, circle_copy);
			*changed = FALSE;
		}
		BeginBatchDraw();
		cleardevice();
		for (i = 0; i < lineSegListLength; i++) {
			line(lineSegList[i].x1,
				lineSegList[i].y1,
				lineSegList[i].x2,
				lineSegList[i].y2);
		}
		circle(circle_copy->x,
			circle_copy->y,
			circle_copy->r);
		line(circle_copy->x,
			circle_copy->y,
			circle_copy->x + circle_copy->e->x * circle_copy->r,
			circle_copy->y + circle_copy->e->y * circle_copy->r);
		EndBatchDraw();
		// 帧率控制
		t1 = clock();
		t = ONE_SEC / FPS_display - (t1 - t0);
		if (t >= 1) {
			Sleep((int)t);
		}
		t0 = t1;
	}
	_endthread();
}

void control(void* arg) {
	arglist_control* arg1 = (arglist_control*)arg;
	Status* active = arg1->active;
	ExMessage m;
	while (*active == ON) {
		m = getmessage(EM_KEY);
		if (WM_KEYDOWN == m.message) {
			if (VK_ESCAPE == m.vkcode) {
				*active = OFF;
			}
		}
		flushmessage(EM_KEY);
	}
	_endthread();
}
#endif // THREADS_CPP_