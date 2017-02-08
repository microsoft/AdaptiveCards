#pragma once

#include<string>
#include <memory>
#include "BaseCardElement.h"
#include "Enums.h"

namespace AdaptiveCards
{
class TextBlock : public BaseCardElement
{
public:
    TextBlock();
    TextBlock(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, Size size, std::string speak, std::string text, TextSize textSize, TextWeight textWeight, bool isSubtle, bool wrap);

    static std::shared_ptr<TextBlock> Deserialize(const Json::Value& root);

    virtual std::string Serialize();

    std::string GetText() const;
    void SetText(const std::string value);

    TextSize GetTextSize() const;
    void SetTextSize(const TextSize value);

    TextWeight GetTextWeight() const;
    void SetTextWeight(const TextWeight value);

    bool GetWrap() const;
    void SetWrap(const bool value);

    bool GetIsSubtle() const;
    void SetIsSubtle(const bool value);

private:
    std::string m_text;
    TextSize m_textSize;
    TextWeight m_textWeight;
    bool m_isSubtle;
    bool m_wrap;
};
}