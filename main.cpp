#include <iostream>
#include <utility>
#include <map>
#include "Windows.h"

// This program lists the window handles owned by the given process ID.

struct WindowInfo {
public:
    std::wstring text;
    HWND handle;
    WindowInfo(std::wstring text, HWND handle) {
        this->text = std::move(text);
        this->handle = handle;
    }
};

std::map<HWND, WindowInfo> foundWindows;

BOOL CALLBACK visitNextWindow(HWND windowHandle, LPARAM pid) {
    DWORD windowPid = NULL;
    GetWindowThreadProcessId(windowHandle, &windowPid);
    if (windowPid == pid) {
        auto textLen = GetWindowTextLengthW(windowHandle);
        std::wstring text(textLen, '\0');
        GetWindowTextW(windowHandle, &text[0], textLen+1);
        WindowInfo wi(text, windowHandle);
        foundWindows.emplace(windowHandle, wi);
    }
    return true;
}


int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cout << "Expected 1 argument: process ID";
        return 1;
    }

    auto pidLen = strlen(argv[1]);
    int pid = strtol(argv[1], &argv[1] + pidLen, 10);

    EnumWindows(visitNextWindow, pid);

    auto count = foundWindows.size();
    std::cout << "Found " << count << " windows for process " << pid << ".\n";
    if (count > 0) {
        std::cout << "Handle\t\t\tText\n";
    }
    for (auto const& pair : foundWindows) {
        std::cout << pair.first << "\t";
        std::wcout << pair.second.text << "\n";
    }

    return 0;
}
