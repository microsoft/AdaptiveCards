#include "pch.h"
#include "AdaptiveInputs.h"

#include "AdaptiveCard.h"
#include "AsyncOperations.h"
#include <windows.foundation.collections.h>
#include <Windows.UI.Xaml.h>
#include "XamlHelpers.h"

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    AdaptiveInputs::AdaptiveInputs()
    {
        m_inputItems = std::make_shared<std::vector<InputItem>>();
    }

    HRESULT AdaptiveInputs::RuntimeClassInitialize() noexcept
    {
        m_inputItems = std::make_shared<std::vector<InputItem>>();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputs::get_AsJson(IJsonObject** value)
    {
        std::string inputItemsAsString = InputItem::InputItemCollectionAsJsonString(*m_inputItems);
        return StringToJsonObject(inputItemsAsString, value);
    }

    std::shared_ptr<std::vector<InputItem>> AdaptiveInputs::GetInputItems()
    {
        return m_inputItems;
    }



}}