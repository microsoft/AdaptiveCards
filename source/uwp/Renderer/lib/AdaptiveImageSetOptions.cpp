#include "pch.h"
#include "AdaptiveHostOptions.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "XamlCardRendererComponent.h"
#include "AdaptiveImageSetOptions.h"
#include "AdaptiveImageSizeOptions.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveImageSetOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveImageSetOptions::RuntimeClassInitialize(ImageSetOptions ImageSetOptions) noexcept
    {
        m_sharedImageSetOptions = ImageSetOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSetOptions::get_ImageSize(ABI::AdaptiveCards::XamlCardRenderer::ImageSize* imageSize)
    {
        *imageSize = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ImageSize>(m_sharedImageSetOptions.imageSize);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSetOptions::put_ImageSize(ABI::AdaptiveCards::XamlCardRenderer::ImageSize imageSize)
    {
        m_sharedImageSetOptions.imageSize = static_cast<AdaptiveCards::ImageSize>(imageSize);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveImageSetOptions::get_Separation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedImageSetOptions.separation);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveImageSetOptions::put_Separation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }
}
}
