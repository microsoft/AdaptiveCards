#include "pch.h"
#include "AdaptiveSpacingDefinition.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveSpacingDefinition::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveSpacingDefinition::RuntimeClassInitialize(SpacingDefinition spacingDefinition) noexcept
    {
        m_sharedSpacingDefinition = spacingDefinition;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingDefinition::get_Left(UINT32* left)
    {
        *left = m_sharedSpacingDefinition.left;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingDefinition::put_Left(UINT32 left)
    {
        m_sharedSpacingDefinition.left = left;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingDefinition::get_Right(UINT32* right)
    {
        *right = m_sharedSpacingDefinition.right;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingDefinition::put_Right(UINT32 right)
    {
        m_sharedSpacingDefinition.left = right;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingDefinition::get_Bottom(UINT32* bottom)
    {
        *bottom = m_sharedSpacingDefinition.bottom;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingDefinition::put_Bottom(UINT32 bottom)
    {
        m_sharedSpacingDefinition.bottom = bottom;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingDefinition::get_Top(UINT32* top)
    {
        *top = m_sharedSpacingDefinition.top;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSpacingDefinition::put_Top(UINT32 top)
    {
        m_sharedSpacingDefinition.top = top;
        return S_OK;
    }
}
}
