#include "pch.h"

#include "BaseElement.h"
#include "ParseUtil.h"

namespace AdaptiveSharedNamespace
{
    std::string BaseElement::Serialize() const
    {
        Json::FastWriter writer;
        return writer.write(SerializeToJsonValue());
    }

    std::string BaseElement::GetId() const
    {
        return m_id;
    }

    void BaseElement::SetId(const std::string& value)
    {
        m_id = value;
    }

    std::string BaseElement::GetElementTypeString() const
    {
        return m_typeString;
    }

    void BaseElement::SetElementTypeString(const std::string& value)
    {
        m_typeString = value;
    }

    void BaseElement::PopulateKnownPropertiesSet()
    {
        m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Fallback),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Id),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Requires),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)});
    }

    Json::Value BaseElement::GetAdditionalProperties() const
    {
        return m_additionalProperties;
    }

    void BaseElement::SetAdditionalProperties(Json::Value const& value)
    {
        m_additionalProperties = value;
    }

    bool BaseElement::MeetsRequirements(const std::unordered_map<std::string, std::string>& hostProvides) const
    {
        for (const auto &requirement : m_requires)
        {
            // special case for adaptive cards version
            const auto& requirementName = requirement.first;
            if (requirementName == "adaptiveCards")
            {
                static const SemanticVersion currentAdaptiveCardsVersion{"1.2"};
                if (currentAdaptiveCardsVersion > requirement.second)
                {
                    return false;
                }
            }
            else
            {
                const auto& provides = hostProvides.find(requirementName);
                if (provides == hostProvides.end())
                {
                    // host doesn't provide this requirement
                    return false;
                }
                else
                {
                    const SemanticVersion providesVersion{provides->second};
                    if (providesVersion < requirement.second)
                    {
                        // host's provided version is too low
                        return false;
                    }
                }
            }
        }
        return true;
    }

    Json::Value BaseElement::SerializeToJsonValue() const
    {
        Json::Value root = GetAdditionalProperties();

        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = GetElementTypeString();

        if (!m_id.empty())
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Id)] = m_id;
        }

        // Handle fallback
        if (m_fallbackType == FallbackType::Drop)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Fallback)] = "drop";
        }
        else if (m_fallbackType == FallbackType::Content)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Fallback)] = m_fallbackContent->SerializeToJsonValue();
        }

        // Handle requires
        if (!m_requires.empty())
        {
            Json::Value jsonRequires{};
            for (const auto& requirement : m_requires)
            {
                jsonRequires[requirement.first] = static_cast<std::string>(requirement.second);
            }

            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Requires)] = jsonRequires;
        }

        return root;
    }

    void BaseElement::GetResourceInformation(std::vector<RemoteResourceInformation>& /*resourceInfo*/)
    {
        return;
    }

    void BaseElement::ParseRequires(ParseContext& /*context*/, const Json::Value& json)
    {
        const auto requiresValue = ParseUtil::ExtractJsonValue(json, AdaptiveCardSchemaKey::Requires, false);
        if (!requiresValue.isNull())
        {
            if (requiresValue.isObject())
            {
                const auto& memberNames = requiresValue.getMemberNames();
                const auto countNames = memberNames.size();
                for (unsigned int i = 0; i < countNames; ++i)
                {
                    const auto& memberName = memberNames.at(i);
                    const auto& memberValue = requiresValue[memberName].asString();
                    try
                    {
                        SemanticVersion memberVersion(memberValue);
                        m_requires.emplace(memberName, memberVersion);
                    }
                    catch (const AdaptiveCardParseException&)
                    {
                        throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Invalid version in requires value: '" + memberValue + "'");
                    }
                }
                return;
            }
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Invalid value for requires (should be object)");
        }
    }
}
