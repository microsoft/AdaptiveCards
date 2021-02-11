#pragma once

#include "pch.h"

namespace RendererQml
{

    enum class Code
    {
        RenderException = 1
    };

    class AdaptiveWarning
    {
    public:
        AdaptiveWarning(Code code, const std::string& message);
        Code GetStatusCode() const;
        const std::string& GetReason() const;

    private:
        const Code m_code;
        const std::string m_message;
    };

}
