#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include "Point.h"

class InputOutput {
	std::vector<Point> ReadPointsFromFile(const std::string& filename);
	void WritePointsToFile(const std::string& filename, const std::vector<Point>& points);
};
#endif // INPUT_OUTPUT