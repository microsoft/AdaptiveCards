#include "pch.h"
#include "json/json.h"
#include "SharedAdaptiveCard.h"

class AdaptiveCards::AdaptiveCard;

Json::Value ApplyJsonTemplating(const Json::Value& templatedCard, const Json::Value& frame);
