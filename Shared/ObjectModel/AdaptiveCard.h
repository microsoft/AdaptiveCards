#pragma once
#include <string>
#include <vector>
#include <memory>
#include "ICardElement.h"

namespace AdaptiveCards
{
    class Container;

    class AdaptiveCard
    {
    public:
        AdaptiveCard(std::wstring title, std::wstring description1, std::wstring description2, std::shared_ptr<Container> root);

        std::wstring GetTitle() const;
        std::wstring GetDescription1() const;
        std::wstring GetDescription2() const;

        const Container* GetRoot() const;

    private:
        std::wstring m_title;
        std::wstring m_description1;
        std::wstring m_description2;
        std::shared_ptr<Container> m_root;

    };
}