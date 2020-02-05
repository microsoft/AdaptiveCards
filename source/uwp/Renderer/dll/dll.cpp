//
//    Copyright (C) Microsoft.  All rights reserved.
//
#include "pch.h"
#include <windows.h>
#include <wrl.h>
#include <wrl\wrappers\corewrappers.h>

using namespace Microsoft::WRL;

WrlCreatorMapIncludePragma(AdaptiveCardRenderer);

STDAPI DllGetActivationFactory(_In_ HSTRING activatableClassId, _COM_Outptr_ IActivationFactory** factory)
{
    return Module<ModuleType::InProc>::GetModule().GetActivationFactory(activatableClassId, factory);
}

STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _COM_Outptr_ void** ppv)
{
    return Module<ModuleType::InProc>::GetModule().GetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow()
{
    HRESULT hr = S_FALSE;
    if (Module<ModuleType::InProc>::GetModule().GetObjectCount() == 0)
    {
        Module<ModuleType::InProc>::GetModule().Terminate();
        hr = S_OK;
    }
    return hr;
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
