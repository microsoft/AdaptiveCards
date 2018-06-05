#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "Enums.h"
#include "ElementParserRegistration.h"

namespace AdaptiveSharedNamespace {
class TimeInput : public BaseInputElement
{
public:
    TimeInput();

    virtual Json::Value SerializeToJsonValue() const override;

    std::string GetMax() const;
    void SetMax(const std::string &value);

    std::string GetMin() const;
    void SetMin(const std::string &value);

    std::string GetPlaceholder() const;
    void SetPlaceholder(const std::string &value);

    std::string GetValue() const;
    void SetValue(const std::string &value);

private:
    void PopulateKnownPropertiesSet();

    std::string m_max;
    std::string m_min;
    std::string m_placeholder;
    std::string m_value;
};

class TimeInputParser : public BaseCardElementParser
{
public:
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
