#pragma once

#include "Enums.h"
#include "pch.h"
#include "BaseActionElement.h"
#include "BaseCardElement.h"
#include "ElementParserRegistration.h"

namespace AdaptiveSharedNamespace {
class Container : public BaseCardElement
{
friend class ContainerParser;
public:
    Container();

    Json::Value SerializeToJsonValue() const override;

    std::vector<std::shared_ptr<BaseCardElement>>& GetItems();
    const std::vector<std::shared_ptr<BaseCardElement>>& GetItems() const;

    ContainerStyle GetStyle() const;
    void SetStyle(const ContainerStyle value);

    std::shared_ptr<BaseActionElement> GetSelectAction() const;
    void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

    void SetLanguage(const std::string& value);

    VerticalContentAlignment GetVerticalContentAlignment() const;
    void SetVerticalContentAlignment(const VerticalContentAlignment value);

    void GetResourceUris(std::vector<std::string>& resourceUris) override;

private:
    void PopulateKnownPropertiesSet() override;

    ContainerStyle m_style;
    VerticalContentAlignment m_verticalContentAlignment;
    std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>> m_items;
    std::shared_ptr<BaseActionElement> m_selectAction;
};

class ContainerParser : public BaseCardElementParser
{
public:
    ContainerParser() = default;
    ContainerParser(const ContainerParser&) = default;
    ContainerParser(ContainerParser&&) = default;
    ContainerParser& operator=(const ContainerParser&) = default;
    ContainerParser& operator=(ContainerParser&&) = default;
    virtual ~ContainerParser() = default;

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
