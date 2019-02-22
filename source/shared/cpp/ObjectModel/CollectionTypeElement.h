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
        // the renderer must also check if HostConfig has
        // padding for card, the root, if the padding is allowed,
        // then the element can bleed to the card
        bool GetCanBleed() const;
        // configures container style related attributes
        // such as style, padding and bleed
        void ConfigForContainerStyle(const AdaptiveCards::ParseContext& context);

        void SetParentalId(const AdaptiveSharedNamespace::InternalId &id);
        AdaptiveSharedNamespace::InternalId GetParentalId(void) const;

        std::shared_ptr<BaseActionElement> GetSelectAction() const;
        void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

        virtual void DeserializeChildren(ParseContext& context, const Json::Value& value) = 0;

        Json::Value SerializeToJsonValue() const override;
        template<typename T> static std::shared_ptr<T> Deserialize(ParseContext& context, const Json::Value& value);

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

    template<typename T>
    std::shared_ptr<T> CollectionTypeElement::Deserialize(ParseContext& context, const Json::Value& value)
    {
        auto collection = BaseCardElement::Deserialize<T>(context, value);
        collection->SetStyle(
            ParseUtil::GetEnumValue<ContainerStyle>(value, AdaptiveCardSchemaKey::Style, ContainerStyle::None, ContainerStyleFromString));

        collection->SetVerticalContentAlignment(ParseUtil::GetEnumValue<VerticalContentAlignment>(
            value, AdaptiveCardSchemaKey::VerticalContentAlignment, VerticalContentAlignment::Top, VerticalContentAlignmentFromString));

        collection->SetBleed(ParseUtil::GetBool(value, AdaptiveCardSchemaKey::Bleed, false));

        // configures for cotainer style
        collection->ConfigForContainerStyle(context);

        // we walk parse tree dfs, so we need to save current style,
        // before we walk back up to a parent.
        context.SaveContextForCollectionTypeElement(collection);

        // Parse Items
        collection->DeserializeChildren(context, value);

        // since we are walking dfs, we have to restore the style before we back up
        context.RestoreContextForCollectionTypeElement(collection);

        // Parse optional selectAction
        collection->SetSelectAction(ParseUtil::GetAction(context, value, AdaptiveCardSchemaKey::SelectAction, false));

        return collection;
    }
}
