#include "pch.h"
#include "util.h"
#include <locale>
#include <codecvt>
#include <string>

#include "AdaptiveTextBlock.h"
#include "AdaptiveImage.h"
#include "AdaptiveImageSet.h"
#include "AdaptiveContainer.h"
#include "AdaptiveColumn.h"
#include "AdaptiveColumnSet.h"
#include "AdaptiveFact.h"
#include "AdaptiveFactSet.h"
#include "AdaptiveInputDate.h"
#include "AdaptiveInputText.h"
#include "AdaptiveInputTime.h"
#include "AdaptiveInputToggle.h"

using namespace AdaptiveCards;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::Windows::UI;
using namespace std;

HRESULT UTF8ToHString(const string& in, HSTRING* out)
{
    if (out == nullptr)
    {
        return E_INVALIDARG;
    }
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    wstring wide = converter.from_bytes(in);
    return WindowsCreateString(wide.c_str(), static_cast<UINT32>(wide.length()), out);
}

HRESULT HStringToUTF8(const HSTRING& in, string& out)
{
    if (in == nullptr)
    {
        return E_INVALIDARG;
    }
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    out = converter.to_bytes(WindowsGetStringRawBuffer(in, nullptr));
    return S_OK;
}

bool Boolify(const boolean value)
{
    return value > 0 ? true : false;
}

HRESULT GenerateContainedElementsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement> projectedContainedElement;
        switch(containedElement->GetElementType())
        {
        case CardElementType::TextBlock:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveTextBlock>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::TextBlock>(containedElement)));
            break;
        case CardElementType::Image:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveImage>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::Image>(containedElement)));
            break;
        case CardElementType::Container:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveContainer>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::Container>(containedElement)));
            break;
        case CardElementType::ColumnSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveColumnSet>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::ColumnSet>(containedElement)));
            break;
        case CardElementType::FactSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveFactSet>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::FactSet>(containedElement)));
            break;
        case CardElementType::ImageSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveImageSet>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::ImageSet>(containedElement)));
            break;
        case CardElementType::InputDate:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveInputDate>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::InputDate>(containedElement)));
            break;
        case CardElementType::InputText:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveInputText>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::InputText>(containedElement)));
            break;
        case CardElementType::InputTime:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveInputTime>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::InputTime>(containedElement)));
            break;
        case CardElementType::InputToggle:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveInputToggle>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::InputToggle>(containedElement)));
            break;
        default:
            return E_UNEXPECTED;
            break;
        }
        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateColumnsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Column>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveColumn>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveCards::Column>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateFactsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Fact>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveFact>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveCards::Fact>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateImagesProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Image>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveImage>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveCards::Image>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GetColorFromString(std::string colorString, Color *color)
{
    std::string alphaString = colorString.substr(1, 2);
    INT32 alpha = strtol(alphaString.c_str(), nullptr, 16);

    std::string redString = colorString.substr(3, 2);
    INT32 red = strtol(redString.c_str(), nullptr, 16);

    std::string blueString = colorString.substr(5, 2);
    INT32 blue = strtol(blueString.c_str(), nullptr, 16);

    std::string greenString = colorString.substr(7, 2);
    INT32 green = strtol(greenString.c_str(), nullptr, 16);

    color->A = alpha;
    color->R = red;
    color->B = blue;
    color->G = green;

    return S_OK;
}