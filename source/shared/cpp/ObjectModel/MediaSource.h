#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"
#include "ElementParserRegistration.h"

namespace AdaptiveSharedNamespace {
class MediaSource
{
public:
    MediaSource();

    virtual Json::Value SerializeToJsonValue() const;

    std::string GetMimeType() const;
    void SetMimeType(const std::string& value);

    std::string GetUrl() const;
    void SetUrl(const std::string& value);

private:
    std::string m_mimeType;
    std::string m_url;
};

class MediaSourceParser
{
public:
    static std::shared_ptr<MediaSource> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const Json::Value& root);

    static std::shared_ptr<MediaSource> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const std::string& jsonString);
};
}
