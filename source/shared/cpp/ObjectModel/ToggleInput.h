#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "Enums.h"
#include "ElementParserRegistration.h"

AdaptiveSharedNamespaceStart
class ToggleInput : public BaseInputElement
{
public:
    ToggleInput();

    virtual Json::Value SerializeToJsonValue() const override;

    std::string GetTitle() const;
    void SetTitle(const std::string &value);

    std::string GetValue() const;
    void SetValue(const std::string &value);

    std::string GetValueOff() const;
    void SetValueOff(const std::string &value);

    std::string GetValueOn() const;
    void SetValueOn(const std::string &value);

private:
    void PopulateKnownPropertiesSet();

    std::string m_title;
    std::string m_value;
    std::string m_valueOff;
    std::string m_valueOn;
};

class ToggleInputParser : public BaseCardElementParser
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
AdaptiveSharedNamespaceEnd
