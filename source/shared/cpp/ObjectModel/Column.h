#pragma once

#include "pch.h"
#include "Enums.h"
#include "BaseActionElement.h"
#include "BaseCardElement.h"

AdaptiveSharedNamespaceStart
class Column : public BaseCardElement
{
public:
    Column();
    Column(Spacing spacing, bool separation, std::string size, unsigned int pixelWidth, ContainerStyle style);
    Column(Spacing spacing, bool separation, std::string size, unsigned int pixelWidth, ContainerStyle style, std::vector<std::shared_ptr<BaseCardElement>>& items);

    virtual std::string Serialize();
    virtual Json::Value SerializeToJsonValue();

    static std::shared_ptr<Column> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        const Json::Value& root);

    static std::shared_ptr<Column> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        const std::string& jsonString);

    std::string GetWidth() const;
    void SetWidth(const std::string value);

    // explicit width takes precedence over relative width 
    int GetPixelWidth() const;
    void SetPixelWidth(const int value);

    ContainerStyle GetStyle() const;
    void SetStyle(const ContainerStyle value);

    std::vector<std::shared_ptr<BaseCardElement>>& GetItems();
    const std::vector<std::shared_ptr<BaseCardElement>>& GetItems() const;

    std::shared_ptr<BaseActionElement> GetSelectAction() const;
    void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

    void SetLanguage(const std::string& language);

    virtual void GetResourceUris(std::vector<std::string>& resourceUris) override;

private:
    void PopulateKnownPropertiesSet();

    std::string m_width;
    unsigned int m_pixelWidth;
    std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>> m_items;
    std::shared_ptr<BaseActionElement> m_selectAction;
    ContainerStyle m_style;
};
AdaptiveSharedNamespaceEnd
