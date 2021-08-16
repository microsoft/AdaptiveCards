// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveMediaEventArgs.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Data::Json;

namespace AdaptiveCards::Rendering::WinUI3
{
    HRESULT AdaptiveMediaEventArgs::RuntimeClassInitialize() { return S_OK; }

    HRESULT AdaptiveMediaEventArgs::RuntimeClassInitialize(_In_ IAdaptiveMedia* media)
    {
        m_media = media;
        return S_OK;
    }

    HRESULT AdaptiveMediaEventArgs::get_Media(_COM_Outptr_ IAdaptiveMedia** media) { return m_media.CopyTo(media); }
}
