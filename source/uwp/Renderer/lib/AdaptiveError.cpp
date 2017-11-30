#include "pch.h"
#include "AdaptiveError.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{

    HRESULT AdaptiveError::RuntimeClassInitialize()
    {
        return S_OK;
    }

    HRESULT AdaptiveError::RuntimeClassInitialize(
        ABI::AdaptiveCards::Rendering::Uwp::ErrorStatusCode statusCode,
        HSTRING message)
    {
        m_statusCode = statusCode;
        m_message.Set(message);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveError::get_StatusCode(ABI::AdaptiveCards::Rendering::Uwp::ErrorStatusCode* value)
    {
        *value = m_statusCode;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveError::put_StatusCode(ABI::AdaptiveCards::Rendering::Uwp::ErrorStatusCode value)
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
}}}
