#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "Enums.h"

namespace AdaptiveCards
{
class HttpAction : public BaseActionElement
{
public:
    HttpAction();

    static std::shared_ptr<HttpAction> Deserialize(const Json::Value& root);
    static std::shared_ptr<HttpAction> DeserializeFromString(const std::string& jsonString);

    virtual std::string Serialize();

    std::string GetUrl() const;
    void SetUrl(const std::string value);

    std::string GetMethod() const;
    void SetMethod(const std::string value);

    std::string GetBody() const;
    void SetBody(const std::string value);

private:
    std::string m_method;
    std::string m_body;
    std::string m_url;
};
}