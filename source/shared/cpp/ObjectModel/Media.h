#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"
#include "ElementParserRegistration.h"
#include "MediaSource.h"

namespace AdaptiveSharedNamespace {
class Media : public BaseCardElement
{
    friend class MediaParser;
public:
    Media();

    Json::Value SerializeToJsonValue() const override;

    std::string GetPoster() const;
    void SetPoster(const std::string& value);

    std::string GetAltText() const;
    void SetAltText(const std::string& value);

    std::vector<std::shared_ptr<MediaSource>>& GetSources();

private:
    std::string m_poster;
    std::string m_altText;
    std::vector<std::shared_ptr<MediaSource>> m_sources;

    void PopulateKnownPropertiesSet() override;
};

class MediaParser : public BaseCardElementParser
{
public:
    MediaParser() = default;
    MediaParser(const MediaParser&) = default;
    MediaParser(MediaParser&&) = default;
    MediaParser& operator=(const MediaParser&) = default;
    MediaParser& operator=(MediaParser&&) = default;
    virtual ~MediaParser() = default;

    std::shared_ptr<BaseCardElement> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const Json::Value& root) override;

    std::shared_ptr<BaseCardElement> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const std::string& jsonString);
};
}
