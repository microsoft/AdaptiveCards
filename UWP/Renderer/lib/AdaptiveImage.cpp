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
    AdaptiveImage::AdaptiveImage()
    {
        m_size = ABI::AdaptiveCards::XamlCardRenderer::CardElementSize::Auto;
    }

    HRESULT AdaptiveImage::RuntimeClassInitialize() noexcept try
    {
        m_sharedImage = std::make_shared<Image>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveImage::RuntimeClassInitialize(std::shared_ptr<AdaptiveCards::Image> sharedImage)
    {
        m_sharedImage = sharedImage;
        return S_OK;
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
        RETURN_IF_FAILED(UTF8ToHString(m_sharedImage->GetUri(), &imageUri));
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
        m_sharedImage->SetUri(uriString);

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveImage::get_ImageStyle(ABI::AdaptiveCards::XamlCardRenderer::ImageStyle* ImageStyle)
    {
        *ImageStyle = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ImageStyle>(m_sharedImage->GetImageStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::put_ImageStyle(ABI::AdaptiveCards::XamlCardRenderer::ImageStyle ImageStyle)
    {
        m_sharedImage->SetImageStyle(static_cast<AdaptiveCards::ImageStyle>(ImageStyle));
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
    HRESULT AdaptiveImage::get_Size(ABI::AdaptiveCards::XamlCardRenderer::CardElementSize* size)
    {
        *size = m_size;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::put_Size(ABI::AdaptiveCards::XamlCardRenderer::CardElementSize size)
    {
        m_size = size;
        return S_OK;
    }

}}
