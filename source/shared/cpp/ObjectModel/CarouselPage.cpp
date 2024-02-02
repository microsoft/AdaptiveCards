// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "CarouselPage.h"

using namespace AdaptiveCards;

namespace AdaptiveCards
{
std::shared_ptr<BaseCardElement> CarouselPageParser::Deserialize(ParseContext& context, const Json::Value& value)
{
    auto carouselPage = StyledCollectionElement::Deserialize<CarouselPage>(context, value);

    carouselPage->SetRtl(ParseUtil::GetOptionalBool(value, AdaptiveCardSchemaKey::Rtl));

    return carouselPage;
}

} // namespace AdaptiveCards
