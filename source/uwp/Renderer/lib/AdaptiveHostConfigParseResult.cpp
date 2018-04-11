#include "pch.h"
#include "AdaptiveHostConfigParseResult.h"

#include "AdaptiveCard.h"
#include <windows.foundation.collections.h>
#include <Windows.UI.Xaml.h>
#include "XamlBuilder.h"
#include "XamlHelpers.h"
#include "AdaptiveHostConfig.h"
#include "vector.h"

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

AdaptiveNamespaceStart
    AdaptiveHostConfigParseResult::AdaptiveHostConfigParseResult()
    {
    }

    HRESULT AdaptiveHostConfigParseResult::RuntimeClassInitialize()
    {
        m_errors = Make<Vector<IAdaptiveError*>>();
        return S_OK;
    }

    HRESULT AdaptiveHostConfigParseResult::RuntimeClassInitialize(IAdaptiveHostConfig* value)
    {
        m_hostConfig = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfigParseResult::get_HostConfig(IAdaptiveHostConfig** value)
    {
        return m_hostConfig.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfigParseResult::get_Errors(ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveError*>** value)
    {
        return m_errors.CopyTo(value);
    }
AdaptiveNamespaceEnd
