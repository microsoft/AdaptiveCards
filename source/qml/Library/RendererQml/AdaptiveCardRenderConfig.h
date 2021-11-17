#pragma once
#include<memory>
#include<string>

namespace RendererQml
{
    struct CardConfig
    {
        int cardRadius{ 8 };
    };

    struct InputFieldConfig
    {
        std::string backgroundColorNormal{ "#FF0F0F0F" };
        std::string backgroundColorOnHovered{ "#0DFFFFFF" };
        std::string backgroundColorOnPressed{ "#4DFFFFFF" };
        std::string borderColorNormal{ "#80FFFFFF" };
        std::string borderColorOnFocus{ "#FF64B4FA" };
        std::string placeHolderColor{ "#B3FFFFFF" };
        std::string textColor{ "#F2FFFFFF" };
        std::string clearIconColorNormal{ "#B3FFFFFF" };
        std::string clearIconColorOnFocus{ "#FF64B4FA" };
        int height{ 32 };
        int pixelSize{ 16 };
        int borderRadius{ 8 };
        int borderWidth{ 1 };
        int clearIconSize{ 16 };
        int clearIconHorizontalPadding{ 12 };
        int textHorizontalPadding{ 12 };
        int textVerticalPadding{ 4 };
    };

    struct InputTextConfig : InputFieldConfig
    {
        int multiLineTextHeight{ 96 };
        int multiLineTextTopPadding{ 7 };
        int multiLineTextBottomPadding{ 4 };
    };

    struct InputNumberConfig : InputFieldConfig
    {
        std::string upDownIconColor{ "#F2FFFFFF" };
        int upDownButtonWidth{ 31 };
        int upDownIconSize{ 16 };
    };

    struct InputTimeConfig : InputFieldConfig
    {
        std::string timeIconColorNormal{ "#F2FFFFFF" };
        std::string timeIconColorOnFocus{ "#FF64B4FA" };
        std::string timePickerBorderColor{ "#80FFFFFF" };
        std::string timePickerBackgroundColor{ "#FF0F0F0F" };
        std::string timePickerElementColorNormal{ "#FF0F0F0F" };
        std::string timePickerElementColorOnHover{ "#0DFFFFFF" };
        std::string timePickerElementColorOnFocus{ "#FF1170CF" };
        std::string timePickerElementTextColorNormal{ "#F2FFFFFF" };
        std::string timePickerElementTextColorOnHighlighted{ "#F2FFFFFF" };
        int timeIconHorizontalPadding{ 12 };
        int timePickerBorderRadius{ 12 };
        int timePickerWidth12Hour{ 200 };
        int timePickerWidth24Hour{ 134 };
        int timePickerHeight{ 280 };
        int timePickerColumnSpacing{ 16 };
        int timePickerHoursAndMinutesTagWidth{ 43 };
        int timePickerAMPMTagWidth{ 50 };
        int timePickerElementHeight{ 32 };
        int timePickerMargins{ 16 };
        int timePickerSpacing{ 4 };
        int timePickerElementRadius{ 4 };
    };

    struct InputDateConfig : InputFieldConfig
    {
        std::string dateIconColorNormal{ "#F2FFFFFF" };
        std::string dateIconColorOnFocus{ "#FF64B4FA" };
        std::string calendarBorderColor{ "#80FFFFFF" };
        std::string calendarBackgroundColor{ "#FF0F0F0F" };
        std::string dateElementColorNormal{ "#FF0F0F0F" };
        std::string dateElementColorOnHover{ "#0DFFFFFF" };
        std::string dateElementColorOnFocus{ "#FF1170CF" };
        std::string dateElementTextColorNormal{ "#F2FFFFFF" };
        std::string dateElementTextColorOnHighlighted{ "#F2FFFFFF" };
        std::string notAvailabledateElementTextColor{ "#B3FFFFFF" };
        int dateElementSize{ 32 };
        int dateIconHorizontalPadding{ 12 };
        int calendarBorderRadius{ 12 };
        int calendarWidth{ 248 };
        int calendarHeight{ 293 };
        int calendarHeaderTextSize{ 16 };
        int dateGridTopMargin{ 14 };
        int calendarDayTextSize{ 16 };
        int calendarDateTextSize{ 16 };
        int arrowIconSize{ 28 };
    };

    struct InputChoiceSetDropDownConfig : InputFieldConfig
    {
        std::string arrowIconColor{ "#F2FFFFFF" };
        std::string dropDownElementColorPressed{ "#4DFFFFFF" };
        std::string dropDownElementColorHovered{ "#0DFFFFFF" };
        std::string dropDownElementColorNormal{ "#FF0F0F0F" };
        std::string dropDownBorderColor{ "#80FFFFFF" };
        std::string dropDownBackgroundColor{ "#FF0F0F0F" };
        float arrowIconHorizontalPadding{ 9.5 };
        int arrowIconVerticalPadding{ 8 };
        int arrowIconWidth{ 13 };
        int arrowIconHeight{ 7 };
        int textHorizontalPadding{ 12 };
        int dropDownElementHeight{ 40 };
        int dropDownElementHorizontalPadding{ 12 };
        int dropDownElementVerticalPadding{ 8 };
        int dropDownElementRadius{ 8 };
        int dropDownElementTextHorizontalPadding{ 12 };
        int dropDownRadius{ 12 };
        int dropDownPadding{ 8 };
        int dropDownHeight{ 216 };
    };

    struct ToggleButtonConfig
    {
        std::string colorOnCheckedAndPressed{ "#FF1170CF" };
        std::string colorOnCheckedAndHovered{ "#FF3492EB" };
        std::string colorOnChecked{ "#FF64B4FA" };
        std::string colorOnUncheckedAndPressed{ "#33FFFFFF" };
        std::string colorOnUncheckedAndHovered{ "#33FFFFFF" };
        std::string colorOnUnchecked{ "#1CFFFFFF" };
        std::string borderColorOnCheckedAndPressed{ "#FF1170CF" };
        std::string borderColorOnCheckedAndHovered{ "#FF3492EB" };
        std::string borderColorOnChecked{ "#FF64B4FA" };
        std::string borderColorOnUncheckedAndPressed{ "#33FFFFFF" };
        std::string borderColorOnUncheckedAndHovered{ "#33FFFFFF" };
        std::string borderColorOnUnchecked{ "#1CFFFFFF" };
        std::string textColor{ "#F2FFFFFF" };
        std::string radioButtonInnerCircleColorOnChecked{ "#F2000000" };
        std::string checkBoxIconColorOnChecked{ "#F2000000" };
        int radioButtonOuterCircleSize{ 16 };
        int radioButtonInnerCircleSize{ 6 };
        int checkBoxSize{ 16 };
        int checkBoxBorderRadius{ 2 };
        int pixelSize{ 16 };
        int borderWidth{ 1 };
    };

    struct ActionButtonConfig
    {
        std::string buttonColorNormal{ "#F2FFFFFF" };
        std::string buttonColorDisabled{ "33FFFFFF" };
        std::string buttonColorHovered{ "#CCFFFFFF" };
        std::string buttonColorPressed{ "#B3FFFFFF" };
        std::string borderColorNormal{ "#F2FFFFFF" };
        std::string borderColorHovered{ "#F2FFFFFF" };
        std::string borderColorPressed{ "#F2FFFFFF" };
        std::string borderColorFocussed{ "#FF64B4FA" };
        std::string textColorNormal{ "#F2000000" };
        std::string textColorHovered{ "#F2000000" };
        std::string textColorPressed{ "#F2000000" };
        std::string textColorDisabled{ "#66FFFFFF" };
        std::string fontWeight{ "Font.DemiBold" };
        int buttonRadius = 16;
        int horizotalPadding = 10;
        int verticalPadding = 5;
        int buttonHeight = 28;
        int iconWidth = 12;
        int iconHeight = 12;
        int imageSize = 14;
        int iconTextSpacing = 5;
        int pixelSize = 14;
    };

    struct ActionButtonsConfig
    {
        ActionButtonConfig primaryColorConfig;
        ActionButtonConfig secondaryColorConfig;
        ActionButtonConfig positiveColorConfig;
        ActionButtonConfig destructiveColorConfig;

        ActionButtonsConfig()
        {
            secondaryColorConfig.buttonColorNormal = "#00FFFFFF";
            secondaryColorConfig.buttonColorHovered = "#12FFFFFF";
            secondaryColorConfig.buttonColorPressed = "#33FFFFFF";
            secondaryColorConfig.borderColorNormal = "#4DFFFFFF";
            secondaryColorConfig.borderColorHovered = "#4DFFFFFF";
            secondaryColorConfig.borderColorPressed = "#4DFFFFFF";
            secondaryColorConfig.borderColorFocussed = "#FF64B4FA";
            secondaryColorConfig.textColorNormal = "#F2FFFFFF";
            secondaryColorConfig.textColorHovered = "#F2FFFFFF";
            secondaryColorConfig.textColorPressed = "#F2FFFFFF";

            positiveColorConfig.buttonColorNormal = "#00FFFFFF";
            positiveColorConfig.buttonColorHovered = "#FF185E46";
            positiveColorConfig.buttonColorPressed = "#FF134231";
            positiveColorConfig.borderColorNormal = "#FF3CC29A";
            positiveColorConfig.borderColorHovered = "#FF185E46";
            positiveColorConfig.borderColorPressed = "#FF134231";
            positiveColorConfig.borderColorFocussed = "#FF64B4FA";
            positiveColorConfig.textColorNormal = "#FF3CC29A";
            positiveColorConfig.textColorHovered = "#F2FFFFFF";
            positiveColorConfig.textColorPressed = "#F2FFFFFF";

            destructiveColorConfig.buttonColorNormal = "#00FFFFFF";
            destructiveColorConfig.buttonColorHovered = "#FFAB0A15";
            destructiveColorConfig.buttonColorPressed = "#FF780D13";
            destructiveColorConfig.borderColorNormal = "#FFFC8B98";
            destructiveColorConfig.borderColorHovered = "#FFAB0A15";
            destructiveColorConfig.borderColorPressed = "#FF780D13";
            destructiveColorConfig.borderColorFocussed = "#FF64B4FA";
            destructiveColorConfig.textColorNormal = "#FFFC8B98";
            destructiveColorConfig.textColorHovered = "#F2FFFFFF";
            destructiveColorConfig.textColorPressed = "#F2FFFFFF";
        }
    };

    //Holds references to all elements
    class AdaptiveCardRenderConfig
    {
    public:
        AdaptiveCardRenderConfig(bool isDarkMode = true);
        bool isDarkMode() const;
        CardConfig getCardConfig() const;
        void setCardConfig(CardConfig config);
        InputTextConfig getInputTextConfig() const;
        void setInputTextConfig(InputTextConfig config);
        InputNumberConfig getInputNumberConfig() const;
        void setInputNumberConfig(InputNumberConfig config);
        InputTimeConfig getInputTimeConfig() const;
        void setInputTimeConfig(InputTimeConfig config);
        InputChoiceSetDropDownConfig getInputChoiceSetDropDownConfig() const;
        void setInputChoiceSetDropDownConfig(InputChoiceSetDropDownConfig config);
        ToggleButtonConfig getToggleButtonConfig() const;
        void setToggleButtonConfig(ToggleButtonConfig config);
        InputDateConfig getInputDateConfig() const;
        void setInputDateConfig(InputDateConfig config);
        ActionButtonsConfig getActionButtonsConfig() const;
        void setActionButtonsConfig(ActionButtonsConfig config);

    private:
        bool m_isDark;
        CardConfig m_cardConfig;
        InputTextConfig m_textInputConfig;
        InputNumberConfig m_numberInputConfig;
        InputTimeConfig m_timeInputConfig;
        InputChoiceSetDropDownConfig m_choiceSetDropdownInputConfig;
        ToggleButtonConfig m_toggleButtonConfig;
        InputDateConfig m_dateInputConfig;
        ActionButtonsConfig m_actionButtonsConfig;
    };
}
