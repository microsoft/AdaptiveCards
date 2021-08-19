#include "pch.h"
#include "AdaptiveError.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    AdaptiveError::AdaptiveError(winrt::AdaptiveCards::ObjectModel::WinUI3::ErrorStatusCode const& statusCode, hstring const& message)
        : Message{message}, StatusCode{statusCode}
    {
    }
}
