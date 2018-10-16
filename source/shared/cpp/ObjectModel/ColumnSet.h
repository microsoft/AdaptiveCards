#pragma once

#include "pch.h"
#include "Enums.h"
#include "BaseCardElement.h"
#include "Column.h"
#include "ElementParserRegistration.h"

namespace AdaptiveSharedNamespace
{
    class ColumnSet : public BaseCardElement
    {
        friend class ColumnSetParser;

    public:
        ColumnSet();

        Json::Value SerializeToJsonValue() const override;

        std::vector<std::shared_ptr<Column>>& GetColumns();
        const std::vector<std::shared_ptr<Column>>& GetColumns() const;

        std::shared_ptr<BaseActionElement> GetSelectAction() const;
        void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

        void SetLanguage(const std::string& language);

        void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

    private:
        void PopulateKnownPropertiesSet() override;

        static const std::unordered_map<CardElementType, std::function<std::shared_ptr<Column>(const Json::Value&)>, EnumHash> ColumnParser;
        std::vector<std::shared_ptr<Column>> m_columns;
        std::shared_ptr<BaseActionElement> m_selectAction;
    };

    class ColumnSetParser : public BaseCardElementParser
    {
    public:
        ColumnSetParser() = default;
        ColumnSetParser(const ColumnSetParser&) = default;
        ColumnSetParser(ColumnSetParser&&) = default;
        ColumnSetParser& operator=(const ColumnSetParser&) = default;
        ColumnSetParser& operator=(ColumnSetParser&&) = default;
        virtual ~ColumnSetParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(std::shared_ptr<ElementParserRegistration> elementParserRegistration,
                                                     std::shared_ptr<ActionParserRegistration> actionParserRegistration,
                                                     std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
                                                     const Json::Value& root) override;

        std::shared_ptr<BaseCardElement> DeserializeFromString(std::shared_ptr<ElementParserRegistration> elementParserRegistration,
                                                               std::shared_ptr<ActionParserRegistration> actionParserRegistration,
                                                               std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
                                                               const std::string& jsonString);
    };
}
