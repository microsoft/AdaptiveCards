#include "pch.h"
#include "AdaptiveFailure.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Uwp;

namespace AdaptiveCards { namespace Uwp
{

    HRESULT AdaptiveFailure::RuntimeClassInitialize()
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFailure::RuntimeClassInitialize(
        ABI::AdaptiveCards::Uwp::FailureStatusCode FailureStatusCode,
        HSTRING message)
    {
        m_FailureStatusCode = FailureStatusCode;
        m_message.Set(message);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFailure::get_FailureStatusCode(ABI::AdaptiveCards::Uwp::FailureStatusCode* value)
    {
        *value = m_FailureStatusCode;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFailure::put_FailureStatusCode(ABI::AdaptiveCards::Uwp::FailureStatusCode value)
    {
        m_FailureStatusCode = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFailure::get_Message(HSTRING* value)
    {
        return m_message.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFailure::put_Message(HSTRING value)
    {
        return m_message.Set(value);
    }
}}
