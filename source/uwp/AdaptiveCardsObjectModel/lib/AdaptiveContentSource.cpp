// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveContentSource.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    void AdaptiveContentSource::InitializeContentSource(const std::shared_ptr<::AdaptiveCards::ContentSource>& sharedContentSource)
    {
        MimeType = UTF8ToHString(sharedContentSource->GetMimeType());
        Url = UTF8ToHString(sharedContentSource->GetUrl());
    }
}
