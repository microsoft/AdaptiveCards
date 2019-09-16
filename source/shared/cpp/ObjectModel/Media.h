// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "ElementParserRegistration.h"
#include "MediaSource.h"

namespace AdaptiveSharedNamespace
{
    class Media : public BaseCardElement
    {
        friend class MediaParser;

    public:
        Media();
        Media(const Media&) = default;
        Media(Media&&) = default;
        Media& operator=(const Media&) = default;
        Media& operator=(Media&&) = default;
        ~Media() = default;

        Json::Value SerializeToJsonValue() const override;

        std::string GetPoster() const;
        void SetPoster(const std::string& value);

        std::string GetAltText() const;
        void SetAltText(const std::string& value);

        std::vector<std::shared_ptr<MediaSource>>& GetSources();

        void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

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

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
