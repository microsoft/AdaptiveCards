#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "Enums.h"

namespace AdaptiveCards
{
class ToggleInput : public BaseInputElement
{
public:
    ToggleInput();

    static std::shared_ptr<ToggleInput> Deserialize(const Json::Value& root);
    static std::shared_ptr<ToggleInput> DeserializeFromString(const std::string& jsonString);

    virtual std::string Serialize();
    Json::Value SerializeToJsonValue();

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
}