#pragma once

#include <memory>
#include "enums.h"
#include "container.h"

namespace AdaptiveCards
{
class ICardElement
{
public:
    ICardElement(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, Size size, std::string speak);
    virtual ~ICardElement() = 0 {};

    std::shared_ptr<Container> GetContainer() const;

    HorizontalAlignment GetHorizontalAlignment() const;
    void SetHorizontalAlignment(const HorizontalAlignment value);

    Size GetSize() const;
    void SetSize(const Size value);

    std::string GetSpeak() const;
    void SetSpeak(const std::string value);

    virtual std::string Serialize() = 0;

private:
    std::weak_ptr<Container> m_container;
    HorizontalAlignment m_horizontalAlignment;
    Size m_size;
    std::string m_speak;
};
}

