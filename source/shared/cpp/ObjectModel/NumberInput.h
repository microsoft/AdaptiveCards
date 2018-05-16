#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "Enums.h"
#include "ElementParserRegistration.h"

AdaptiveSharedNamespaceStart
class NumberInput : public BaseInputElement
{
public:
    NumberInput();

    virtual Json::Value SerializeToJsonValue() const override;

    std::string GetPlaceholder() const;
    void SetPlaceholder(const std::string &value);

    int GetValue() const;
    void SetValue(const int value);

    int GetMax() const;
    void SetMax(const int value);

    int GetMin() const;
    void SetMin(const int value);

private:
    void PopulateKnownPropertiesSet();

    std::string m_placeholder;
    int m_value;
    int m_max;
    int m_min;
};

class NumberInputParser : public BaseCardElementParser
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
