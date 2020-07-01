// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "BaseElement.h"
#include "ParseUtil.h"
#include "SemanticVersion.h"

namespace AdaptiveSharedNamespace
{
    unsigned int InternalId::s_currentInternalId = 1;

    InternalId InternalId::Current()
    {
        InternalId internalId{s_currentInternalId};
        return internalId;
    }

    InternalId InternalId::Next()
    {
        s_currentInternalId++;

        // handle overflow case
        if (s_currentInternalId == InternalId::Invalid)
        {
            s_currentInternalId++;
        }

        return Current();
    }

    InternalId::InternalId() : m_internalId{InternalId::Invalid} {}

    InternalId::InternalId(const unsigned int id) : m_internalId{id} {}

    std::string BaseElement::Serialize() const { return ParseUtil::JsonToString(SerializeToJsonValue()); }

    std::string BaseElement::GetId() const { return m_id; }

    void BaseElement::SetId(const std::string& value) { m_id = value; }

    std::string BaseElement::GetElementTypeString() const { return m_typeString; }

    void BaseElement::SetElementTypeString(const std::string& value) { m_typeString = value; }

    void BaseElement::PopulateKnownPropertiesSet()
    {
        m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Fallback),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Id),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Requires),
                                  AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)});
    }

    const Json::Value& BaseElement::GetAdditionalProperties() const { return m_additionalProperties; }

    void BaseElement::SetAdditionalProperties(Json::Value const& value) { m_additionalProperties = value; }

    // Given a map of what our host provides, determine if this element's requirements are satisfied.
    bool BaseElement::MeetsRequirements(const AdaptiveSharedNamespace::FeatureRegistration& featureRegistration) const
    {
        for (const auto& requirement : *m_requires)
        {
            // special case for adaptive cards version
            const auto& requirementName = requirement.first;
            const auto& requirementVersion = requirement.second;
            const auto& featureVersion = featureRegistration.GetFeatureVersion(requirementName);
            if (featureVersion.empty())
            {
                // host doesn't provide this requirement
                return false;
            }
            else
            {
                // host provides this requirement, but does it provide an acceptible version?
                const SemanticVersion providesVersion{featureVersion};
                if (providesVersion < requirementVersion)
                {
                    // host's provided version is too low
                    return false;
                }
            }
        }

        return true;
    }

    std::shared_ptr<std::unordered_map<std::string, AdaptiveSharedNamespace::SemanticVersion>> BaseElement::GetRequirements() const
    {
        return m_requires;
    }

    Json::Value BaseElement::SerializeToJsonValue() const
    {
        Json::Value root = GetAdditionalProperties(); // Create a copy of the additional properties by assigning the return value to a value, rather than reference, type

        // Important -- we're explicitly getting the type as a string here because that's where we store the type that
        // was specified by the card author.
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
        if (!m_requires->empty())
        {
            Json::Value jsonRequires{};
            for (const auto& requirement : *m_requires)
            {
                jsonRequires[requirement.first] = static_cast<std::string>(requirement.second);
            }

            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Requires)] = jsonRequires;
        }

        return root;
    }

    // Base implementation for elements that have no resource information
    void BaseElement::GetResourceInformation(std::vector<RemoteResourceInformation>& /*resourceInfo*/) { return; }

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

                    if (memberValue == "*")
                    {
                        // * means any version.
                        m_requires->emplace(memberName, "0");
                    }
                    else
                    {
                        try
                        {
                            SemanticVersion memberVersion(memberValue);
                            m_requires->emplace(memberName, memberVersion);
                        }
                        catch (const AdaptiveCardParseException&)
                        {
                            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                                             "Invalid version in requires value: '" + memberValue + "'");
                        }
                    }
                }
                return;
            }
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Invalid value for requires (should be object)");
        }
    }
}
