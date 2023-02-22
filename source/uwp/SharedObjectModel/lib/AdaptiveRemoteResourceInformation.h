// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveRemoteResourceInformation.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    struct AdaptiveRemoteResourceInformation : AdaptiveRemoteResourceInformationT<AdaptiveRemoteResourceInformation>
    {
        AdaptiveRemoteResourceInformation() { }
        AdaptiveRemoteResourceInformation(::AdaptiveCards::RemoteResourceInformation const& info);

        property<hstring> Url;
        property<hstring> MimeType;
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::factory_implementation
{
    struct AdaptiveRemoteResourceInformation : AdaptiveRemoteResourceInformationT<AdaptiveRemoteResourceInformation, implementation::AdaptiveRemoteResourceInformation>
    {
    };
}
