//
//    Copyright (C) Microsoft.  All rights reserved.
//
#include "pch.h"
#include <windows.h>
#include <wrl.h>
#include <wrl\wrappers\corewrappers.h>
#include <module.g.cpp>

using namespace Microsoft::WRL;

STDAPI DllGetActivationFactory(_In_ HSTRING activatableClassId, _COM_Outptr_ IActivationFactory** factory)
{
    return WINRT_GetActivationFactory(activatableClassId, reinterpret_cast<void**>(factory));
}

STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _COM_Outptr_ void** ppv)
{
    return Module<ModuleType::InProc>::GetModule().GetClassObject(rclsid, riid, ppv);
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

STDAPI_(void) DllAddRef()
{
    Module<ModuleType::InProc>::GetModule().IncrementObjectCount();
}

STDAPI_(void) DllRelease()
{
    Module<ModuleType::InProc>::GetModule().DecrementObjectCount();
}
