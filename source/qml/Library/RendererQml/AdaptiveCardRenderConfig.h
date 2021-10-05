#pragma once
#include<memory>
#include<string>

namespace RendererQml
{
    struct InputFieldConfig
    {
        //Sample Values
        std::string height{ "16" };
        std::string leftPadding{ "12" };
        std::string rightPadding{ "12" };
        std::string radius{ "5" };
    };

    //Specific Properties for InputText
    struct InputTextConfig : InputFieldConfig
    {
        //Sample Values
        std::string multiLineTextHeight{ "20" };
    };

    //Holds references to all elements
    class AdaptiveCardRenderConfig
    {
    public:
        AdaptiveCardRenderConfig(bool isDarkMode = true);
        bool isDarkMode() const;
        InputTextConfig getInputTextConfig() const;
        void setInputTextConfig(InputTextConfig config);

    private:
        bool m_isDark;
        InputTextConfig m_textInputConfig;
    };
}
