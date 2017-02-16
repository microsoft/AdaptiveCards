#pragma once

#include "pch.h"
#include "Enums.h"
#include "BaseCardElement.h"

namespace AdaptiveCards
{
class BaseCardElement;
class Container : public BaseCardElement, public std::enable_shared_from_this<Container>
{
public:
    Container();
    Container(std::shared_ptr<Container> parent,
        HorizontalAlignment horizontalAlignment,
        CardElementSize size,
        std::string speak,
        std::string backgroundImageUrl,
        std::string backgroundColor
    );
    Container(std::shared_ptr<Container> parent,
        HorizontalAlignment horizontalAlignment,
        CardElementSize size,
        std::string speak,
        std::string backgroundImageUrl,
        std::string backgroundColor,
        std::vector<std::shared_ptr<BaseCardElement>> &items
    );

    virtual std::string Serialize();
    const std::vector<std::shared_ptr<BaseCardElement>>& GetItems();

    void AddItem(std::shared_ptr<BaseCardElement>& item);
    std::shared_ptr<BaseCardElement> GetItem(const size_t index) const;

    static std::shared_ptr<Container> Deserialize(const Json::Value& root);

    std::string GetBackgroundImageUrl() const;
    void SetBackgroundImageUrl(const std::string value);

    std::string GetBackgroundColor() const;
    void SetBackgroundColor(const std::string value);

private:
    std::string m_backgroundImageUrl;
    std::string m_backgroundColor;
    std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>> m_items;
};
}