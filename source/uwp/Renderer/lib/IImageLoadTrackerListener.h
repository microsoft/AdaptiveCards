// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    MIDL_INTERFACE("D940E878-F2E0-4AF7-A844-4D090C7379E3")
    IImageLoadTrackerListener : public IInspectable
    {
    public:
        IFACEMETHOD(AllImagesLoaded)() = 0;
        IFACEMETHOD(ImagesLoadingHadError)() = 0;
    };

}
