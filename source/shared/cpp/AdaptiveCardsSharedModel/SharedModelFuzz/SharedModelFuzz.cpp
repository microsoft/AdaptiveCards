// SharedModelFuzz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <optional>
#include "Enums.h"
#include "json/json.h"

#include "SharedAdaptiveCard.h"
#include "BaseCardElement.h"

#ifdef __cplusplus
#define FUZZ_EXPORT extern "C" __declspec(dllexport)
#else
#define FUZZ_EXPORT __declspec(dllexport)
#endif
FUZZ_EXPORT int __cdecl LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    std::string fuzzInput;
    fuzzInput.assign(reinterpret_cast<const char*>(data), size);

    try
    {
        auto parsedCard = AdaptiveCards::AdaptiveCard::DeserializeFromString(fuzzInput, "1.6");
        if (parsedCard)
        {
            auto warnings = parsedCard->GetWarnings();
            auto card = parsedCard->GetAdaptiveCard();
            auto actions = card->GetActions();
            auto body = card->GetBody();
            auto serializedCard = card->Serialize();
        }
    }
    catch (const AdaptiveCards::AdaptiveCardParseException&) {
        // Ignore parse exceptions
    }
    catch (const Json::Exception&) {
        // Ignore JSON exceptions
    }

    return 0;
}
