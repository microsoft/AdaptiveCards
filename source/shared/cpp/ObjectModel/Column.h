#pragma once

#include "pch.h"
#include "Enums.h"
#include "Container.h"

namespace AdaptiveCards
{
class Column : public Container
{
public:
    Column();
    Column(SeparationStyle separation, std::string speak, std::string size);
    Column(SeparationStyle separation, std::string speak, std::string size, std::vector<std::shared_ptr<BaseCardElement>>& items);

    virtual std::string Serialize();

    static std::shared_ptr<Column> Deserialize(const Json::Value& root);

    const CardElementType Column::GetElementType() const;

    std::string GetSize() const;
    void SetSize(const std::string value);

private:
    std::string m_size;
};
}