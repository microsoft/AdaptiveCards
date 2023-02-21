// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Xaml_Rendering
{
    MIDL_INTERFACE("BF58F7BB-A330-4C75-AF7F-6E5FD8C0C070")
    IXamlBuilderListener : public ::IUnknown
    {
    public:
        virtual void AllImagesLoaded() = 0;
        virtual void ImagesLoadingHadError() = 0;
        virtual void XamlBuilderHadError() = 0;
    };

}
