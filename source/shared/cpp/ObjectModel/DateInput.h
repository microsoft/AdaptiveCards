#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "Enums.h"
#include "ElementParserRegistration.h"

AdaptiveSharedNamespaceStart
class DateInput : public BaseInputElement
{
public:
    DateInput();

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

class DateInputParser : public BaseCardElementParser
{
public:
    std::shared_ptr<BaseCardElement> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        const Json::Value& root);

    std::shared_ptr<BaseCardElement> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        const std::string& jsonString);
};
AdaptiveSharedNamespaceEnd
