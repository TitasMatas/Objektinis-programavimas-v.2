#include <windows.h>
#include <shlobj.h>
#include <shobjidl.h>
#include <objbase.h>
#include <KnownFolders.h>
#include <iostream>
#include <string>

static std::wstring getSpecialFolder(int csidl) {
    wchar_t path[MAX_PATH] = {0};
    HRESULT hr = SHGetFolderPathW(nullptr, csidl, nullptr, SHGFP_TYPE_CURRENT, path);
    if (FAILED(hr)) return L"";
    return path;
}

static std::wstring getKnownFolder(REFKNOWNFOLDERID id) {
    PWSTR p = nullptr;
    HRESULT hr = SHGetKnownFolderPath(id, 0, nullptr, &p);
    if (FAILED(hr) || !p) return L"";
    std::wstring s(p);
    CoTaskMemFree(p);
    return s;
}

static bool ensureDirectoryW(const std::wstring& path) {
    int res = SHCreateDirectoryExW(nullptr, path.c_str(), nullptr);
    return (res == ERROR_SUCCESS) || (res == ERROR_ALREADY_EXISTS);
}

static std::wstring getExeDirW() {
    wchar_t buffer[MAX_PATH] = {0};
    GetModuleFileNameW(nullptr, buffer, MAX_PATH);
    std::wstring fullPath(buffer);
    size_t pos = fullPath.find_last_of(L"\\/");
    if (pos == std::wstring::npos) return L".";
    return fullPath.substr(0, pos);
}

static bool copyFileToW(const std::wstring& src, const std::wstring& dst) {
    return CopyFileW(src.c_str(), dst.c_str(), FALSE) != 0;
}

static bool createShortcutW(
    const std::wstring& shortcutPath,
    const std::wstring& targetPath,
    const std::wstring& description
) {
    IShellLinkW* pShellLink = nullptr;
    IPersistFile* pPersistFile = nullptr;

    HRESULT hr = CoCreateInstance(
        CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER,
        IID_IShellLinkW, reinterpret_cast<void**>(&pShellLink)
    );
    if (FAILED(hr) || !pShellLink) return false;

    pShellLink->SetPath(targetPath.c_str());
    pShellLink->SetDescription(description.c_str());

    hr = pShellLink->QueryInterface(IID_IPersistFile, reinterpret_cast<void**>(&pPersistFile));
    if (FAILED(hr) || !pPersistFile) {
        pShellLink->Release();
        return false;
    }

    hr = pPersistFile->Save(shortcutPath.c_str(), TRUE);

    pPersistFile->Release();
    pShellLink->Release();

    return SUCCEEDED(hr);
}

static void printLastError(const wchar_t* where) {
    DWORD e = GetLastError();
    std::wcerr << L"[KLAIDA] " << where << L" GetLastError=" << e << L"\n";
}

int main() {
    const std::wstring installDir = L"C:\\Program Files\\VU\\Titas-Matas";
    const std::wstring programPath = installDir + L"\\programa.exe";

    std::wcout << L"=== Setup installer ===\n";
    std::wcout << L"[OK] Sukurtas aplankas i Program files: " << installDir << L"\n";

    const std::wstring baseDir = getExeDirW();
    const std::wstring srcProgram = baseDir + L"\\programa.exe";

    if (!ensureDirectoryW(installDir)) {
        std::wcerr << L"[KLAIDA] Nepavyko sukurti katalogo. Paleisk Setup.exe su Administrator teisėmis.\n";
        return 1;
    }

    if (!copyFileToW(srcProgram, programPath)) {
        std::wcerr << L"[KLAIDA] Reikia paleisti Setup.exe su Admin\n";
        printLastError(L"CopyFileW");
        return 2;
    }

    HRESULT hr = CoInitialize(nullptr);
    if (FAILED(hr)) {
        std::wcerr << L"[KLAIDA] Nepavyko inicializuoti COM (CoInitialize).\n";
        return 3;
    }

    // OneDrive-aware Desktop
    const std::wstring desktop = getKnownFolder(FOLDERID_Desktop);
    std::wcout << L"[OK] Desktop kelias: " << desktop << L"\n";

    if (desktop.empty()) {
        std::wcerr << L"[KLAIDA] Nepavyko gauti Desktop kelio.\n";
        CoUninitialize();
        return 4;
    }

    std::wstring desktopLnk = desktop + L"\\Studentu Pazymiu Sistema.lnk";
    if (!createShortcutW(desktopLnk, programPath, L"Studentu Pazymiu Sistema")) {
        std::wcerr << L"[KLAIDA] Nepavyko sukurti Desktop nuorodos: " << desktopLnk << L"\n";
        printLastError(L"IPersistFile::Save");
    } else {
        std::wcout << L"[OK] Sukurta Desktop nuoroda: " << desktopLnk << L"\n";
    }

    // Start Menu (current user)
    const std::wstring programs = getSpecialFolder(CSIDL_PROGRAMS);
    if (!programs.empty()) {
        const std::wstring startFolder = programs + L"\\VU\\Titas-Matas";
        ensureDirectoryW(startFolder);

        std::wstring startLnk = startFolder + L"\\Studentu Pazymiu Sistema.lnk";
        if (!createShortcutW(startLnk, programPath, L"Studentu Pazymiu Sistema")) {
            std::wcerr << L"[KLAIDA] Nepavyko sukurti Start Menu nuorodos: " << startLnk << L"\n";
        }
    }

    CoUninitialize();

    std::wcout << L"[OK] Baigta.\n";
    return 0;
}
