#include <iostream>
#include <cstdint>
#include <thread>

#include "cheats.h" // structs.h->memory.h
#include "gui.h"

DWORD WINAPI Payload(HMODULE hModule)
{
    // LOAD CHEAT DATA
    if ((BYTE)(PedFactory) != 0xE0) // check if pedfactory doesnt point to a struct
    {
        std::cout << "Structures Aren't Updated!\nClosing in 3 seconds...";
        Sleep(3000);
        exit(1);
    }

    Cheats Cheats;

    // load player name
    for (uint8_t i = 0; i < 24; i++)
    {
        if (PedFactory->Ped->PlayerInfo->PlayerName[i] == 0) break;
        Config::pname += (PedFactory->Ped->PlayerInfo->PlayerName[i]);
    }

    // gui init
    gui::CreateHWindow("Cheat Menu");
    gui::CreateDevice();
    gui::CreateImGui();

    SetWindowPos(gui::window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    while (gui::isRunning)
    {
        gui::BeginRender();
        gui::Render();
        gui::EndRender();
        Cheats.CheckUpdate(); // check for gui update

        Sleep(10);
    }
    
    // destroy gui
    gui::DestroyImGui();
    gui::DestroyDevice();
    gui::DestroyHWindow();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Payload, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

