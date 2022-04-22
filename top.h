#ifndef TOP_H_
#define TOP_H_
#include <stdio.h>
#include <graphics.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <process.h>

#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0

#define PI 3.1415926535
#define FPS_logic 100.0
#define FPS_display 100.0
#define ONE_SEC 1000.0
#define WIDTH 1280
#define HEIGHT 720
#define LINE_NUMBER 3

#define MIN2(X,Y) (((X)<(Y))?(X):(Y))
#define MAX2(X,Y) (((X)>(Y))?(X):(Y))

typedef char Status;

typedef struct {
	double x;
	double y;
}vector_2_def, * vector_2;

typedef struct {
	double x;
	double y;
	double r;
	double speed;// 速度 pixel/s
	double theta;// 方向 θ∈[0,2π)
	vector_2 e;// 方向向量
}Circle_def, * Circle;

typedef struct {
	// Ax+By+C=0
	double A;
	double B;
	double C;
	vector_2 n;// 法向量
}Line_def, * Line;

typedef struct {
	Circle circle_display;
	Status* changed;
	Circle circle;
	Line* lineList;
	int lineListLength;
	Status* active;
}arglist_logic;

typedef struct {
	double x1;
	double y1;
	double x2;
	double y2;
}LineSegment;

typedef struct {
	Circle circle_display;
	LineSegment* lineSegList;
	int linSegListLength;
	Status* changed;
	Status* active;
}arglist_display;

typedef struct {
	Status* active;
}arglist_control;

// vector.cpp
vector_2 create_vector_2(double x, double y);
double dotproduct_vector_2(vector_2 v1, vector_2 v2);

// Circle.cpp
Circle create_Circle(double x, double y, double r, double speed, double theta);
Circle copy_Circle(Circle circle);
Status copyto_Circle(Circle source, Circle& target);
void destroy_Circle(Circle& circle);
Status remapTheta(double& theta);

// Line.cpp
Line create_Line(double A, double B, double C);
Line create_Line_2dots(double x1, double y1, double x2, double y2);
Line create_Line_LineSegment(LineSegment lineSeg);

// bounce.cpp
char sgn(double x);
Status isCollided_Circle_Line(Circle circle, Line line);
Status isAcross_Circle_Line(Circle circle, Circle nextCircle, Line line);
Status isCollidedOrAcross(Circle circle, Circle nextCircle, Line line);
void gotoNext_Circle(Circle& circle, double time);
double time_gotoLine_Circle(Circle circle, Line line);
Status setDirectionOfReflection_remapped(Circle& circle, Line line);
double gotoClosestLine_Circle(Circle& circle, Circle nextCircle,
	Line* lineList, int lineListLength, double totalTime);

// threads.cpp
void logic(void* arg);
void display(void* arg);
void control(void* arg);

#endif// TOP_H_

