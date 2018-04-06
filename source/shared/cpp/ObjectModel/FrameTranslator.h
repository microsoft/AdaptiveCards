#include "pch.h"
#include "json/json.h"
#include "SharedAdaptiveCard.h"

class AdaptiveCards::AdaptiveCard;

Json::Value ApplyFrame(const Json::Value& templatedCard, const Json::Value& frame);

void PruneCard(std::shared_ptr<AdaptiveCards::AdaptiveCard>);