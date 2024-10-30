#ifndef DLLMANAGER_H
#define DLLMANAGER_H

#include <Windows.h>
#include <string>
#include <stdexcept>
#include <string>

class DLLManager {
public:
    DLLManager();
    ~DLLManager();

    bool LoadLibrary(const std::wstring& dllPath);
    void UnloadLibrary();

    template<typename T>
    T GetFunction(const std::string& functionName) {
        if (!hDLL) {
            throw std::runtime_error("DLLka nie zostala zaladowana.");
        }

        FARPROC procAddress = ::GetProcAddress(hDLL, functionName.c_str());
        if (!procAddress) {
            throw std::runtime_error("Nie otrzymano oczekiwanej funkcji z DLLki: " + functionName);
        }

        return reinterpret_cast<T>(procAddress);
    }

    void SwitchLibrary(const std::wstring& newDllPath);

private:
    HINSTANCE hDLL;
};
#endif // DLLMANAGER_H