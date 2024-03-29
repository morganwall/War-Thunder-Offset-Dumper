#include <Windows.h>
#include <iostream>
#include <vector>

using std::cout;
using std::vector;

std::uint8_t* Scan(const char* signature) noexcept
{
    static const auto patternToByte = [](const char* pattern) noexcept -> vector<int>
    {
        auto bytes = vector<int>{ };
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + std::strlen(pattern);

        for (auto current = start; current < end; ++current)
        {
            if (*current == '?')
            {
                ++current;

                if (*current == '?')
                    ++current;

                bytes.push_back(-1);
            }
            else
                bytes.push_back(std::strtoul(current, &current, 16));

        }

        return bytes;
    };

    static const auto handle = ::GetModuleHandleA("aces.exe");

    if (!handle)
        return nullptr;

    auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(handle);
    auto ntHeaders =
        reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(handle) + dosHeader->e_lfanew);

    auto size = ntHeaders->OptionalHeader.SizeOfImage;
    auto bytes = patternToByte(signature);
    auto scanBytes = reinterpret_cast<std::uint8_t*>(handle);

    auto s = bytes.size();
    auto d = bytes.data();

    for (auto i = 0ul; i < size - s; ++i)
    {
        bool found = true;

        for (auto j = 0ul; j < s; ++j)
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1)
            {
                found = false;
                break;
            }
        }

        if (found)
            return &scanBytes[i];
    }

    return nullptr;
}

const auto get = [](const char* signature) noexcept -> std::uintptr_t
{
    return reinterpret_cast<std::uintptr_t>(Scan(signature));
};

template<typename T = std::uintptr_t>
constexpr T GetOffset(std::uintptr_t address, int offset)
{
    return (T)(address + (int)((*(int*)(address + offset) + offset) + sizeof(int)));
}

DWORD WINAPI MainThread(HMODULE hModule)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    cout << "War Thunder Offset Dumper by morganlewiswall.\n\n";
	
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle("aces.exe");
    uintptr_t cGame = (GetOffset<std::uintptr_t>(get("48 8B 05 ? ? ? ? F2 0F 10 4F 08"), 0x3));
    uintptr_t cLocalPlayer = (GetOffset<std::uintptr_t>(get("48 8B 2D ? ? ? ? 48 85 ED 74 ? F6 85 ? ? ? ? ? 74"), 0x3));
    //uintptr_t cPlayerList = (GetOffset<std::uintptr_t>(get("48 8B 0D ? ? ? ? 89 C0 48 8B 1C C1 48 85 DB 74 ? 48 8B 05"), 0x3));
    uintptr_t cViewMatrix = (GetOffset<std::uintptr_t>(get("48 8D 0D ? ? ? ? FF 15 ? ? ? ? 0F 28 05"), 0x3));
    uintptr_t cHud = (GetOffset<std::uintptr_t>(get("48 8B 0D ? ? ? ? 80 B9 ? ? ? ? ? 0F 84 ? ? ? ? 80 BF"), 0x3));

    cout << "Addresses:\n";
    cout << "Base:         0x" << std::hex << std::uppercase << moduleBase << "\n";
    cout << "cGame:        0x" << std::hex << std::uppercase << cGame << "\n";
    cout << "cLocalPlayer: 0x" << std::hex << std::uppercase << cLocalPlayer << "\n";
    //cout << "cPlayerList:  0x" << std::hex << std::uppercase << cPlayerList << "\n";
    cout << "cViewMatrix:  0x" << std::hex << std::uppercase << cViewMatrix << "\n";
    cout << "cHud:         0x" << std::hex << std::uppercase << cHud << "\n";

    cout << "-----------------------------------------------------\n";

    cout << "Offsets:\n";
    cout << "cGame:        0x" << std::hex << std::uppercase << cGame - moduleBase << "\n";
    cout << "cLocalPlayer: 0x" << std::hex << std::uppercase << cLocalPlayer - moduleBase << "\n";
    //cout << "cPlayerList:  0x" << std::hex << std::uppercase << cPlayerList - moduleBase << "\n";
    cout << "cViewMatrix:  0x" << std::hex << std::uppercase << cViewMatrix - moduleBase << "\n";
    cout << "cHud:         0x" << std::hex << std::uppercase << cHud - moduleBase << "\n";
    
    cout << "-----------------------------------------------------\n";

    cout << "Press Delete to Exit Without Closing the Game.\n";
    while (true)
        if (GetAsyncKeyState(VK_DELETE))
            break;

    if (f)
        fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}