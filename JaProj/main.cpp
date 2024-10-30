#include <iostream>
#include <vector>
#include <windows.h>

#include "ConvexHullCalculator.h"
#include "DLLManager.h"
#include "InputOutput.h"
#include "Logger.h"
#include "Point.h"
#include "ThreadPool.h"
#include "Timer.h"
#include "VectorOperations.h"

typedef int (*MyProc1Func)(int, int);

int main()
{
    DLLManager dllManager;

    try {
        // Zaladowanie biblioteki w asm
        dllManager.LoadLibrary(L"JAAsm.dll");

        // Pobieranie funkcji o nazwie MyProc1 z biblioteki
        MyProc1Func MyProc1 = dllManager.GetFunction<MyProc1Func>("MyProc1");

        // Przyklad uzycia funkcji 
        int x = 4;
        int y = 5;
        int result = MyProc1(x, y);

        std::cout << "Wynik ASM DLL: " << result << std::endl;

        // Przelacznik na biblioteke cpp
        dllManager.SwitchLibrary(L"JACpp.dll");
        MyProc1 = dllManager.GetFunction<MyProc1Func>("MyProc1");

        // Przyklad uzycia ale jako biblioteka cpp
        result = MyProc1(x, y);
        std::cout << "Wynik C++ DLL: " << result << std::endl;

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Blad: " << e.what() << std::endl;
    }

    // Zwolnienie biblioteki zaimplementowane w destruktorze klasy DLLmenager
    return 0;
}

