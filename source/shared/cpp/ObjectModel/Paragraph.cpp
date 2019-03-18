#include "pch.h"
#include "Paragraph.h"

using namespace AdaptiveSharedNamespace;

Paragraph::Paragraph()
{
    PopulateKnownPropertiesSet();
}

std::vector<std::shared_ptr<Inline>>& Paragraph::GetInlines()
{
    return m_inlines;
}

const std::vector<std::shared_ptr<Inline>>& Paragraph::GetInlines() const
{
    return m_inlines;
}

Json::Value Paragraph::GetAdditionalProperties() const
{
    return m_additionalProperties;
}

void Paragraph::SetAdditionalProperties(Json::Value const& value)
{
    m_additionalProperties = value;
}

std::shared_ptr<Paragraph> AdaptiveSharedNamespace::Paragraph::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<Paragraph> paragraph = std::make_shared<Paragraph>();

    auto inlines =
        ParseUtil::GetElementCollectionOfSingleType<Inline>(context, json, AdaptiveCardSchemaKey::Inlines, Inline::Deserialize, false);
    paragraph->m_inlines = std::move(inlines);

    HandleUnknownProperties(json, paragraph->m_knownProperties, paragraph->m_additionalProperties);

    return paragraph;
}

void Paragraph::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Inlines),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)});
}

Json::Value Paragraph::SerializeToJsonValue() const
{
    Json::Value root = Json::Value();

    std::string inlinesPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Inlines);
    root[inlinesPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& inlineToSerialize : GetInlines())
    {
        root[inlinesPropertyName].append(inlineToSerialize->SerializeToJsonValue());
    }

    return root;
}
