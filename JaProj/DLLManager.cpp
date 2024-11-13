#include "DLLManager.h"
#include <stdexcept>
#include <locale>
#include <codecvt>

DLLManager::DLLManager() : hDLL(nullptr) {}

DLLManager::~DLLManager() {
    UnloadLibrary();
}

bool DLLManager::LoadLibrary(const std::wstring& dllPath) {
    if (hDLL != nullptr) {
        UnloadLibrary();
    }

    hDLL = ::LoadLibraryW(dllPath.c_str());
    if (!hDLL) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string dllPathStr = converter.to_bytes(dllPath);
        throw std::runtime_error("Zaladowanie biblioteki dll nie powiodlo sie: " + dllPathStr);
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