#include "pch.h"
#include "Carousel.h"

using namespace AdaptiveCards;

namespace AdaptiveCards
{
Carousel::Carousel() : CollectionCoreElement(CardElementType::Carousel)
{
    PopulateKnownPropertiesSet();
}

void Carousel::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({
        AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HeightInPixels),
        AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::InitialPage),
        AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Loop),
        AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Orientation),
        AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Pages),
        AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Timer),
    });
}

Json::Value Carousel::SerializeToJsonValue() const
{
    Json::Value root = CollectionCoreElement::SerializeToJsonValue();

    if (!m_heightInPixels.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HeightInPixels)] = m_heightInPixels;
    }

    if (m_initialPage.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::InitialPage)] = m_initialPage.value_or(0);
    }

    if (m_autoLoop.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Loop)] = m_autoLoop.value_or(false);
    }

    if (!m_pages.empty())
    {
        const std::string& pagesPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Pages);
        root[pagesPropertyName] = Json::Value(Json::arrayValue);
        for (const auto& page : m_pages)
        {
            root[pagesPropertyName].append(page->SerializeToJsonValue());
        }
    }

    if (m_orientation.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Orientation)] =
            CarouselOrientationToString(m_orientation.value_or(CarouselOrientation::Horizontal));
    }

    if (m_timer.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Timer)] = m_timer.value_or(0);
    }

    return root;
}

std::vector<std::shared_ptr<AdaptiveCards::CarouselPage>>& Carousel::GetPages()
{
    return m_pages;
}

const std::vector<std::shared_ptr<AdaptiveCards::CarouselPage>>& Carousel::GetPages() const
{
    return m_pages;
}

void Carousel::SetPages(const std::vector<std::shared_ptr<AdaptiveCards::CarouselPage>>& value)
{
    m_pages = value;
}

std::string Carousel::GetHeightInPixels() const
{
    return m_heightInPixels;
}

void Carousel::SetHeightInPixels(const std::string& value)
{
    m_heightInPixels = value;
}

std::optional<unsigned long> Carousel::GetTimer() const
{
    return m_timer;
}

void Carousel::SetTimer(const std::optional<unsigned long>& value)
{
    m_timer = value;
}

std::optional<unsigned int> Carousel::GetInitialPage() const
{
    return m_initialPage;
}

void Carousel::SetInitialPage(const std::optional<unsigned int>& value)
{
    m_initialPage = value;
}

std::optional<CarouselOrientation> Carousel::GetOrientation() const
{
    return m_orientation;
}

void Carousel::SetOrientation(const std::optional<CarouselOrientation>& value)
{
    m_orientation = value;
}

std::optional<bool> Carousel::GetAutoLoop() const
{
    return m_autoLoop;
}

void Carousel::setAutoLoop(const std::optional<bool>& value)
{
    m_autoLoop = value;
}

void Carousel::DeserializeChildren(ParseContext& context, const Json::Value& value)
{
    if (auto deserializedPages =
            ParseUtil::GetElementCollection<CarouselPage>(true, context, value, AdaptiveCardSchemaKey::Pages, false);
        !deserializedPages.empty())
    {
        m_pages = deserializedPages;
    }
}

std::shared_ptr<BaseCardElement> CarouselParser::Deserialize(ParseContext& context, const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::Carousel);

    context.AddProhibitedElementType(m_prohibitedTypesList);

    std::shared_ptr<Carousel> carousel = CollectionCoreElement::Deserialize<Carousel>(context, value);

    carousel->SetHeightInPixels(ParseUtil::GetString(value, AdaptiveCardSchemaKey::HeightInPixels));

    carousel->SetInitialPage(ParseUtil::GetOptionalUnsignedInt(value, AdaptiveCardSchemaKey::InitialPage));

    carousel->SetTimer(ParseUtil::GetOptionalUnsignedInt(value, AdaptiveCardSchemaKey::Timer));

    carousel->setAutoLoop(ParseUtil::GetOptionalBool(value, AdaptiveCardSchemaKey::Loop));

    carousel->SetOrientation(ParseUtil::GetOptionalEnumValue<CarouselOrientation>(
        value, AdaptiveCardSchemaKey::Orientation, CarouselOrientationFromString));

    return carousel;
}

std::shared_ptr<BaseCardElement> CarouselParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return CarouselParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
} // namespace AdaptiveCards
