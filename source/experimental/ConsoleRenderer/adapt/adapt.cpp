// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "stdafx.h"

using namespace AdaptiveSharedNamespace;

DWORD SetConsoleModeForDisplay()
{
    DWORD dwRet = 0;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOut != INVALID_HANDLE_VALUE)
    {
        GetConsoleMode(hOut, &dwRet);
        SetConsoleMode(hOut, dwRet | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }

    return dwRet;
}

void RestoreConsoleModeForDisplay(DWORD dwRestore)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOut != INVALID_HANDLE_VALUE)
    {
        SetConsoleMode(hOut, dwRestore);
    }
}

int main(int /*argc*/, char *argv[])
{
    DWORD dwOld = SetConsoleModeForDisplay();

    auto parseResult = AdaptiveCard::DeserializeFromFile(argv[1], "1.1");

    std::vector<std::string> result;
    RenderToConsole(parseResult->GetAdaptiveCard(), 120U, result);
    for (auto row : result)
    {
        printf(row.c_str());
        printf("\n");
    }

    RestoreConsoleModeForDisplay(dwOld);
    return 0;
}
