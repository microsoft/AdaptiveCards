#include "pch.h"
#include "ImageRenderResult.h"

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveSharedNamespace::XamlCardRenderer;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Storage::Streams;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    _Use_decl_annotations_
    HRESULT ImageRenderResult::RuntimeClassInitialize(HSTRING altText, IBuffer* pixelBuffer, int width, int height)
    {
        m_altText.Attach(altText);
        m_pixelBuffer = pixelBuffer;
        m_pixelWidth = width;
        m_pixelHeight = height;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT ImageRenderResult::get_AltText(HSTRING* altText)
    {
        return m_altText.CopyTo(altText);
    }

    _Use_decl_annotations_
    HRESULT ImageRenderResult::get_ImageBuffer(ABI::Windows::Storage::Streams::IBuffer** imageBuffer)
    {
        return m_pixelBuffer.CopyTo(imageBuffer);
    }

    _Use_decl_annotations_
    HRESULT ImageRenderResult::get_IsAllContentClippedOut(boolean* /*allContentClipped*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT ImageRenderResult::get_ImageWidthPixels(int* width)
    {
        *width = m_pixelWidth;
        return S_OK;
    }
    
    _Use_decl_annotations_
    HRESULT ImageRenderResult::get_ImageHeightPixels(int* height)
    {
        *height = m_pixelHeight;
        return S_OK;
    }

}}
