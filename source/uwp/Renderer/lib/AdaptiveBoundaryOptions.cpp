#include "pch.h"
#include "AdaptiveHostOptions.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "XamlCardRendererComponent.h"
#include "AdaptiveBoundaryOptions.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards {
    namespace XamlCardRenderer
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
        HRESULT AdaptiveBoundaryOptions::get_Left(INT32* left)
        {
            *left = m_sharedBoundaryOptions.left;
            return S_OK;
        }

        _Use_decl_annotations_
        HRESULT AdaptiveBoundaryOptions::put_Left(INT32 left)
        {
            m_sharedBoundaryOptions.left = left;
            return S_OK;
        }

        _Use_decl_annotations_
        HRESULT AdaptiveBoundaryOptions::get_Right(INT32* right)
        {
            *right = m_sharedBoundaryOptions.right;
            return S_OK;
        }

        _Use_decl_annotations_
        HRESULT AdaptiveBoundaryOptions::put_Right(INT32 right)
        {
            m_sharedBoundaryOptions.left = right;
            return S_OK;
        }

        _Use_decl_annotations_
        HRESULT AdaptiveBoundaryOptions::get_Bottom(INT32* bottom)
        {
            *bottom = m_sharedBoundaryOptions.bottom;
            return S_OK;
        }

        _Use_decl_annotations_
        HRESULT AdaptiveBoundaryOptions::put_Bottom(INT32 bottom)
        {
            m_sharedBoundaryOptions.bottom = bottom;
            return S_OK;
        }

        _Use_decl_annotations_
        HRESULT AdaptiveBoundaryOptions::get_Top(INT32* top)
        {
            *top = m_sharedBoundaryOptions.top;
            return S_OK;
        }

        _Use_decl_annotations_
        HRESULT AdaptiveBoundaryOptions::put_Top(INT32 top)
        {
            m_sharedBoundaryOptions.top = top;
            return S_OK;
        }
    }
}
