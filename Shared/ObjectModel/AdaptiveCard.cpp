#include "AdaptiveCard.h"

namespace AdaptiveCards
{
    AdaptiveCard::AdaptiveCard(std::wstring title, std::wstring description1, std::wstring description2, std::shared_ptr<Container> root) : m_title(title), m_description1(description1), m_description2(description2), m_root(root) {}

    std::wstring AdaptiveCard::GetTitle() const
    {
        return m_title;
    }

    std::wstring AdaptiveCard::GetDescription1() const
    {
        return m_description1;
    }

    std::wstring AdaptiveCard::GetDescription2() const
    {
        return m_description2;
    }

    const Container* AdaptiveCard::GetRoot() const
    {
        return m_root.get();
    }
};

