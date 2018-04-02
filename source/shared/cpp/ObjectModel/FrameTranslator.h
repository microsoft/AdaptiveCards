#include "pch.h"
#include "json/json.h"
#include "SharedAdaptiveCard.h"

class AdaptiveCards::AdaptiveCard;

void ApplyFrame(const Json::Value& templatedCard, const Json::Value& frame, Json::Value& result);

void PruneCard(std::shared_ptr<AdaptiveCards::AdaptiveCard>);