#pragma once

#include "pch.h"
#include "ElementParserRegistration.h"
#include "ActionParserRegistration.h"
#include "AdaptiveCardParseWarning.h"

namespace AdaptiveSharedNamespace
{
    class ParseContext
    {
    public:
        ParseContext();
        ParseContext(std::shared_ptr<ElementParserRegistration> elementRegistration,
                     std::shared_ptr<ActionParserRegistration> actionRegistration);

        std::shared_ptr<ElementParserRegistration> elementParserRegistration;
        std::shared_ptr<ActionParserRegistration> actionParserRegistration;
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings;

        void PushElement(const std::tuple<std::string, unsigned int, bool>& ids);
        void PopElement();

    private:
        static const unsigned int InvalidFallbackId = 0U;
        unsigned int GetNearestFallbackId(const unsigned int skipId) const;

        // (ID, internal ID, isFallback)[]
        std::vector<std::tuple<std::string, unsigned int, bool>> m_idStack;

        // note: not enum class because we don't want typed values
        enum TupleIndex : unsigned int
        {
            Id = 0U,
            InternalId,
            IsFallback
        };

        // ID -> (internal ID, fallback ID)
        std::unordered_multimap<std::string, std::pair<unsigned int, unsigned int>> m_elementIds;
    };
}
