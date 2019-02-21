#pragma once

#include "pch.h"
#include "BaseCardElement.h"

namespace AdaptiveSharedNamespace
{
    class CollectionTypeElement : public BaseCardElement
    {
    public:
        CollectionTypeElement(const CollectionTypeElement&) = default;
        CollectionTypeElement(CollectionTypeElement&&) = default;
        CollectionTypeElement& operator=(const CollectionTypeElement&) = default;
        CollectionTypeElement& operator=(CollectionTypeElement&&) = default;
        ~CollectionTypeElement() = default;
        CollectionTypeElement(CardElementType type, ContainerStyle style = ContainerStyle::None,
            VerticalContentAlignment alignment = VerticalContentAlignment::Top);

        ContainerStyle GetStyle() const;
        void SetStyle(const ContainerStyle value);

        VerticalContentAlignment GetVerticalContentAlignment() const;
        void SetVerticalContentAlignment(const VerticalContentAlignment value);

        bool GetPadding() const;
        void SetPadding(const bool value);

        bool GetBleed() const;
        void SetBleed(const bool value);
        // tells if current element can bleed 
        // when GetCanBleed() return false and GetBleed() returns true 
        // the user must also check if HostConfig has
        // padding for card, the root, if the padding is allowed,
        // the user has to interpret the returned value correctly
        bool GetCanBleed() const;
        // configures container style related attributes
        // such as style, padding and bleed
        void ConfigForContainerStyle(const AdaptiveCards::ParseContext& context);

        void SetParentalId(const AdaptiveSharedNamespace::InternalId &id);
        AdaptiveSharedNamespace::InternalId GetParentalId(void) const;

        std::shared_ptr<BaseActionElement> GetSelectAction() const;
        void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

        Json::Value SerializeToJsonValue() const override;

    private:
        void SetCanBleed(const bool value);

        // Applies padding flag When appropriate
        void ConfigPadding(const AdaptiveCards::ParseContext& context);
        // Applies bleed flag when appropriate
        void ConfigBleed(const AdaptiveCards::ParseContext& context);

        ContainerStyle m_style;
        VerticalContentAlignment m_verticalContentAlignment;
        bool m_hasPadding;
        bool m_hasBleed;
        bool m_canBleed;
        // id refers to parent to where bleed property should target
        AdaptiveSharedNamespace::InternalId m_parentalId;

        std::shared_ptr<BaseActionElement> m_selectAction;
    };
}
