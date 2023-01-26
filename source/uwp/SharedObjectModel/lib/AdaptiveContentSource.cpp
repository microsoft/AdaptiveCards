// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveContentSource.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    void AdaptiveContentSource::InitializeContentSource(std::shared_ptr<::AdaptiveCards::ContentSource> const& sharedContentSource)
    {
        MimeType = UTF8ToHString(sharedContentSource->GetMimeType());
        Url = UTF8ToHString(sharedContentSource->GetUrl());
    }
}
