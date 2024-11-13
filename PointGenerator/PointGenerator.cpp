#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <utility>
#include <cmath> // dla std::round

using Point = std::pair<double, double>;

std::vector<Point> generateRandomPoints(int numPoints) {
    std::vector<Point> points;
    const int minCoordinate = -10000;
    const int maxCoordinate = 10000;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(minCoordinate, maxCoordinate);
    std::uniform_int_distribution<int> intOrDouble(0, 1);

    for (int i = 0; i < numPoints; ++i) {
        double x = dis(gen);
        double y = dis(gen);

        // Losowy wybór czy współrzędna ma być zaokrąglona do int
        if (intOrDouble(gen) == 0) x = static_cast<int>(x);
        if (intOrDouble(gen) == 0) y = static_cast<int>(y);

        // Zaokrąglenie do trzech miejsc po przecinku
        x = std::round(x * 1000.0) / 1000.0;
        y = std::round(y * 1000.0) / 1000.0;

        points.emplace_back(x, y);
    }

    return points;
}

void savePointsToFile(const std::vector<Point>& points, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& point : points) {
            file << point.first << " " << point.second << "\n";
        }
        file.close();
        std::cout << "Punkty zapisane do pliku: " << filename << std::endl;
    }
    else {
        std::cerr << "Nie można otworzyć pliku do zapisu!" << std::endl;
    }
}

int main() {
    int numPoints;
    std::cout << "Podaj liczbę punktów do wygenerowania: ";
    std::cin >> numPoints;

    std::vector<Point> points = generateRandomPoints(numPoints);
    savePointsToFile(points, "punkty.txt");

    return 0;
}