#include <windows.h>
#include <shlobj.h>
#include <iostream>
#include <string>

static bool ensureDirectory(const std::string& path) {
    int res = SHCreateDirectoryExA(nullptr, path.c_str(), nullptr);
    return (res == ERROR_SUCCESS) || (res == ERROR_ALREADY_EXISTS);
}

static std::string getExeDir() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    std::string fullPath(buffer);
    size_t pos = fullPath.find_last_of("\\/");
    if (pos == std::string::npos) return ".";
    return fullPath.substr(0, pos);
}

static bool copyFileTo(const std::string& src, const std::string& dst) {
    return CopyFileA(src.c_str(), dst.c_str(), FALSE) != 0;
}

int main() {
    const std::string installDir = "C:\\Program Files\\VU\\Titas-Matas";

    std::cout << "=== Setup installer ===\n";
    std::cout << "Diegimo katalogas: " << installDir << "\n\n";

    const std::string baseDir = getExeDir();

    const std::string srcProgram = baseDir + "\\programa.exe";
    const std::string dstProgram = installDir + "\\programa.exe";

    const std::string srcReadme = baseDir + "\\README.md";
    const std::string dstReadme = installDir + "\\README.md";

    if (!ensureDirectory(installDir)) {
        std::cerr << "[KLAIDA] Nepavyko sukurti katalogo. Paleisk Setup.exe su Administrator teisėmis.\n";
        return 1;
    }

    if (!copyFileTo(srcProgram, dstProgram)) {
        std::cerr << "[KLAIDA] Nepavyko nukopijuoti programa.exe.\n";
        std::cerr << "Patikrink, ar programa.exe yra tame pačiame folderyje kaip Setup.exe.\n";
        return 2;
    }

    // Optional README
    copyFileTo(srcReadme, dstReadme);

    std::cout << "[OK] Programa idiegta sekmingai!\n";
    std::cout << "Kelias: " << installDir << "\n";
    std::cout << "Paleidimas: " << dstProgram << "\n\n";
    std::cout << "Pastaba: jei diegimas nepavyko, paleisk Setup.exe su 'Run as Administrator'.\n";

    return 0;
}
