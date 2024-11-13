#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>

#include "DLLManager.h"
#include "InputOutput.h"
#include "Logger.h"
#include "Point.h"
#include "ThreadPool.h"
#include "Timer.h"

typedef Point* (*CalculateConvexHullFunc)(const Point*, int, int*);

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    DLLManager dllManager;
    Logger logger;
    InputOutput io;
    Timer timer;

    std::string filename = "1000000.txt";
    timer.Start();
    std::vector<Point> points = io.ReadPointsFromFileRemoveDuplicates(filename, logger);
    long long duration_microseconds = timer.Stop();
    std::cout << "Czas wykonania funkcji wczytyujacej dane wejsciowe: " << Timer::FormatDuration(duration_microseconds) << std::endl;

    if (points.empty()) {
        logger.LogError("Wystąpił problem podczas wczytywania punktów. Program zostanie zakończony.");
        return 1;
    }

    try {
        // Zaladowanie biblioteki w asm
        dllManager.LoadLibrary(L"JAAsm.dll");

        // Pobieranie funkcji o nazwie MyProc1 z biblioteki
        //MyProc1Func MyProc1 = dllManager.GetFunction<MyProc1Func>("MyProc1");
        

        // Przyklad uzycia funkcji 
        int x = 4;
        int y = 5;
        //int result = MyProc1(x, y);

        //std::cout << "Wynik ASM DLL: " << result << std::endl;

        // Przelacznik na biblioteke cpp
        dllManager.SwitchLibrary(L"JACpp.dll");
       // MyProc1 = dllManager.GetFunction<MyProc1Func>("MyProc1");
        CalculateConvexHullFunc calculateConvexHull = dllManager.GetFunction<CalculateConvexHullFunc>("CalculateConvexHull");
        if (!calculateConvexHull) {
            std::cerr << "Nie udało się załadować funkcji CalculateConvexHull z DLL." << std::endl;
            return 1;
        }
        
        // Przyklad uzycia ale jako biblioteka cpp
        int hull_size = 0;
        timer.Start();
        Point* hull_points = calculateConvexHull(points.data(), points.size(), &hull_size);
        std::vector<Point> convex_hull(hull_points, hull_points + hull_size);
        delete[] hull_points;   

        std::cout << "Punkty tworzące otoczkę wypukłą:" << std::endl;
        for (const auto& point : convex_hull) {
            std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
        }

        long long duration_microseconds = timer.Stop();
        std::cout << "Czas wykonania funkcji obliczajacej otoczke wypukla: " << Timer::FormatDuration(duration_microseconds) << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Blad: " << e.what() << std::endl;
    }

    // Zwolnienie biblioteki zaimplementowane w destruktorze klasy DLLmenager
    return 0;
}


