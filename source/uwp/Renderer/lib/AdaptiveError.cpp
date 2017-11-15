#include "pch.h"
#include "AdaptiveError.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Uwp;

namespace AdaptiveCards { namespace Uwp
{

    HRESULT AdaptiveError::RuntimeClassInitialize()
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveError::RuntimeClassInitialize(
        ABI::AdaptiveCards::Uwp::ErrorStatusCode statusCode,
        HSTRING message)
    {
        m_statusCode = statusCode;
        m_message.Set(message);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveError::get_StatusCode(ABI::AdaptiveCards::Uwp::ErrorStatusCode* value)
    {
        *value = m_statusCode;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveError::put_StatusCode(ABI::AdaptiveCards::Uwp::ErrorStatusCode value)
    {
        m_statusCode = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveError::get_Message(HSTRING* value)
    {
        return m_message.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveError::put_Message(HSTRING value)
    {
        return m_message.Set(value);
    }
}}
