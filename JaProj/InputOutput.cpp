#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <regex>
#include <unordered_set>

#include "Point.h"
#include "Logger.h" 
#include "InputOutput.h"

std::vector<Point> InputOutput::ReadPointsFromFileRemoveDuplicates(const std::string& filename, Logger& logger) {
    std::vector<Point> points;
    constexpr double MIN_COORDINATE = -1e9;
    constexpr double MAX_COORDINATE = 1e9;
    constexpr double SCALE_FACTOR = 1e9; 

    
    struct PointHash {
        std::size_t operator()(const Point& p) const {
            auto xi = static_cast<int64_t>(p.x * SCALE_FACTOR);
            auto yi = static_cast<int64_t>(p.y * SCALE_FACTOR);
            return std::hash<int64_t>{}(xi) ^ (std::hash<int64_t>{}(yi) << 1);
        }
    };

    struct PointEqual {
        bool operator()(const Point& a, const Point& b) const {
            return std::abs(a.x - b.x) < 1e-9 && std::abs(a.y - b.y) < 1e-9;
        }
    };

    std::unordered_set<Point, PointHash, PointEqual> unique_points;
    std::ifstream file(filename);
    int line_number = 0;
    int error_count = 0;
    int duplicate_count = 0;

    if (!file.is_open()) {
        logger.LogError("Nie mo¿na otworzyæ pliku: " + filename);
        return points;
    }

    std::string line;
    while (std::getline(file, line)) {
        line_number++;

       
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

       
        double x, y;
        char extra;
        std::istringstream iss(line);

        
        if (!(iss >> x >> y) || iss.get(extra)) {
            logger.LogError("B³êdna linia " + std::to_string(line_number) + ": " + line);
            error_count++;
            continue;
        }

       
        if (x < MIN_COORDINATE || x > MAX_COORDINATE || y < MIN_COORDINATE || y > MAX_COORDINATE) {
            logger.LogError("Poza zakresem w linii " + std::to_string(line_number) + ": " + line);
            error_count++;
            continue;
        }

        Point point{ x, y };
        if (unique_points.insert(point).second) {
            points.push_back(point);
        }
        else {
            logger.LogInfo("Duplikat pominiêty w linii " + std::to_string(line_number) + ": " + line);
            duplicate_count++;
        }
    }

    file.close();

    if (points.size() < 3) {
        logger.LogError("Za ma³o poprawnych punktów (mniej ni¿ 3)");
    }
    else {
        logger.LogInfo("Za³adowano poprawnych punktów: " + std::to_string(points.size()));
        logger.LogInfo("Pominiêto duplikatów: " + std::to_string(duplicate_count));
        logger.LogInfo("Pominiêto b³êdnych linii: " + std::to_string(error_count));
    }

    return points;
}
std::vector<Point> InputOutput::ReadPointsFromFile(const std::string& filename, Logger& logger) {
    std::vector<Point> points;
    constexpr double MIN_COORDINATE = -1e9;
    constexpr double MAX_COORDINATE = 1e9;

    std::ifstream file(filename);
    int line_number = 0;
    int error_count = 0;

    if (!file.is_open()) {
        logger.LogError("Nie mo¿na otworzyæ pliku: " + filename);
        return points;
    }

    std::string line;
    while (std::getline(file, line)) {
        line_number++;

        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        double x, y;
        char extra;
        std::istringstream iss(line);

        if (!(iss >> x >> y) || iss.get(extra)) {
            logger.LogError("B³êdna linia " + std::to_string(line_number) + ": " + line);
            error_count++;
            continue;
        }

        if (x < MIN_COORDINATE || x > MAX_COORDINATE || y < MIN_COORDINATE || y > MAX_COORDINATE) {
            logger.LogError("Poza zakresem w linii " + std::to_string(line_number) + ": " + line);
            error_count++;
            continue;
        }

        points.push_back(Point{ x, y });
    }

    file.close();

    if (points.size() < 3) {
        logger.LogError("Za ma³o poprawnych punktów (mniej ni¿ 3)");
    }
    else {
        logger.LogInfo("Za³adowano poprawnych punktów: " + std::to_string(points.size()));
        logger.LogInfo("Pominiêto b³êdnych linii: " + std::to_string(error_count));
    }

    return points;
}