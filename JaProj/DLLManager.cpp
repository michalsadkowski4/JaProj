#include "DLLManager.h"
#include <stdexcept>

DLLManager::DLLManager() : hDLL(nullptr) {}

DLLManager::~DLLManager() {
    UnloadLibrary();
}

bool DLLManager::LoadLibrary(const std::wstring& dllPath) {
    if (hDLL != nullptr) {
        UnloadLibrary();
    }

    hDLL = ::LoadLibrary(dllPath.c_str());
    if (!hDLL) {
        throw std::runtime_error("Zaladowanie biblioteki dll nie powiodlo sie: " + std::string(dllPath.begin(), dllPath.end()));
    }

    return true;
}

void DLLManager::UnloadLibrary() {
    if (hDLL) {
        ::FreeLibrary(hDLL);
        hDLL = nullptr;
    }
}

void DLLManager::SwitchLibrary(const std::wstring& newDllPath) {
    UnloadLibrary();
    LoadLibrary(newDllPath);
}