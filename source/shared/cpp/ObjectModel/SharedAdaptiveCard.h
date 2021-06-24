// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "BaseActionElement.h"
#include "ParseResult.h"
#include "Refresh.h"
#include "Authentication.h"

namespace AdaptiveCards
{
    class Container;
    class BackgroundImage;

    class AdaptiveCard
    {
    public:
        AdaptiveCard();

        AdaptiveCard(std::string const& version,
                     std::string const& fallbackText,
                     std::string const& backgroundImageUrl,
                     ContainerStyle style,
                     std::string const& speak,
                     std::string const& language,
                     VerticalContentAlignment verticalContentAlignment,
                     HeightType height,
                     unsigned int minHeight);

        AdaptiveCard(std::string const& version,
                     std::string const& fallbackText,
                     std::string const& backgroundImageUrl,
                     ContainerStyle style,
                     std::string const& speak,
                     std::string const& language,
                     VerticalContentAlignment verticalContentAlignment,
                     HeightType height,
                     unsigned int minHeight,
                     std::vector<std::shared_ptr<BaseCardElement>>& body,
                     std::vector<std::shared_ptr<BaseActionElement>>& actions);

        AdaptiveCard(std::string const& version,
                     std::string const& fallbackText,
                     std::shared_ptr<BackgroundImage> backgroundImage,
                     ContainerStyle style,
                     std::string const& speak,
                     std::string const& language,
                     VerticalContentAlignment verticalContentAlignment,
                     HeightType height,
                     unsigned int minHeight);

        AdaptiveCard(std::string const& version,
                     std::string const& fallbackText,
                     std::shared_ptr<BackgroundImage> backgroundImage,
                     ContainerStyle style,
                     std::string const& speak,
                     std::string const& language,
                     VerticalContentAlignment verticalContentAlignment,
                     HeightType height,
                     unsigned int minHeight,
                     std::vector<std::shared_ptr<BaseCardElement>>& body,
                     std::vector<std::shared_ptr<BaseActionElement>>& actions);

        AdaptiveCard(std::string const& version,
                     std::string const& fallbackText,
                     std::shared_ptr<BackgroundImage> backgroundImage,
                     std::shared_ptr<Refresh> refresh,
                     std::shared_ptr<Authentication> authentication,
                     ContainerStyle style,
                     std::string const& speak,
                     std::string const& language,
                     VerticalContentAlignment verticalContentAlignment,
                     HeightType height,
                     unsigned int minHeight,
                     std::vector<std::shared_ptr<BaseCardElement>>& body,
                     std::vector<std::shared_ptr<BaseActionElement>>& actions);

        std::string GetVersion() const;
        void SetVersion(const std::string& value);
        std::string GetFallbackText() const;
        void SetFallbackText(const std::string& value);
        std::shared_ptr<BackgroundImage> GetBackgroundImage() const;
        void SetBackgroundImage(const std::shared_ptr<BackgroundImage> value);
        std::shared_ptr<Refresh> GetRefresh() const;
        void SetRefresh(const std::shared_ptr<Refresh> value);
        std::shared_ptr<Authentication> GetAuthentication() const;
        void SetAuthentication(const std::shared_ptr<Authentication> value);
        std::string GetSpeak() const;
        void SetSpeak(const std::string& value);
        ContainerStyle GetStyle() const;
        void SetStyle(const ContainerStyle value);
        const std::string& GetLanguage() const;
        void SetLanguage(const std::string& value);
        VerticalContentAlignment GetVerticalContentAlignment() const;
        void SetVerticalContentAlignment(const VerticalContentAlignment value);
        HeightType GetHeight() const;
        void SetHeight(const HeightType value);
        unsigned int GetMinHeight() const;
        void SetMinHeight(const unsigned int value);
        std::optional<bool> GetRtl() const;
        void SetRtl(const std::optional<bool>& value);

        std::shared_ptr<BaseActionElement> GetSelectAction() const;
        void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

        std::vector<std::shared_ptr<BaseCardElement>>& GetBody();
        const std::vector<std::shared_ptr<BaseCardElement>>& GetBody() const;
        std::vector<std::shared_ptr<BaseActionElement>>& GetActions();
        const std::vector<std::shared_ptr<BaseActionElement>>& GetActions() const;

        const std::unordered_set<std::string>& GetKnownProperties() const;
        const Json::Value& GetAdditionalProperties() const;
        void SetAdditionalProperties(Json::Value&& additionalProperties);
        void SetAdditionalProperties(const Json::Value& additionalProperties);

        std::vector<RemoteResourceInformation> GetResourceInformation();

        CardElementType GetElementType() const;
#ifdef __ANDROID__
#pragma GCC diagnostic ignored "-Wdynamic-exception-spec"
        static std::shared_ptr<ParseResult> DeserializeFromFile(const std::string& jsonFile,
                                                                std::string rendererVersion,
                                                                ParseContext& context) throw(AdaptiveCards::AdaptiveCardParseException);
        static std::shared_ptr<ParseResult> DeserializeFromFile(const std::string& jsonFile,
                                                                std::string rendererVersion) throw(AdaptiveCards::AdaptiveCardParseException);

        static std::shared_ptr<ParseResult> Deserialize(const Json::Value& json,
                                                        std::string rendererVersion,
                                                        ParseContext& context) throw(AdaptiveCards::AdaptiveCardParseException);

        static std::shared_ptr<ParseResult> DeserializeFromString(const std::string& jsonString,
                                                                  std::string rendererVersion,
                                                                  ParseContext& context) throw(AdaptiveCards::AdaptiveCardParseException);
        static std::shared_ptr<ParseResult> DeserializeFromString(const std::string& jsonString,
                                                                  std::string rendererVersion) throw(AdaptiveCards::AdaptiveCardParseException);
        static std::shared_ptr<AdaptiveCard> MakeFallbackTextCard(const std::string& fallbackText,
                                                                  const std::string& language,
                                                                  const std::string& speak) throw(AdaptiveCards::AdaptiveCardParseException);
#else
        static std::shared_ptr<ParseResult> DeserializeFromFile(const std::string& jsonFile,
                                                                const std::string& rendererVersion,
                                                                ParseContext& context);
        static std::shared_ptr<ParseResult> DeserializeFromFile(const std::string& jsonFile, const std::string& rendererVersion);

        static std::shared_ptr<ParseResult> Deserialize(const Json::Value& json, const std::string& rendererVersion, ParseContext& context);

        static std::shared_ptr<ParseResult> DeserializeFromString(const std::string& jsonString,
                                                                  const std::string& rendererVersion,
                                                                  ParseContext& context);
        static std::shared_ptr<ParseResult> DeserializeFromString(const std::string& jsonString, const std::string& rendererVersion);

        static std::shared_ptr<AdaptiveCard> MakeFallbackTextCard(const std::string& fallbackText,
                                                                  const std::string& language,
                                                                  const std::string& speak);

#endif // __ANDROID__
        Json::Value SerializeToJsonValue() const;
        std::string Serialize() const;

        const InternalId GetInternalId() const { return m_internalId; }

    private:
        static void _ValidateLanguage(const std::string& language, std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings);
        void PopulateKnownPropertiesSet();

        std::string m_version;
        std::string m_fallbackText;
        std::shared_ptr<BackgroundImage> m_backgroundImage;
        std::shared_ptr<Refresh> m_refresh;
        std::shared_ptr<Authentication> m_authentication;
        std::string m_speak;
        ContainerStyle m_style;
        std::string m_language;
        VerticalContentAlignment m_verticalContentAlignment;
        HeightType m_height;
        unsigned int m_minHeight;
        std::optional<bool> m_rtl;
        InternalId m_internalId;
        std::unordered_set<std::string> m_knownProperties;
        Json::Value m_additionalProperties;

        std::vector<std::shared_ptr<BaseCardElement>> m_body;
        std::vector<std::shared_ptr<BaseActionElement>> m_actions;

        std::shared_ptr<BaseActionElement> m_selectAction;
    };
}
