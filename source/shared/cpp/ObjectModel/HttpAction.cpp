#include "HttpAction.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

HttpAction::HttpAction() : BaseActionElement(ActionType::Http)
{
}

std::shared_ptr<HttpAction> HttpAction::Deserialize(const Json::Value& json)
{
    std::shared_ptr<HttpAction> httpAction = BaseActionElement::Deserialize<HttpAction>(json);

    httpAction->SetTitle(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Title));
    httpAction->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url));
    httpAction->SetBody(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Body));
    httpAction->SetMethod(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Method));

    return httpAction;
}

std::shared_ptr<HttpAction> HttpAction::DeserializeFromString(const std::string& jsonString)
{
    Json::Value jsonValue(jsonString);

    return HttpAction::Deserialize(jsonValue);
}

std::string HttpAction::Serialize()
{
    return "";
}

std::string HttpAction::GetUrl() const
{
    return m_url;
}

void HttpAction::SetUrl(const std::string value)
{
    m_url = value;
}

std::string HttpAction::GetBody() const
{
    return m_body;
}

void HttpAction::SetBody(const std::string value)
{
    m_body = value;
}

std::string HttpAction::GetMethod() const
{
    return m_method;
}

void HttpAction::SetMethod(const std::string value)
{
    m_method = value;
}

