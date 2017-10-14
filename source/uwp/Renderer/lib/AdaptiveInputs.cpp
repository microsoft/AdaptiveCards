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
using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace Uwp
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
    HRESULT AdaptiveInputs::AsJson(InputValueMode inputMode, IJsonObject** value)
    {
        std::string inputItemsAsString;
        switch (inputMode)
        {
        case InputValueMode::RawString:
        default:
            inputItemsAsString = GetInputItemsAsJsonString();
            break;
        }

        return StringToJsonObject(inputItemsAsString, value);
    }

    std::shared_ptr<std::vector<InputItem>> AdaptiveInputs::GetInputItems()
    {
        return m_inputItems;
    }

    std::string AdaptiveInputs::GetInputItemsAsJsonString()
    {
        Json::Value jsonValue;
        for (auto& inputElement : *m_inputItems)
        {
            std::string key = inputElement.GetIdString();
            std::string value = inputElement.Serialize();
            jsonValue[key] = value;
        }

        Json::StreamWriterBuilder writerBuilder;
        std::unique_ptr<Json::StreamWriter> writer(writerBuilder.newStreamWriter());
        std::ostringstream outStream;
        writer->write(jsonValue, &outStream);
        return outStream.str();
    }

    _Use_decl_annotations_
    HRESULT AdaptiveInputs::AsValueSet(IPropertySet** value)
    {
        *value = nullptr;
        ComPtr<IPropertySet> valueSet;
        RETURN_IF_FAILED(ActivateInstance(HStringReference(RuntimeClass_Windows_Foundation_Collections_ValueSet).Get(), &valueSet));
        ComPtr<IMap<HSTRING, IInspectable*>> propertySetMap;
        RETURN_IF_FAILED(valueSet.As(&propertySetMap));

        ComPtr<IPropertyValueStatics> propertyValueFactory;
        RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_PropertyValue).Get(), &propertyValueFactory));

        ComPtr<IInspectable> propVal;
        boolean replaced;
        for (auto& inputElement : *m_inputItems)
        {
            HSTRING key = inputElement.GetId();
            std::string value = inputElement.Serialize();
            HSTRING valueHstring;
            RETURN_IF_FAILED(UTF8ToHString(value, &valueHstring));
            RETURN_IF_FAILED(propertyValueFactory->CreateString(valueHstring, propVal.ReleaseAndGetAddressOf()));
            RETURN_IF_FAILED(propertySetMap->Insert(key, propVal.Get(), &replaced));
        }
        return valueSet.CopyTo(value);
    }

}}