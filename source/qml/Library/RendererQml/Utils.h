#pragma once

#include "pch.h"
#include "HostConfig.h"

namespace RendererQml
{
	enum CheckBoxType
	{
		Toggle,
		RadioButton,
		CheckBox,
		ComboBox
	};

	struct Checkbox
	{
		const std::string id;
		CheckBoxType type = CheckBoxType::Toggle;
		const std::string text;
		const std::string value;
		const std::string valueOn;
		const std::string valueOff;
		const bool isWrap;
		const bool isVisible;
		const bool isChecked;

		Checkbox(std::string id, CheckBoxType type, const std::string text, const std::string value, const std::string valueOn, const std::string valueOff, const bool isWrap, const bool isVisible, const bool isChecked)
			: id(id),
			type(type),
			text(text),
			value(value),
			valueOn(valueOn),
			valueOff(valueOff),
			isWrap(isWrap),
			isVisible(isVisible),
			isChecked(isChecked)
		{}

		Checkbox(std::string id, CheckBoxType type, const std::string text, const std::string value, const bool isWrap, const bool isVisible, const bool isChecked)
			: id(id),
			type(type),
			text(text),
			value(value),
			isWrap(isWrap),
			isVisible(isVisible),
			isChecked(isChecked)
		{}
	};	
	
	using Checkboxes = std::vector<Checkbox>;

	struct ChoiceSet
	{
		const std::string id;
		const bool isMultiSelect;
		AdaptiveCards::ChoiceSetStyle style = AdaptiveCards::ChoiceSetStyle::Compact;
		const std::vector<std::string> values;
		Checkboxes choices;
		const std::string placeholder;

		ChoiceSet(const std::string id, const bool isMultiSelect, AdaptiveCards::ChoiceSetStyle style, const std::vector<std::string> values, Checkboxes choices, const std::string placeholder)
			: id(id),
			isMultiSelect(isMultiSelect),
			style(style),
			values(values),
			choices(choices),
			placeholder(placeholder)
		{}
	};

	class Utils
    {
    public:

        template <class T, class U>
        static bool IsInstanceOfSmart(U u);

        template <class T, class U>
        static bool IsInstanceOf(U u);

        static int HexStrToInt(const std::string& str);
        static int GetSpacing(const AdaptiveCards::SpacingConfig& spacingConfig, const AdaptiveCards::Spacing spacing);
        static const AdaptiveCards::ContainerStyleDefinition& GetContainerStyle(const AdaptiveCards::ContainerStylesDefinition& containerStyles, AdaptiveCards::ContainerStyle style);

        static bool CaseInsensitiveCompare(const std::string& str1, const std::string& str2);
        static bool IsNullOrWhitespace(const std::string& str);
        static std::string& RightTrim(std::string& str);
        static std::string& LeftTrim(std::string& str);
        static std::string& Trim(std::string& str);
        static std::string& Replace(std::string& str, char what, char with);
        static std::string& Replace(std::string& str, const std::string& what, const std::string& with);
        static std::string& ToLower(std::string& str);
        static bool TryParse(const std::string& str, double& value);
        static bool EndsWith(const std::string& str, const std::string& end);

		//Element Helpers
		static std::string GetHorizontalAlignment(std::string alignType);
		static std::string GetVerticalAlignment(std::string alignType);
		static std::string GetHorizontalAnchors(std::string alignType);
		static std::string GetVerticalAnchors(std::string alignType);
		static std::string GetWeight(AdaptiveCards::TextWeight weight);

		static std::string GetDate(const std::string& date);
		static const bool isValidTime(const std::string& time);
		static std::string defaultTimeto12hour(std::string& defaultTime);
        static std::string defaultTimeto24hour(std::string& defaultTime);

        static std::string ConvertToLowerIdValue(const std::string& value);

		static bool isSystemTime12Hour();

		static RendererQml::DateFormat GetSystemDateFormat();

		static std::vector<std::string> splitString(const std::string& string, char delimiter);
		static std::string HandleEscapeSequences(std::string& text);

    private:
        Utils() {}
		static std::string FetchSystemDateTime(const std::string& fetchFormat);
    };

    template<class T, class U>
    inline bool Utils::IsInstanceOfSmart(U u)
    {
        return std::dynamic_pointer_cast<T>(u) != nullptr;
    }

    template<class T, class U>
    inline bool Utils::IsInstanceOf(U u)
    {
        return dynamic_cast<T>(u) != nullptr;
    }

    class TextUtils
    {
    public:
        static std::string ApplyTextFunctions(const std::string& text, const std::string& lang);
        static std::locale GetValidCultureInfo(const std::string& lang);
        static bool GetLocalTime(const std::string& tzOffset, std::tm& tm, std::tm& lt);

    private:
        static std::regex m_textFunctionRegex;
    };
}
