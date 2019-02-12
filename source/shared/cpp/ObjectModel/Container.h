#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "CollectionTypeElement.h"

namespace AdaptiveSharedNamespace
{
    class BaseActionElement;

    class Container : public BaseCardElement, public CollectionTypeElement
    {
        friend class ContainerParser;

    public:
        Container();
        Container(const Container&) = default;
        Container(Container&&) = default;
        Container& operator=(const Container&) = default;
        Container& operator=(Container&&) = default;
        ~Container() = default;

        Json::Value SerializeToJsonValue() const override;

        std::vector<std::shared_ptr<BaseCardElement>>& GetItems();
        const std::vector<std::shared_ptr<BaseCardElement>>& GetItems() const;

        std::shared_ptr<BaseActionElement> GetSelectAction() const;
        void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

        void SetLanguage(const std::string& value);

        void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

    private:
        void PopulateKnownPropertiesSet() override;

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

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
