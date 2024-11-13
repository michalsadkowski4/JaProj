#include "ConvexHullCalculator.h"
#include <algorithm>
#include <cmath>
#include <vector>


int ConvexHullCalculator::Ccw(const Point& a, const Point& b, const Point& c) {
    double area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area > 0) return -1; 
    if (area < 0) return 1;  
    return 0;                
}


double ConvexHullCalculator::SqrDist(const Point& a, const Point& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool ConvexHullCalculator::PolarCompare(const Point& p0, const Point& a, const Point& b) {
    int order = Ccw(p0, a, b);
    if (order == 0)
        return SqrDist(p0, a) < SqrDist(p0, b);
    return order == -1;
}


Point* ConvexHullCalculator::CalculateConvexHull(const Point* points, int num_points, int* out_size) {
    if (num_points < 3) {
        *out_size = 0;
        return nullptr;
    }

    
    std::vector<Point> points_vec(points, points + num_points);

    
    auto it = std::min_element(points_vec.begin(), points_vec.end(),
        [](const Point& a, const Point& b) {
            return a.y < b.y || (a.y == b.y && a.x < b.x);
        });
    Point p0 = *it;
    points_vec.erase(it);

    
    std::sort(points_vec.begin(), points_vec.end(),
        [&p0](const Point& a, const Point& b) {
            return PolarCompare(p0, a, b);
        });

   
    points_vec.insert(points_vec.begin(), p0);

    
    std::vector<Point> hull;
    hull.push_back(points_vec[0]);
    hull.push_back(points_vec[1]);

    for (size_t i = 2; i < points_vec.size(); ++i) {
        while (hull.size() > 1 &&
            Ccw(hull[hull.size() - 2], hull.back(), points_vec[i]) != -1) {
            hull.pop_back();
        }
        hull.push_back(points_vec[i]);
    }

    
    *out_size = static_cast<int>(hull.size());
    Point* result = new Point[*out_size];
    std::copy(hull.begin(), hull.end(), result);
    return result;
}

extern "C" __declspec(dllexport) Point* CalculateConvexHull(const Point* points, int num_points, int* out_size) {
    ConvexHullCalculator calculator;
    return calculator.CalculateConvexHull(points, num_points, out_size);
}