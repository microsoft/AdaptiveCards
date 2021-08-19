#include "pch.h"
#include "AdaptiveAuthCardButton.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    AdaptiveAuthCardButton::AdaptiveAuthCardButton(std::shared_ptr<::AdaptiveCards::AuthCardButton> const& sharedAuthCardButton)
    {
        Type = UTF8ToHString(sharedAuthCardButton->GetType());
        Title = UTF8ToHString(sharedAuthCardButton->GetTitle());
        Image = UTF8ToHString(sharedAuthCardButton->GetImage());
        Value = UTF8ToHString(sharedAuthCardButton->GetValue());
    }

    std::shared_ptr<::AdaptiveCards::AuthCardButton> AdaptiveAuthCardButton::GetSharedModel()
    {
        auto authCardButton = std::make_shared<::AdaptiveCards::AuthCardButton>();
        authCardButton->SetType(HStringToUTF8(Type));
        authCardButton->SetTitle(HStringToUTF8(Title));
        authCardButton->SetImage(HStringToUTF8(Image));
        authCardButton->SetValue(HStringToUTF8(Value));
        return authCardButton;
    }

}
