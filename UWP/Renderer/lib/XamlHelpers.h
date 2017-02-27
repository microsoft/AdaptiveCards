#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
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
            Microsoft::WRL::ComPtr<T> localXamlElement(xamlElement);

            ComPtr<IUIElement> elementToAppend;
            THROW_IF_FAILED(localXamlElement.As(&elementToAppend));

            ComPtr<IVector<UIElement*>> panelChildren;
            THROW_IF_FAILED(panel->get_Children(panelChildren.ReleaseAndGetAddressOf()));

            THROW_IF_FAILED(panelChildren->Append(xamlElement));
        }
    };

}}