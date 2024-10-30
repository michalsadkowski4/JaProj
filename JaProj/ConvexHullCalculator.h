#ifndef CONVEXHULLCALCULATOR_H
#define CONVEXHULLCALCULATOR_H

#include <vector>
#include "Point.h"

class ConvexHullCalculator
{
	enum AlgorithmMode currentMode;
	int threadCount;

	std::vector<Point> CalculateConvexHull(const std::vector<Point>& points);
	void SetAlgorithmMode(AlgorithmMode mode);
	void SetThreadCount(int count);
};
#endif // CONVEXHULLCALCULATOR_H