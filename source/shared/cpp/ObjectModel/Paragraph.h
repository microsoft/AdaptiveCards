#pragma once

#include "pch.h"
#include "Inline.h"

namespace AdaptiveSharedNamespace
{
    class Paragraph
    {
    public:
        Paragraph();
        Paragraph(const Paragraph&) = default;
        Paragraph(Paragraph&&) = default;
        Paragraph& operator=(const Paragraph&) = default;
        Paragraph& operator=(Paragraph&&) = default;
        ~Paragraph() = default;

        virtual Json::Value SerializeToJsonValue() const;

        std::vector<std::shared_ptr<Inline>>& GetInlines();
        const std::vector<std::shared_ptr<Inline>>& GetInlines() const;

        static std::shared_ptr<Paragraph> Deserialize(ParseContext& context, const Json::Value& root);

        Json::Value GetAdditionalProperties() const;
        void SetAdditionalProperties(const Json::Value& additionalProperties);

    private:
        void PopulateKnownPropertiesSet();

        std::vector<std::shared_ptr<Inline>> m_inlines;
        std::unordered_set<std::string> m_knownProperties;
        Json::Value m_additionalProperties;
    };
}
