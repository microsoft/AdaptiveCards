#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

AdaptiveNamespaceStart
    class XamlHelpers
    {
    public:
        template<typename T>
        static Microsoft::WRL::ComPtr<T> CreateXamlClass(_In_ Microsoft::WRL::Wrappers::HStringReference className)
        {
            Microsoft::WRL::ComPtr<IInspectable> inspectableClass;
            THROW_IF_FAILED(RoActivateInstance(className.Get(), inspectableClass.ReleaseAndGetAddressOf()));

            Microsoft::WRL::ComPtr<T> result;
            THROW_IF_FAILED(inspectableClass.As<T>(&result));
            return result;
        }

        template<typename T, typename C>
        static void IterateOverVector(
            ABI::Windows::Foundation::Collections::IVector<T*>* vector,
            C iterationCallback)
        {
            Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<T*>> localVector(vector);
            ComPtr<IIterable<T*>> vectorIterable;
            THROW_IF_FAILED(localVector.As<IIterable<T*>>(&vectorIterable));

            Microsoft::WRL::ComPtr<IIterator<T*>> vectorIterator;
            if (FAILED(vectorIterable->First(&vectorIterator)))
            {
                return;
            }

            boolean hasCurrent = false;
            HRESULT hr = vectorIterator->get_HasCurrent(&hasCurrent);
            while (SUCCEEDED(hr) && hasCurrent)
            {
                Microsoft::WRL::ComPtr<T> current = nullptr;
                hr = vectorIterator->get_Current(&current);
                if (FAILED(hr))
                {
                    break;
                }

                iterationCallback(current.Get());
                hr = vectorIterator->MoveNext(&hasCurrent);
            }
        }

        template<typename T>
        static void AppendXamlElementToPanel(
            T* xamlElement,
            ABI::Windows::UI::Xaml::Controls::IPanel* panel)
        {
            if (!xamlElement)
            {
                return;
            }

            Microsoft::WRL::ComPtr<T> localXamlElement(xamlElement);

            ComPtr<IUIElement> elementToAppend;
            THROW_IF_FAILED(localXamlElement.As(&elementToAppend));

            ComPtr<IVector<UIElement*>> panelChildren;
            THROW_IF_FAILED(panel->get_Children(panelChildren.ReleaseAndGetAddressOf()));

            THROW_IF_FAILED(panelChildren->Append(elementToAppend.Get()));
        }

        template<typename T>
        static void SetToggleValue(
            T* item,
            boolean isChecked)
        {
            ComPtr<IPropertyValueStatics> propertyValueStatics;
            ABI::Windows::Foundation::GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_PropertyValue).Get(), &propertyValueStatics);

            ComPtr<IPropertyValue> propertyValue;
            propertyValueStatics->CreateBoolean(isChecked, &propertyValue);

            ComPtr<ABI::Windows::Foundation::IReference<bool>> boolProperty;
            propertyValue.As(&boolProperty);

            ComPtr<T> localItem(item);
            ComPtr<IToggleButton> toggleButton;
            THROW_IF_FAILED(localItem.As(&toggleButton));
            THROW_IF_FAILED(toggleButton->put_IsChecked(boolProperty.Get()));
        }

        template<typename T>
        static void GetToggleValue(
            T* item,
            boolean* isChecked)
        {
            ComPtr<T> localItem(item);
            ComPtr<IToggleButton> toggleButton;
            THROW_IF_FAILED(localItem.As(&toggleButton));

            ComPtr<IReference<bool>> isCheckedReference;
            THROW_IF_FAILED(toggleButton->get_IsChecked(&isCheckedReference));

            if (isCheckedReference != nullptr)
            {
                THROW_IF_FAILED(isCheckedReference->get_Value(isChecked));
            }
            else
            {
                *isChecked = false;
            }
        }

        template<typename T>
        static void SetContent(
            T* item,
            HSTRING contentString)
        {
            ComPtr<T> localItem(item);
            ComPtr<IContentControl> contentControl;
            THROW_IF_FAILED(localItem.As(&contentControl));

            ComPtr<ITextBlock> content = XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
            THROW_IF_FAILED(content->put_Text(contentString));
            THROW_IF_FAILED(contentControl->put_Content(content.Get()));
        }

        template<typename T>
        static void AddRow(
            T* item,
            ABI::Windows::UI::Xaml::Controls::IGrid* grid,
            ABI::Windows::UI::Xaml::GridLength rowHeight)
        {
            ComPtr<ABI::Windows::UI::Xaml::Controls::IGrid> localGrid(grid);

            ComPtr<IVector<RowDefinition*>> rowDefinitions;
            THROW_IF_FAILED(localGrid->get_RowDefinitions(&rowDefinitions));

            unsigned int rowIndex;
            THROW_IF_FAILED(rowDefinitions->get_Size(&rowIndex));
            ComPtr<IGridStatics> gridStatics;
            THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));
            Microsoft::WRL::ComPtr<T> localItem(item);
            ComPtr<IFrameworkElement> localItemAsFrameworkElement;
            THROW_IF_FAILED(localItem.As(&localItemAsFrameworkElement));
            gridStatics->SetRow(localItemAsFrameworkElement.Get(), rowIndex);

            ComPtr<IRowDefinition> rowDefinition = XamlHelpers::CreateXamlClass<IRowDefinition>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RowDefinition));
            THROW_IF_FAILED(rowDefinition->put_Height(rowHeight));
            THROW_IF_FAILED(rowDefinitions->Append(rowDefinition.Get()));

            ComPtr<ABI::Windows::UI::Xaml::Controls::IPanel> localPanel;
            THROW_IF_FAILED(localGrid.As(&localPanel));
            XamlHelpers::AppendXamlElementToPanel(item, localPanel.Get());
        }
    };
AdaptiveNamespaceEnd