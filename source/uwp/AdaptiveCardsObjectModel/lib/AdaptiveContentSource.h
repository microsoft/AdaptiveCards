// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ContentSource.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct AdaptiveContentSource
    {
        void InitializeContentSource(std::shared_ptr<::AdaptiveCards::ContentSource> const& sharedContentSource);

        property<hstring> MimeType;
        property<hstring> Url;
    };
}
