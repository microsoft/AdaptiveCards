//
//    Copyright (C) Microsoft.  All rights reserved.
//
#include "pch.h"
#include <module.g.cpp>

STDAPI DllGetActivationFactory(_In_ HSTRING activatableClassId, _COM_Outptr_ IActivationFactory** factory)
{
    return WINRT_GetActivationFactory(activatableClassId, reinterpret_cast<void**>(factory));
}

STDAPI DllCanUnloadNow()
{
    return WINRT_CanUnloadNow();
}

STDAPI_(BOOL) DllMain(_In_ HINSTANCE hInstance, _In_ DWORD dwReason, _In_ void* /*lpReserved*/)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hInstance);
        break;
    }
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
