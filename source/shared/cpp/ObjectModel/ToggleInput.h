#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "Enums.h"
#include "ElementParserRegistration.h"

namespace AdaptiveCards
{
class ToggleInput : public BaseInputElement
{
public:
    ToggleInput();

    virtual Json::Value SerializeToJsonValue() override;

    std::string GetTitle() const;
    void SetTitle(const std::string value);

    std::string GetValue() const;
    void SetValue(const std::string value);

    std::string GetValueOff() const;
    void SetValueOff(const std::string value);

    std::string GetValueOn() const;
    void SetValueOn(const std::string value);

private:
    std::string m_title;
    std::string m_value;
    std::string m_valueOff;
    std::string m_valueOn;
};

class ToggleInputParser : public IBaseCardElementParser
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
}