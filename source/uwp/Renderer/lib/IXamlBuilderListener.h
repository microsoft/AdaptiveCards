#pragma once

AdaptiveNamespaceStart

MIDL_INTERFACE("BF58F7BB-A330-4C75-AF7F-6E5FD8C0C070")
IXamlBuilderListener : public IInspectable
{
public:
    IFACEMETHOD(AllImagesLoaded)() = 0;
    IFACEMETHOD(ImagesLoadingHadError)() = 0;
    IFACEMETHOD(XamlBuilderHadError)() = 0;
};

AdaptiveNamespaceEnd