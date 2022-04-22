#include "top.h"

int main() {
	initgraph(WIDTH, HEIGHT);
	setorigin(0, HEIGHT);
	setaspectratio(1, -1);
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	Circle circle = create_Circle(WIDTH / 2,
		HEIGHT / 2, 50, 500, 0);
	LineSegment lineSeg[LINE_NUMBER] = {};
	lineSeg[0] = { 200,100,1100,200 };
	lineSeg[1] = { 1100,200,600,650 };
	lineSeg[2] = { 600,650,200,100 };
	Line line[LINE_NUMBER] = {};
	for (int i = 0; i < LINE_NUMBER; i++) {
		line[i] = create_Line_LineSegment(lineSeg[i]);
	}
	Status changed = FALSE;
	Status active = ON;
	arglist_logic arg_logic = {};
	arg_logic.active = &active;
	arg_logic.changed = &changed;
	arg_logic.circle = circle;
	arg_logic.circle_display = copy_Circle(circle);
	arg_logic.lineList = line;
	arg_logic.lineListLength = LINE_NUMBER;
	arglist_display arg_display = {};
	arg_display.active = &active;
	arg_display.changed = &changed;
	arg_display.circle_display = arg_logic.circle_display;
	arg_display.lineSegList = lineSeg;
	arg_display.linSegListLength = LINE_NUMBER;
	arglist_control arg_control = {};
	arg_control.active = &active;
	HANDLE handle[3];
	handle[2] = (HANDLE)_beginthread(logic, 0, (void*)&arg_logic);
	handle[1] = (HANDLE)_beginthread(display, 0, (void*)&arg_display);
	handle[0] = (HANDLE)_beginthread(control, 0, (void*)&arg_control);
	WaitForMultipleObjects(3, handle, TRUE, INFINITE);
	closegraph();
	return 0;
}