#include "pch.h"
#include "AdaptiveTemplater.h"
#include "FrameTranslator.h"

namespace AdaptiveNamespace
{
    HRESULT AdaptiveJsonTemplaterStaticsImpl::ApplyJsonTemplating(ABI::Windows::Data::Json::IJsonObject* adaptiveJson,
                                                                  ABI::Windows::Data::Json::IJsonObject* adaptiveFrame,
                                                                  ABI::Windows::Data::Json::IJsonObject* adaptiveRuntimeObject,
                                                                  ABI::Windows::Data::Json::IJsonObject** result) noexcept try
    {
        std::string adaptiveJsonString;
        RETURN_IF_FAILED(JsonObjectToString(adaptiveJson, adaptiveJsonString));

        Json::Value json;
        if (!adaptiveJsonString.empty())
        {
            json = ParseUtil::GetJsonValueFromString(adaptiveJsonString);
        }

        Json::Value frame;
        if (adaptiveFrame)
        {
            std::string adaptiveFrameString;
            RETURN_IF_FAILED(JsonObjectToString(adaptiveFrame, adaptiveFrameString));
            frame = ParseUtil::GetJsonValueFromString(adaptiveFrameString);
        }

        Json::Value runtimeObject;
        if (adaptiveRuntimeObject)
        {
            std::string adaptiveRuntimeObjectString;
            RETURN_IF_FAILED(JsonObjectToString(adaptiveRuntimeObject, adaptiveRuntimeObjectString));
            runtimeObject = ParseUtil::GetJsonValueFromString(adaptiveRuntimeObjectString);
        }

        Json::Value jsonCppResult = ::ApplyJsonTemplating(json, frame, runtimeObject);

        Json::FastWriter writer;
        std::string resultString = writer.write(jsonCppResult);
        return StringToJsonObject(resultString, result);
    }
    CATCH_RETURN;
}
