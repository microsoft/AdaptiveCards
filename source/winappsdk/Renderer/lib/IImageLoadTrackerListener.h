// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::WinUI3
{
    struct DECLSPEC_UUID("D940E878-F2E0-4AF7-A844-4D090C7379E3") IImageLoadTrackerListener
        : public winrt::Windows::Foundation::IInspectable
    {
    public:
        const virtual void AllImagesLoaded();
        const virtual void ImagesLoadingHadError();
    };

}
