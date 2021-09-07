// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveRemoteResourceInformation.g.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct AdaptiveRemoteResourceInformation : AdaptiveRemoteResourceInformationT<AdaptiveRemoteResourceInformation>
    {
        AdaptiveRemoteResourceInformation() { }
        AdaptiveRemoteResourceInformation(::AdaptiveCards::RemoteResourceInformation const& info);

        property<hstring> Url;
        property<hstring> MimeType;
    };
}
namespace winrt::AdaptiveCards::ObjectModel::WinUI3::factory_implementation
{
    struct AdaptiveRemoteResourceInformation : AdaptiveRemoteResourceInformationT<AdaptiveRemoteResourceInformation, implementation::AdaptiveRemoteResourceInformation>
    {
    };
}
