#pragma once

#include "pch.h"
#include "Enums.h"
#include "json\json.h"

namespace AdaptiveCards
{
class Container;
class BaseCardElement
{
public:
    BaseCardElement(CardElementType type, std::shared_ptr<Container> parent, HorizontalAlignment horizontalAlignment, CardElementSize size, std::string speak);
    BaseCardElement(CardElementType type);

    virtual ~BaseCardElement();

    std::shared_ptr<Container> GetParent() const;
    void SetContainer(std::shared_ptr<Container> container);

    HorizontalAlignment GetHorizontalAlignment() const;
    void SetHorizontalAlignment(const HorizontalAlignment value);

    CardElementSize GetSize() const;
    void SetSize(const CardElementSize value);

    std::string GetSpeak() const;
    void SetSpeak(const std::string value);

    const CardElementType GetElementType() const;

    virtual std::string Serialize() = 0;

private:
    std::weak_ptr<Container> m_parent;
    HorizontalAlignment m_horizontalAlignment;
    CardElementSize m_size;
    std::string m_speak;
    CardElementType m_type;
};
}

