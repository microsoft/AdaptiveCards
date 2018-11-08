#include "pch.h"
#include "ParseContext.h"

namespace AdaptiveSharedNamespace
{
    ParseContext::ParseContext() :
        elementParserRegistration{std::make_shared<ElementParserRegistration>()},
        actionParserRegistration{std::make_shared<ActionParserRegistration>()},
        elementIds{std::make_shared<std::unordered_set<std::string>>()},
        warnings{}
    {
    }

    ParseContext::ParseContext(std::shared_ptr<ElementParserRegistration> elementRegistration, std::shared_ptr<ActionParserRegistration> actionRegistration, std::shared_ptr<std::unordered_set<std::string>> ids) : warnings{}
    {
        elementParserRegistration = (elementRegistration) ? elementRegistration : std::make_shared<ElementParserRegistration>();
        actionParserRegistration = (actionRegistration) ? actionRegistration : std::make_shared<ActionParserRegistration>();
        elementIds = (ids) ? ids : std::make_shared<std::unordered_set<std::string>>();
    }
}
