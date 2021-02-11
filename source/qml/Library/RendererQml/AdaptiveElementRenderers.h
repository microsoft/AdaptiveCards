#pragma once

#include "pch.h"

namespace RendererQml
{

    template <class TUIElement, class TContext> class AdaptiveElementRenderers
    {
    public:
        using ElementRendererFunction = std::function<std::shared_ptr<TUIElement>(std::shared_ptr<AdaptiveCards::BaseElement>, std::shared_ptr<TContext>)>;

        AdaptiveElementRenderers()
        {
        }

        template <class TElement>
        void Set(std::function<std::shared_ptr<TUIElement>(std::shared_ptr<TElement>, std::shared_ptr<TContext>)> renderer)
        {
            if (!std::is_assignable<AdaptiveCards::BaseElement, TElement>::value)
            {
                throw std::invalid_argument("Type of method template must inherit from AdaptiveCards::BaseElement");
            }
            m_dictionary[typeid(TElement)] = [renderer](std::shared_ptr<AdaptiveCards::BaseElement> element, std::shared_ptr<TContext> context) { return renderer(std::dynamic_pointer_cast<TElement>(element), context); };
        }

        template <class TElement>
        void Remove()
        {
            m_dictionary.erase(typeid(TElement));
        }

        template <class TElement>
        ElementRendererFunction Get()
        {
            return Get(typeid(TElement), std::is_assignable<AdaptiveCards::BaseActionElement, TElement>::value);
        }

        ElementRendererFunction Get(std::type_index type, bool isBaseActionElement)
        {
            auto iter = m_dictionary.find(type);
            if (iter != m_dictionary.end())
            {
                return iter->second;
            }

            if (isBaseActionElement)
            {
                auto iter = m_dictionary.find(typeid(AdaptiveCards::BaseActionElement));
                if (iter != m_dictionary.end())
                {
                    return iter->second;
                }
            }

            throw std::invalid_argument(Formatter() << "Unable to locate renderer for " << type.name());
        }

    private:
        std::unordered_map<std::type_index, ElementRendererFunction> m_dictionary;
    };

}
