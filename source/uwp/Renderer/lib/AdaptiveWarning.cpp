#include "pch.h"
#include "AdaptiveWarning.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Uwp;

namespace AdaptiveCards { namespace Uwp
{

    HRESULT AdaptiveWarning::RuntimeClassInitialize()
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveWarning::RuntimeClassInitialize(
        ABI::AdaptiveCards::Uwp::WarningStatusCode statusCode,
        HSTRING message)
    {
        m_statusCode = statusCode;
        m_message.Set(message);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveWarning::get_StatusCode(ABI::AdaptiveCards::Uwp::WarningStatusCode* value)
    {
        *value = m_statusCode;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveWarning::put_StatusCode(ABI::AdaptiveCards::Uwp::WarningStatusCode value)
    {
        m_statusCode = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveWarning::get_Message(HSTRING* value)
    {
        return m_message.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveWarning::put_Message(HSTRING value)
    {
        return m_message.Set(value);
    }
}}
