#include "pch.h"
#include "AdaptiveImage.h"
#include "Util.h"
#include "XamlCardRendererComponent.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    AdaptiveImage::AdaptiveImage() : m_image(std::make_unique<Image>())
    {
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::get_Uri(IUriRuntimeClass** uri)
    {
        *uri= nullptr;

        ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
        RETURN_IF_FAILED(GetActivationFactory(
            HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(),
            &uriActivationFactory));

        HSTRING imageUri;
        RETURN_IF_FAILED(UTF8ToHString(m_image->GetUri(), &imageUri));
        RETURN_IF_FAILED(uriActivationFactory->CreateUri(imageUri, uri));

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::put_Uri(IUriRuntimeClass* uri) try
    {
        if (uri == nullptr)
        {
            return E_INVALIDARG;
        }

        HString uriTemp;
        uri->get_AbsoluteUri(uriTemp.GetAddressOf());

        std::string uriString;
        RETURN_IF_FAILED(HStringToUTF8(uriTemp.Get(), uriString));
        m_image->SetUri(uriString);

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveImage::get_ImageStyle(ABI::AdaptiveCards::XamlCardRenderer::ImageStyle* ImageStyle)
    {
        *ImageStyle = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ImageStyle>(m_image->GetImageStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::put_ImageStyle(ABI::AdaptiveCards::XamlCardRenderer::ImageStyle ImageStyle)
    {
        m_image->SetImageStyle(static_cast<AdaptiveCards::ImageStyle>(ImageStyle));
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveImage::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::Image;
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveImage::put_ElementType(ElementType /*elementType*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveImage::Render(IUIElement** /*image*/)
    {
        return S_OK;
    }
}}
