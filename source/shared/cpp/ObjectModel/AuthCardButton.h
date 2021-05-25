// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "ParseContext.h"

namespace AdaptiveCards
{
    class AuthCardButton
    {
    public:
        AuthCardButton() {}
        AuthCardButton(std::string type, std::string title, std::string image, std::string value) :
            m_type(std::move(type)), m_title(std::move(title)), m_image(std::move(image)), m_value(std::move(value))
        {
        }

        std::string GetType();
        std::string GetType() const;
        void SetType(std::string);

        std::string GetTitle();
        std::string GetTitle() const;
        void SetTitle(std::string);

        std::string GetImage();
        std::string GetImage() const;
        void SetImage(std::string);

        std::string GetValue();
        std::string GetValue() const;
        void SetValue(std::string);

        bool ShouldSerialize() const;
        std::string Serialize() const;
        Json::Value SerializeToJsonValue() const;

        static std::shared_ptr<AuthCardButton> Deserialize(ParseContext& context, const Json::Value& json);
        static std::shared_ptr<AuthCardButton> DeserializeFromString(ParseContext& context, const std::string& jsonString);

    private:
        std::string m_type;
        std::string m_title;
        std::string m_image;
        std::string m_value;
    };
}
