#include <iostream>
#include <windows.h>

//extern "C" int MyProc1(int a, int b);
typedef int (*MyProc1Func)(int, int);
HINSTANCE hDLL = LoadLibrary(L"JAAsm.dll");
MyProc1Func MyProc1 = (MyProc1Func)GetProcAddress(hDLL, "MyProc1");

int main()
{
    int x = 4;
    int y = 5;
    int result = MyProc1(x, y);
    
    std::cout << result;
    FreeLibrary(hDLL);
}

