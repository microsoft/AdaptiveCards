// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BackgroundImage.h"
#include "BaseCardElement.h"
#include "CollectionCoreElement.h"
#include "Util.h"

namespace AdaptiveCards
{
    class StyledCollectionElement : public CollectionCoreElement
    {
    public:
        StyledCollectionElement(const StyledCollectionElement&) = default;
        StyledCollectionElement(StyledCollectionElement&&) = default;
        StyledCollectionElement& operator=(const StyledCollectionElement&) = default;
        StyledCollectionElement& operator=(StyledCollectionElement&&) = default;
        ~StyledCollectionElement() = default;
        StyledCollectionElement(CardElementType type,
                                ContainerStyle style = ContainerStyle::None,
                                std::optional<VerticalContentAlignment> alignment = std::nullopt);

        ContainerStyle GetStyle() const;
        void SetStyle(const ContainerStyle value);

        std::optional<VerticalContentAlignment> GetVerticalContentAlignment() const;
        void SetVerticalContentAlignment(const std::optional<VerticalContentAlignment> value);

        bool GetPadding() const;
        void SetPadding(const bool value);

        bool GetBleed() const;
        void SetBleed(const bool value);
        // tells if current element can bleed
        // when GetCanBleed() return true
        // Can Bleed
        // To find the direction of the bleed
        // Call GetBleedDirection()
        // the renderer must also check if HostConfig has
        // padding for card, the root, if the padding is allowed,
        // then the element can bleed to the card
        bool GetCanBleed() const { return (m_bleedDirection != ContainerBleedDirection::BleedRestricted); }
        ContainerBleedDirection GetBleedDirection() const { return m_bleedDirection; }

        // configures container style related attributes
        // such as style, padding and bleed
        void ConfigForContainerStyle(const AdaptiveCards::ParseContext& context);

        void SetParentalId(const AdaptiveCards::InternalId& id);
        AdaptiveCards::InternalId GetParentalId(void) const;

        std::shared_ptr<BaseActionElement> GetSelectAction() const;
        void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

        std::shared_ptr<BackgroundImage> GetBackgroundImage() const;
        void SetBackgroundImage(const std::shared_ptr<BackgroundImage> value);

        unsigned int GetMinHeight() const;
        void SetMinHeight(const unsigned int value);

        template<typename T>
        void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo,
                                    const std::vector<std::shared_ptr<T>>& elements);

        Json::Value SerializeToJsonValue() const override;
        template<typename T> static std::shared_ptr<T> Deserialize(ParseContext& context, const Json::Value& value);

    private:
        // Applies padding flag When appropriate
        void ConfigPadding(const AdaptiveCards::ParseContext& context);
        // Applies bleed flag when appropriate
        void ConfigBleed(const AdaptiveCards::ParseContext& context);
        void SetBleedDirection(const ContainerBleedDirection bleedDirection) { m_bleedDirection = bleedDirection; }

        ContainerStyle m_style;
        std::optional<VerticalContentAlignment> m_verticalContentAlignment;
        ContainerBleedDirection m_bleedDirection;

        unsigned int m_minHeight;
        bool m_hasPadding;
        bool m_hasBleed;
        // id refers to parent to where bleed property should target
        AdaptiveCards::InternalId m_parentalId;

        std::shared_ptr<BackgroundImage> m_backgroundImage;
        std::shared_ptr<BaseActionElement> m_selectAction;
    };

    template<typename T>
    std::shared_ptr<T> StyledCollectionElement::Deserialize(ParseContext& context, const Json::Value& value)
    {
        auto collection = BaseCardElement::Deserialize<T>(context, value);

        auto backgroundImage = ParseUtil::GetBackgroundImage(value);
        collection->SetBackgroundImage(backgroundImage);

        bool canFallbackToAncestor = context.GetCanFallbackToAncestor();
        context.SetCanFallbackToAncestor(canFallbackToAncestor || (collection->GetFallbackType() != FallbackType::None));
        collection->SetCanFallbackToAncestor(canFallbackToAncestor);

        collection->SetStyle(
            ParseUtil::GetEnumValue<ContainerStyle>(value, AdaptiveCardSchemaKey::Style, ContainerStyle::None, ContainerStyleFromString));

        collection->SetVerticalContentAlignment(ParseUtil::GetOptionalEnumValue<VerticalContentAlignment>(
            value, AdaptiveCardSchemaKey::VerticalContentAlignment, VerticalContentAlignmentFromString));

        collection->SetBleed(ParseUtil::GetBool(value, AdaptiveCardSchemaKey::Bleed, false));

        if (const auto& minHeight =
                ParseSizeForPixelSize(ParseUtil::GetString(value, AdaptiveCardSchemaKey::MinHeight), &context.warnings);
            minHeight.has_value())
        {
            collection->SetMinHeight(*minHeight);
        }

        // configures for container style
        collection->ConfigForContainerStyle(context);

        // we walk parse tree dfs, so we need to save current style,
        // before we walk back up to a parent.
        context.SaveContextForStyledCollectionElement(*collection);

        // Parse Items
        collection->DeserializeChildren(context, value);

        // since we are walking dfs, we have to restore the style before we back up
        context.RestoreContextForStyledCollectionElement(*collection);

        context.SetCanFallbackToAncestor(canFallbackToAncestor);

        // Parse optional selectAction
        collection->SetSelectAction(ParseUtil::GetAction(context, value, AdaptiveCardSchemaKey::SelectAction, false));

        return collection;
    }

    template<typename T>
    void StyledCollectionElement::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo,
                                                         const std::vector<std::shared_ptr<T>>& elements)
    {
        if (m_backgroundImage != nullptr)
        {
            RemoteResourceInformation backgroundImageInfo;
            backgroundImageInfo.url = m_backgroundImage->GetUrl();
            backgroundImageInfo.mimeType = "image";
            resourceInfo.push_back(backgroundImageInfo);
        }

        CollectionCoreElement::GetResourceInformation(resourceInfo, elements);
    }
}
