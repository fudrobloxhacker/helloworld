#include <windows.h>
#include <array>
#include <intrin.h>

#pragma optimize("", off)
#pragma runtime_checks("", off)

#define _(x) ((x)^0xAA)
#define __(x) (x * 0x0101010101010101ULL & 0x8040201008040201ULL)
#define ___(x) reinterpret_cast<BOOL(WINAPI*)(HANDLE,LPCVOID,DWORD,LPDWORD,LPVOID)>(GetProcAddress(x,"WriteConsoleA"))

int main() {
    constexpr std::array<unsigned char, 12> _ = {
        _(0x48), _(0x65), _(0x6C), _(0x6C), _(0x6F), _(0x20),
        _(0x57), _(0x6F), _(0x72), _(0x6C), _(0x64), _(0x21)
    };

    std::array<char, 13> __;
    for (int ___ = 0; ___ < 12; ___++) {
        __[___] = static_cast<char>(_[___] ^ 0xAA);
    }

    HMODULE ____ = LoadLibraryA("kernel32.dll");
    if (!____) return 1;

    void* _____ = GetStdHandle(STD_OUTPUT_HANDLE);
    if (_____ == INVALID_HANDLE_VALUE) return 1;

    DWORD ______;
    if (!___(____)(_____, __.data(), 12, &______, 0)) return 1;

    unsigned char _______[] = {
        0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xFF, 0xE0
    };

    void* ________ = VirtualAlloc(0, sizeof(_______), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!________) return 1;

    memcpy(________, _______, sizeof(_______));
    *(void**)((char*)________ + 2) = ___(____);
    ((void(*)())________)();

    VirtualFree(________, 0, MEM_RELEASE);
    FreeLibrary(____);

    return 0;
}