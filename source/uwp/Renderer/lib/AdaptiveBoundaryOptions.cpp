#include "pch.h"
#include "AdaptiveBoundaryOptions.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveBoundaryOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveBoundaryOptions::RuntimeClassInitialize(BoundaryOptions boundaryOptions) noexcept
    {
        m_sharedBoundaryOptions = boundaryOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveBoundaryOptions::get_Left(UINT32* left)
    {
        *left = m_sharedBoundaryOptions.left;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveBoundaryOptions::put_Left(UINT32 left)
    {
        m_sharedBoundaryOptions.left = left;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveBoundaryOptions::get_Right(UINT32* right)
    {
        *right = m_sharedBoundaryOptions.right;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveBoundaryOptions::put_Right(UINT32 right)
    {
        m_sharedBoundaryOptions.left = right;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveBoundaryOptions::get_Bottom(UINT32* bottom)
    {
        *bottom = m_sharedBoundaryOptions.bottom;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveBoundaryOptions::put_Bottom(UINT32 bottom)
    {
        m_sharedBoundaryOptions.bottom = bottom;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveBoundaryOptions::get_Top(UINT32* top)
    {
        *top = m_sharedBoundaryOptions.top;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveBoundaryOptions::put_Top(UINT32 top)
    {
        m_sharedBoundaryOptions.top = top;
        return S_OK;
    }
}
}
