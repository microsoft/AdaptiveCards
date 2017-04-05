#pragma once

namespace AdaptiveCards { namespace XamlCardRenderer
{

MIDL_INTERFACE("BF58F7BB-A330-4C75-AF7F-6E5FD8C0C070")
IXamlBuilderListener : public IInspectable
{
public:
    IFACEMETHOD(AllImagesLoaded)() = 0;
};

}}