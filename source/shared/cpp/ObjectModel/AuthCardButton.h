// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "ParseContext.h"

namespace AdaptiveSharedNamespace
{
    class AuthCardButton
    {
    public:
        AuthCardButton() : AuthCardButton("", "", "", "") {}
        AuthCardButton(std::string type, std::string title, std::string image, std::string value) :
            m_type(type), m_title(title), m_image(image), m_value(value) {}

        std::string GetType();
        void SetType(std::string);

        std::string GetTitle();
        void SetTitle(std::string);

        std::string GetImage();
        void SetImage(std::string);

        std::string GetValue();
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
