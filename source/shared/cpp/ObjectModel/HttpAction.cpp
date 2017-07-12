#include "HttpAction.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

HttpAction::HttpAction() : BaseActionElement(ActionType::Http)
{
}

std::shared_ptr<HttpAction> HttpAction::Deserialize(const Json::Value& json)
{
    std::shared_ptr<HttpAction> httpAction = BaseActionElement::Deserialize<HttpAction>(json);

    httpAction->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url, true));
    httpAction->SetBody(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Body));
    httpAction->SetMethod(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Method, true));

    return httpAction;
}

std::shared_ptr<HttpAction> HttpAction::DeserializeFromString(const std::string& jsonString)
{
    Json::Value jsonValue(jsonString);

    return HttpAction::Deserialize(jsonValue);
}

std::string HttpAction::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value HttpAction::SerializeToJsonValue()
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Url)] = GetUrl();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Body)] = GetBody();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Method)] = GetMethod();

    return root;
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

