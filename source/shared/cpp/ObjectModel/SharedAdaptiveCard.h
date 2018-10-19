#pragma once

#include "BaseCardElement.h"
#include "BaseActionElement.h"
#include "Enums.h"
#include "pch.h"
#include "ParseResult.h"

namespace AdaptiveSharedNamespace
{
    class Container;

    class AdaptiveCard
    {
    public:
        AdaptiveCard();
        AdaptiveCard(std::string const& version,
                     std::string const& fallbackText,
                     std::string const& backgroundImage,
                     ContainerStyle style,
                     std::string const& speak,
                     std::string const& language,
                     VerticalContentAlignment verticalContentAlignment,
                     HeightType height);
        AdaptiveCard(std::string const& version,
                     std::string const& fallbackText,
                     std::string const& backgroundImage,
                     ContainerStyle style,
                     std::string const& speak,
                     std::string const& language,
                     VerticalContentAlignment verticalContentAlignment,
                     HeightType height,
                     std::vector<std::shared_ptr<BaseCardElement>>& body,
                     std::vector<std::shared_ptr<BaseActionElement>>& actions);

        std::string GetVersion() const;
        void SetVersion(const std::string& value);
        std::string GetFallbackText() const;
        void SetFallbackText(const std::string& value);
        std::string GetBackgroundImage() const;
        void SetBackgroundImage(const std::string& value);
        std::string GetSpeak() const;
        void SetSpeak(const std::string& value);
        ContainerStyle GetStyle() const;
        void SetStyle(const ContainerStyle value);
        std::string GetLanguage() const;
        void SetLanguage(const std::string& value);
        VerticalContentAlignment GetVerticalContentAlignment() const;
        void SetVerticalContentAlignment(const VerticalContentAlignment value);
        HeightType GetHeight() const;
        void SetHeight(const HeightType value);

        std::shared_ptr<BaseActionElement> GetSelectAction() const;
        void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

        std::vector<std::shared_ptr<BaseCardElement>>& GetBody();
        const std::vector<std::shared_ptr<BaseCardElement>>& GetBody() const;
        std::vector<std::shared_ptr<BaseActionElement>>& GetActions();
        const std::vector<std::shared_ptr<BaseActionElement>>& GetActions() const;

        std::vector<RemoteResourceInformation> GetResourceInformation();

        const CardElementType GetElementType() const;
#ifdef __ANDROID__
        static std::shared_ptr<ParseResult> DeserializeFromFile(
            const std::string& jsonFile,
            std::string rendererVersion,
            std::shared_ptr<ElementParserRegistration> elementParserRegistration = nullptr,
            std::shared_ptr<ActionParserRegistration> actionParserRegistration = nullptr) throw(AdaptiveSharedNamespace::AdaptiveCardParseException);
        static std::shared_ptr<ParseResult> Deserialize(const Json::Value& json,
                                                        std::string rendererVersion,
                                                        std::shared_ptr<ElementParserRegistration> elementParserRegistration = nullptr,
                                                        std::shared_ptr<ActionParserRegistration> actionParserRegistration =
                                                            nullptr) throw(AdaptiveSharedNamespace::AdaptiveCardParseException);
        static std::shared_ptr<ParseResult> DeserializeFromString(
            const std::string& jsonString,
            std::string rendererVersion,
            std::shared_ptr<ElementParserRegistration> elementParserRegistration = nullptr,
            std::shared_ptr<ActionParserRegistration> actionParserRegistration = nullptr) throw(AdaptiveSharedNamespace::AdaptiveCardParseException);
        static std::shared_ptr<AdaptiveCard> MakeFallbackTextCard(const std::string& fallbackText,
                                                                  const std::string& language,
                                                                  const std::string& speak) throw(AdaptiveSharedNamespace::AdaptiveCardParseException);
#else
        static std::shared_ptr<ParseResult> DeserializeFromFile(const std::string& jsonFile,
                                                                std::string rendererVersion,
                                                                std::shared_ptr<ElementParserRegistration> elementParserRegistration = nullptr,
                                                                std::shared_ptr<ActionParserRegistration> actionParserRegistration = nullptr);

        static std::shared_ptr<ParseResult> Deserialize(const Json::Value& json,
                                                        std::string rendererVersion,
                                                        std::shared_ptr<ElementParserRegistration> elementParserRegistration = nullptr,
                                                        std::shared_ptr<ActionParserRegistration> actionParserRegistration = nullptr);

        static std::shared_ptr<ParseResult>
        DeserializeFromString(const std::string& jsonString,
                              std::string rendererVersion,
                              std::shared_ptr<ElementParserRegistration> elementParserRegistration = nullptr,
                              std::shared_ptr<ActionParserRegistration> actionParserRegistration = nullptr);

        static std::shared_ptr<AdaptiveCard> MakeFallbackTextCard(const std::string& fallbackText,
                                                                  const std::string& language,
                                                                  const std::string& speak);

#endif // __ANDROID__
        Json::Value SerializeToJsonValue() const;
        std::string Serialize() const;

    private:
        std::string m_version;
        std::string m_fallbackText;
        std::string m_backgroundImage;
        std::string m_speak;
        ContainerStyle m_style;
        std::string m_language;
        VerticalContentAlignment m_verticalContentAlignment;
        HeightType m_height;

        std::vector<std::shared_ptr<BaseCardElement>> m_body;
        std::vector<std::shared_ptr<BaseActionElement>> m_actions;

        std::shared_ptr<BaseActionElement> m_selectAction;
    };
}
