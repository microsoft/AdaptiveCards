#include "pch.h"
#include "XamlHelpers.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::Windows::UI::Xaml::Media;

namespace AdaptiveNamespace
{
    ComPtr<ABI::Windows::UI::Xaml::Media::IBrush> XamlHelpers::GetSolidColorBrush(ABI::Windows::UI::Color color)
    {
        ComPtr<ISolidColorBrush> solidColorBrush =
            XamlHelpers::CreateXamlClass<ISolidColorBrush>(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_SolidColorBrush));
        THROW_IF_FAILED(solidColorBrush->put_Color(color));
        ComPtr<IBrush> solidColorBrushAsBrush;
        THROW_IF_FAILED(solidColorBrush.As(&solidColorBrushAsBrush));
        return solidColorBrushAsBrush;
    }
}
