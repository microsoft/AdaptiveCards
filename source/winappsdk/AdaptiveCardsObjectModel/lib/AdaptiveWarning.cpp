#include "pch.h"
#include "AdaptiveWarning.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    AdaptiveWarning::AdaptiveWarning(winrt::AdaptiveCards::ObjectModel::WinUI3::WarningStatusCode const& statusCode, hstring const& message) :
        StatusCode{statusCode}, Message{message}
    {
        throw hresult_not_implemented();
    }
}
