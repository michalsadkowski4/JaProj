#ifndef CONVEX_HULL_CALCULATOR_H
#define CONVEX_HULL_CALCULATOR_H

#include "Point.h"



class ConvexHullCalculator {
public:
	static int Ccw(const Point& a, const Point& b, const Point& c);
	static double SqrDist(const Point& a, const Point& b);
	static bool PolarCompare(const Point& p0, const Point& a, const Point& b);
	Point* CalculateConvexHull(const Point* points, int num_points, int* out_size);
};

extern "C" __declspec(dllexport) Point* CalculateConvexHull(const Point* points, int num_points, int* out_size);


#endif // CONVEX_HULL_CALCULATOR_H
