#include "pch.h"
#include "AdaptiveImage.h"

#include "Util.h"
#include "AdaptiveCardRendererComponent.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace Uwp
{
    AdaptiveImage::AdaptiveImage()
    {
    }

    HRESULT AdaptiveImage::RuntimeClassInitialize() noexcept try
    {
        m_sharedImage = std::make_shared<Image>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveImage::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::Image>& sharedImage)
    {
        if (sharedImage == nullptr)
        {
            return E_INVALIDARG;
        }

        m_sharedImage = sharedImage;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::get_Url(IUriRuntimeClass** url)
    {
        *url = nullptr;

        ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
        RETURN_IF_FAILED(GetActivationFactory(
            HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(),
            &uriActivationFactory));

        HSTRING imageUri;
        RETURN_IF_FAILED(UTF8ToHString(m_sharedImage->GetUrl(), &imageUri));
        RETURN_IF_FAILED(uriActivationFactory->CreateUri(imageUri, url));

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::put_Url(IUriRuntimeClass* url) try
    {
        if (url == nullptr)
        {
            return E_INVALIDARG;
        }

        HString urlTemp;
        url->get_AbsoluteUri(urlTemp.GetAddressOf());

        std::string urlString;
        RETURN_IF_FAILED(HStringToUTF8(urlTemp.Get(), urlString));
        m_sharedImage->SetUrl(urlString);

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveImage::get_Style(ABI::AdaptiveCards::Uwp::ImageStyle* imageStyle)
    {
        *imageStyle = static_cast<ABI::AdaptiveCards::Uwp::ImageStyle>(m_sharedImage->GetImageStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::put_Style(ABI::AdaptiveCards::Uwp::ImageStyle imageStyle)
    {
        m_sharedImage->SetImageStyle(static_cast<AdaptiveCards::ImageStyle>(imageStyle));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::get_Size(ABI::AdaptiveCards::Uwp::ImageSize* imageSize)
    {
        *imageSize = static_cast<ABI::AdaptiveCards::Uwp::ImageSize>(m_sharedImage->GetImageSize());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::put_Size(ABI::AdaptiveCards::Uwp::ImageSize imageSize)
    {
        m_sharedImage->SetImageSize(static_cast<AdaptiveCards::ImageSize>(imageSize));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::get_AltText(HSTRING* text)
    {
        return UTF8ToHString(m_sharedImage->GetAltText(), text);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::put_AltText(HSTRING text)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(text, out));
        m_sharedImage->SetAltText(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::get_HorizontalAlignment(ABI::AdaptiveCards::Uwp::HAlignment* alignment)
    {
        *alignment = static_cast<ABI::AdaptiveCards::Uwp::HAlignment>(m_sharedImage->GetHorizontalAlignment());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::put_HorizontalAlignment(ABI::AdaptiveCards::Uwp::HAlignment alignment)
    {
        m_sharedImage->SetHorizontalAlignment(static_cast<AdaptiveCards::HorizontalAlignment>(alignment));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::Image;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::get_Spacing(ABI::AdaptiveCards::Uwp::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::Uwp::Spacing>(m_sharedImage->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::put_Spacing(ABI::AdaptiveCards::Uwp::Spacing spacing)
    {
        m_sharedImage->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::get_Separator(boolean* separator)
    {
        *separator = m_sharedImage->GetSeparator();
        return S_OK;

        //Issue #629 to make separator an object
        //return GenerateSeparatorProjection(m_sharedImage->GetSeparator(), separator);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::put_Separator(boolean separator)
    {
        m_sharedImage->SetSeparator(separator);

        /*Issue #629 to make separator an object
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedImage->SetSeparator(sharedSeparator);
        */

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedImage->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedImage->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImage::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }
}}
