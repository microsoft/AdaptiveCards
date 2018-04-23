#include "pch.h"
#include "XamlHelpers.h"
#include "HtmlHelpers.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace AdaptiveNamespace;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Documents;
using namespace ABI::Windows::UI::Xaml::Controls;

HRESULT GetXamlBasicStatics(
    ABI::Windows::UI::Xaml::IXamlBasicStatics ** xamlBasicStatics)
{
    static ComPtr<IXamlBasicStatics> s_xamlBasicStatics;

    if (s_xamlBasicStatics == nullptr)
    {
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_XamlBasic).Get(), &s_xamlBasicStatics));
    }

    return s_xamlBasicStatics.CopyTo(xamlBasicStatics);
}

HRESULT AddInlineToXamlBasicObject(
    IXamlBasicObject * basicInlines,
    IXamlBasicObject * basicInline)
{
    ComPtr<IXamlBasicStatics> xamlBasicStatics;
    GetXamlBasicStatics(&xamlBasicStatics);

    THROW_IF_FAILED(xamlBasicStatics->CollectionAdd_IXamlBasicObject(basicInlines, basicInline));

    return S_OK;
}

HRESULT GetTextFromXmlNode(
    ABI::Windows::Data::Xml::Dom::IXmlNode* node,
    HSTRING* text)
{
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> localNode = node;
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNodeSerializer> textNodeSerializer;
    RETURN_IF_FAILED(localNode.As(&textNodeSerializer));

    RETURN_IF_FAILED(textNodeSerializer->get_InnerText(text));
    return S_OK;
}

HRESULT AddListInlines(
    IAdaptiveRenderContext* renderContext,
    ABI::Windows::Data::Xml::Dom::IXmlNode* node,
    bool isListOrdered,
    IXamlBasicObject * basicInlines)
{
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNamedNodeMap> attributeMap;
    RETURN_IF_FAILED(node->get_Attributes(&attributeMap));

    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> startNode;
    RETURN_IF_FAILED(attributeMap->GetNamedItem(HStringReference(L"start").Get(), &startNode));

    int iteration = 1;
    if (startNode != nullptr)
    {
        HString start;
        RETURN_IF_FAILED(GetTextFromXmlNode(startNode.Get(), start.GetAddressOf()));
        iteration = std::stoi(HStringToUTF8(start.Get()));
    }

    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> listChild;
    RETURN_IF_FAILED(node->get_FirstChild(&listChild));

    while (listChild != nullptr)
    {
        std::wstring listElementString = L"\n";
        if (!isListOrdered)
        {
            listElementString += L"● ";
        }
        else
        {
            wchar_t buffer[10];
            swprintf_s(buffer, ARRAYSIZE(buffer), L"%d. ", iteration);

            std::wstring numberElementString(buffer);
            listElementString += numberElementString;
        }

        HString listElementHString;
        RETURN_IF_FAILED(listElementHString.Set(listElementString.c_str()));

        ComPtr<IXamlBasicStatics> xamlBasicStatics;
        GetXamlBasicStatics(&xamlBasicStatics);

        ComPtr<IXamlBasicObject> basicRun;
        THROW_IF_FAILED(xamlBasicStatics->CreateInstance_ByIndex(XamlTypeIndex_Run, &basicRun));

        xamlBasicStatics->SetValue_String_ByIndex(basicRun.Get(), XamlPropertyIndex_Run_Text, listElementHString.Get());

        AddInlineToXamlBasicObject(basicInlines, basicRun.Get());

        RETURN_IF_FAILED(AddTextInlines(renderContext, listChild.Get(), false, false, basicInlines)); 

        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextListChild;
        RETURN_IF_FAILED(listChild->get_NextSibling(&nextListChild));

        iteration++;
        listChild = nextListChild;
    }
    return S_OK;
}

HRESULT AddLinkInline(
    IAdaptiveRenderContext* renderContext,
    ABI::Windows::Data::Xml::Dom::IXmlNode* node,
    BOOL isBold,
    BOOL isItalic,
    IXamlBasicObject * basicInlines)
{
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNamedNodeMap> attributeMap;
    RETURN_IF_FAILED(node->get_Attributes(&attributeMap));

    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> hrefNode;
    RETURN_IF_FAILED(attributeMap->GetNamedItem(HStringReference(L"href").Get(), &hrefNode));

    if (hrefNode == nullptr)
    {
        return E_INVALIDARG;
    }

    HString href;
    RETURN_IF_FAILED(GetTextFromXmlNode(hrefNode.Get(), href.GetAddressOf()));

    ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
    RETURN_IF_FAILED(GetActivationFactory(
        HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(),
        &uriActivationFactory));

    ComPtr<IUriRuntimeClass> uri;
    RETURN_IF_FAILED(uriActivationFactory->CreateUri(href.Get(), uri.GetAddressOf()));

    ComPtr<IXamlBasicStatics> xamlBasicStatics;
    GetXamlBasicStatics(&xamlBasicStatics);

    ComPtr<IXamlBasicObject> basicHyperlink;
    THROW_IF_FAILED(xamlBasicStatics->CreateInstance_ByIndex(XamlTypeIndex_Hyperlink, &basicHyperlink));

    xamlBasicStatics->SetValue_Object_ByIndex(basicHyperlink.Get(), XamlPropertyIndex_Hyperlink_NavigateUri, uri.Get());

    ComPtr<IXamlBasicObject> basicHyperlinkInlines;
    THROW_IF_FAILED(xamlBasicStatics->GetXamlBasicObjectValue_ByIndex(basicHyperlink.Get(), XamlPropertyIndex_Span_Inlines, &basicHyperlinkInlines));

    RETURN_IF_FAILED(AddTextInlines(renderContext, node, isBold, isItalic, basicHyperlinkInlines.Get())); 

    AddInlineToXamlBasicObject(basicInlines, basicHyperlink.Get());

    return S_OK;
}

HRESULT AddSingleTextInline(
    IAdaptiveRenderContext* renderContext,
    HSTRING string,
    bool isBold,
    bool isItalic,
    IXamlBasicObject * basicInlines)
{
    ComPtr<IXamlBasicStatics> xamlBasicStatics;
    GetXamlBasicStatics(&xamlBasicStatics);

    ComPtr<IXamlBasicObject> basicRun;
    THROW_IF_FAILED(xamlBasicStatics->CreateInstance_ByIndex(XamlTypeIndex_Run, &basicRun));

    xamlBasicStatics->SetValue_String_ByIndex(basicRun.Get(), XamlPropertyIndex_Run_Text, string);
    
    if (isBold)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        ComPtr<IAdaptiveFontWeightsConfig> fontWeightsConfig;
        RETURN_IF_FAILED(hostConfig->get_FontWeights(&fontWeightsConfig));

        ABI::Windows::UI::Text::FontWeight boldFontWeight;
        RETURN_IF_FAILED(fontWeightsConfig->get_Bolder(&boldFontWeight.Weight));

        //RETURN_IF_FAILED(runAsTextElement->put_FontWeight(boldFontWeight)); //BECKYTODO 
    }

    if (isItalic)
    {
        //RETURN_IF_FAILED(runAsTextElement->put_FontStyle(ABI::Windows::UI::Text::FontStyle::FontStyle_Italic)); //BECKYTODO
    }

    AddInlineToXamlBasicObject(basicInlines, basicRun.Get()); 

    return S_OK;
}

HRESULT AddTextInlines(
    IAdaptiveRenderContext* renderContext,
    ABI::Windows::Data::Xml::Dom::IXmlNode* node,
    BOOL isBold,
    BOOL isItalic,
    IXamlBasicObject * basicInlines)
{
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> childNode;
    RETURN_IF_FAILED(node->get_FirstChild(&childNode));

    while (childNode != nullptr)
    {
        HString nodeName;
        RETURN_IF_FAILED(childNode->get_NodeName(nodeName.GetAddressOf()));

        INT32 isLinkResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"a").Get(), &isLinkResult));

        INT32 isBoldResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"strong").Get(), &isBoldResult));

        INT32 isItalicResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"em").Get(), &isItalicResult));

        INT32 isTextResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"#text").Get(), &isTextResult));

        if (isLinkResult == 0)
        {
            RETURN_IF_FAILED(AddLinkInline(renderContext, childNode.Get(), isBold, isItalic, basicInlines)); 
        }
        else if (isTextResult == 0)
        {
            HString text;
            RETURN_IF_FAILED(GetTextFromXmlNode(childNode.Get(), text.GetAddressOf()));
            RETURN_IF_FAILED(AddSingleTextInline(renderContext, text.Get(), isBold, isItalic, basicInlines)); 
        }
        else
        {
            RETURN_IF_FAILED(AddTextInlines(renderContext, childNode.Get(), isBold || (isBoldResult == 0), isItalic || (isItalicResult == 0), basicInlines)); 
        }

        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextChildNode;
        RETURN_IF_FAILED(childNode->get_NextSibling(&nextChildNode));
        childNode = nextChildNode;
    }

    return S_OK;
}

HRESULT AddHtmlInlines(
    IAdaptiveRenderContext* renderContext,
    ABI::Windows::Data::Xml::Dom::IXmlNode * node,
    IXamlBasicObject * basicInlines)
{
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> childNode;
    RETURN_IF_FAILED(node->get_FirstChild(&childNode));

    while (childNode != nullptr)
    {
        HString nodeName;
        RETURN_IF_FAILED(childNode->get_NodeName(nodeName.GetAddressOf()));

        INT32 isOrderedListResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"ol").Get(), &isOrderedListResult));

        INT32 isUnorderedListResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"ul").Get(), &isUnorderedListResult));

        INT32 isParagraphResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"p").Get(), &isParagraphResult));

        if ((isOrderedListResult == 0) || (isUnorderedListResult == 0))
        {
            RETURN_IF_FAILED(AddListInlines(renderContext, childNode.Get(), (isOrderedListResult == 0), basicInlines)); 
        }
        else if (isParagraphResult == 0)
        {
            RETURN_IF_FAILED(AddTextInlines(renderContext, childNode.Get(), false, false, basicInlines)); 
        }
        else
        {
            RETURN_IF_FAILED(AddHtmlInlines(renderContext, childNode.Get(), basicInlines)); 
        }

        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextChildNode;
        RETURN_IF_FAILED(childNode->get_NextSibling(&nextChildNode));
        childNode = nextChildNode;
    }
    return S_OK;
}