#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include "Point.h"
#include "Logger.h"

class InputOutput {
public:
	std::vector<Point> ReadPointsFromFile(const std::string& filename, Logger& logger );
	std::vector<Point> ReadPointsFromFileRemoveDuplicates(const std::string& filename, Logger& logger);
	void WritePointsToFile(const std::string& filename, const std::vector<Point>& points);
};
#endif // INPUT_OUTPUT