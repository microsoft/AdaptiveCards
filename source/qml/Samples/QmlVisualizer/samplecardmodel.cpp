#include "samplecardmodel.h"
#include "samplecardlist.h"
#include "adaptivecard_light_config.h"
#include "adaptivecard_dark_config.h"
#include "AdaptiveCardRenderConfig.h"

#include <windows.h>
#include <shellapi.h>
#include <mutex>

using namespace RendererQml;

std::mutex images_mutex;

SampleCardModel::SampleCardModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{

    std::shared_ptr<AdaptiveSharedNamespace::HostConfig> hostConfig = std::make_shared<AdaptiveSharedNamespace::HostConfig>(AdaptiveSharedNamespace::HostConfig::DeserializeFromString(LightConfig::lightConfig));
    auto renderConfig = getRenderConfig(false);
    renderer_ptr = std::make_shared<AdaptiveCardQmlRenderer>(AdaptiveCardQmlRenderer(hostConfig, renderConfig));
}

int SampleCardModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->cardList().size();
}

QVariant SampleCardModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant(QStringLiteral("error"));

    const Card card = mList->cardList().at(index.row());

    switch (role)
    {
    case CardNameRole:
        return QVariant(card.CardName);
    case CardJsonString:
        return QVariant(card.CardJson);
    }
    return QVariant();
}

QHash<int, QByteArray> SampleCardModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[CardNameRole] = "CardName";
    names[CardJsonString] = "CardJson";
    return names;
}

SampleCardList *SampleCardModel::list() const
{
    return mList;
}

void SampleCardModel::setList(SampleCardList *list)
{
    beginResetModel();

    if(mList)
    {
        mList->disconnect(this);
    }
    mList = list;

    endResetModel();
}

std::shared_ptr<AdaptiveCards::HostConfig> SampleCardModel::getHostConfig()
{
    std::shared_ptr<AdaptiveCards::HostConfig> hostConfig = std::make_shared<AdaptiveCards::HostConfig>();

    AdaptiveCards::SpacingConfig spacingConfig = hostConfig->GetSpacing();
    spacingConfig.paddingSpacing = 15;
    hostConfig->SetSpacing(spacingConfig);

    AdaptiveCards::SeparatorConfig separatorConfig = hostConfig->GetSeparator();
    separatorConfig.lineColor = "#FF707070";
    hostConfig->SetSeparator(separatorConfig);

    AdaptiveCards::FontSizesConfig fontSizesConfig = hostConfig->GetFontSizes();
    fontSizesConfig.SetFontSize(AdaptiveCards::TextSize::Small, 12);
    fontSizesConfig.SetFontSize(AdaptiveCards::TextSize::Medium, 17);
    fontSizesConfig.SetFontSize(AdaptiveCards::TextSize::Large, 21);
    fontSizesConfig.SetFontSize(AdaptiveCards::TextSize::ExtraLarge, 26);
    fontSizesConfig.SetFontSize(AdaptiveCards::TextSize::Default, 14);
    hostConfig->SetFontSizes(fontSizesConfig);

    AdaptiveCards::ImageSizesConfig imageSizesConfig = hostConfig->GetImageSizes();
    imageSizesConfig.smallSize = 40;
    imageSizesConfig.mediumSize = 80;
    imageSizesConfig.largeSize = 160;
    hostConfig->SetImageSizes(imageSizesConfig);

    auto containerStyles = hostConfig->GetContainerStyles();
    containerStyles.emphasisPalette.backgroundColor = "#AABBCCDD";
    hostConfig->SetContainerStyles(containerStyles);

    return hostConfig;
}

QString SampleCardModel::generateQml(const QString& cardQml)
{
    std::map<std::string, std::string> urls;

    std::shared_ptr<int> imgCounter{ 0 };

    std::shared_ptr<AdaptiveCards::ParseResult> mainCard = AdaptiveCards::AdaptiveCard::DeserializeFromString(cardQml.toStdString(), "2.0");
    std::shared_ptr<RenderedQmlAdaptiveCard> result = renderer_ptr->RenderCard(mainCard->GetAdaptiveCard());
    const auto generatedQml = result->GetResult();
	
    //SYNCHRONOUS
    ImageDownloader::clearImageFolder();
	
	generatedQml->Transform([&urls](QmlTag& genQml)
	{
		if (genQml.GetElement() == "Frame" && genQml.HasProperty("readonly property bool hasBackgroundImage"))
		{
            auto url = genQml.GetProperty("property var imgSource");
            urls[genQml.GetId()] = Utils::Replace(url, "\"", "");

            //Temp
            char* imgUrl = ImageDownloader::Convert(url);
            const std::string imageName = genQml.GetId() + ".jpg";

            if (ImageDownloader::download_jpeg(imageName, imgUrl))
            {
                genQml.Property("property var imgSource", "\"" + getImagePath(imageName) + "\"");
            }
            else
            {
                printf("!! Failed to download file!");
            }
            //Temp            
		}
		else if (genQml.GetElement() == "Image" && genQml.HasProperty("readonly property bool isImage"))
		{
            auto url = genQml.GetProperty("source");
            urls[genQml.GetId()] = Utils::Replace(url, "\"", "");

            //Temp
            char* imgUrl = ImageDownloader::Convert(url);
            const std::string imageName = genQml.GetId() + ".jpg";

            if (ImageDownloader::download_jpeg(imageName, imgUrl))
            {
                genQml.Property("source", "\"" + getImagePath(imageName) + "\"");
            }
            else
            {
                printf("!! Failed to download file!");
            }
            //Temp 
		}
		else if (genQml.GetElement() == "Button" && genQml.HasProperty("readonly property bool hasIconUrl"))
		{
            auto url = genQml.GetProperty("property var imgSource");
            urls[genQml.GetId()] = Utils::Replace(url, "\"", "");

            //Temp
            char* imgUrl = ImageDownloader::Convert(url);
            const std::string imageName = genQml.GetId() + ".jpg";

            if (ImageDownloader::download_jpeg(imageName, imgUrl))
            {
                genQml.Property("property var imgSource", "\"" + getImagePath(imageName) + "\"");
            }
            else
            {
                printf("!! Failed to download file!");
            }
            //Temp 
		}
	});

	//ASYNCHRONOUS
	/*generatedQml->Transform([&urls](QmlTag& genQml)
	{
		if (genQml.GetElement() == "Frame" && genQml.HasProperty("readonly property bool hasBackgroundImage"))
		{
			auto url = genQml.GetProperty("property var imgSource");
			urls[genQml.GetId()] = Utils::Replace(url, "\"", "");
		}
		else if (genQml.GetElement() == "Image" && genQml.HasProperty("readonly property bool isImage"))
		{
			auto url = genQml.GetProperty("source");
			urls[genQml.GetId()] = Utils::Replace(url, "\"", "");
		}
		else if (genQml.GetElement() == "Button" && genQml.HasProperty("readonly property bool hasIconUrl"))
		{
			auto url = genQml.GetProperty("property var imgSource");
			urls[genQml.GetId()] = Utils::Replace(url, "\"", "");
		}
	});

	std::thread thread_object([urls]() {
		images_mutex.lock();
		const std::map<std::string, std::string> paths = rehostImage(urls);
		printf("Number of Images downloaded: %d\n", paths.size());
		images_mutex.unlock();
		});

	//Detaching the thread to make it asynchronous
	thread_object.detach();*/

	const QString generatedQmlString = QString::fromStdString(generatedQml->ToString());
    return generatedQmlString;
}

const std::map<std::string, std::string> SampleCardModel::rehostImage(const std::map<std::string, std::string>& urls)
{
	ImageDownloader::clearImageFolder();
	const std::map<std::string, std::string> file_paths = ImageDownloader::download_multiple_jpeg(urls);
	return file_paths;
}

void SampleCardModel::setTheme(const QString& theme)
{
    std::shared_ptr<AdaptiveSharedNamespace::HostConfig> hostConfig;
    bool isDark = true;

    if(theme.toStdString() == "Light")
    {
        isDark = false;
        hostConfig = std::make_shared<AdaptiveSharedNamespace::HostConfig>(AdaptiveSharedNamespace::HostConfig::DeserializeFromString(LightConfig::lightConfig));
    }
    else
    {
        hostConfig = std::make_shared<AdaptiveSharedNamespace::HostConfig>(AdaptiveSharedNamespace::HostConfig::DeserializeFromString(DarkConfig::darkConfig));
    }

    auto renderConfig = getRenderConfig(isDark);
    renderer_ptr = std::make_shared<AdaptiveCardQmlRenderer>(AdaptiveCardQmlRenderer(hostConfig, renderConfig));

    emit reloadCardOnThemeChange();
}

std::wstring SampleCardModel::toWString(const std::string& input)
{
#ifdef _WIN32
    // Convert UTF-8 to UTF-16
    if (!input.empty())
    {
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &input[0], static_cast<int>(input.length()), nullptr, 0);
        std::wstring utf16String(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, &input[0], static_cast<int>(input.length()), &utf16String[0], size_needed);
        return utf16String;
    }

    return std::wstring();
#else
    return converterToString->from_bytes(input);
#endif
}

void SampleCardModel::onAdaptiveCardButtonClicked(const QString& title, const QString& type, const QString& data)
{
    if (type == "Action.OpenUrl")
    {
        actionOpenUrlButtonClicked(title, type, data);
    }
    else if(type == "Action.Submit")
    {
        actionSubmitButtonClicked(title, type, data);
    }
}

void SampleCardModel::actionOpenUrlButtonClicked(const QString& title, const QString& type, const QString& data)
{
    QString output;
    output.append("Title: " + title + "\n");
    output.append("Type: " + type + "\n");
    output.append("Url: " + data);
    emit sendCardResponseToQml(output);

    // Open url in default browser
    ShellExecute(0, 0, toWString(data.toStdString()).c_str(), 0, 0, SW_SHOW);
}

void SampleCardModel::actionSubmitButtonClicked(const QString& title, const QString& type, const QString& data)
{
    QString output;
    output.append("Title: " + title + "\n");
    output.append("Type: " + type + "\n");
    output.append("data: " + data);
    emit sendCardResponseToQml(output);
}

const std::string SampleCardModel::getImagePath(const std::string& imageName)
{
	std::string file_path = __FILE__;
	std::string dir_path = file_path.substr(0, file_path.rfind("\\"));
    dir_path.append("\\Images\\" + imageName);
	std::replace(dir_path.begin(), dir_path.end(), '\\', '/');
	dir_path = std::string("file:/") + dir_path;

	return dir_path;
}

std::shared_ptr<AdaptiveCardRenderConfig> SampleCardModel::getRenderConfig(const bool isDark)
{
    auto renderConfig = std::make_shared<AdaptiveCardRenderConfig>(isDark);
    renderConfig->setInputTextConfig(getInputTextConfig(isDark));
    renderConfig->setInputNumberConfig(getInputNumberConfig(isDark));
    renderConfig->setInputTimeConfig(getInputTimeConfig(isDark));
    renderConfig->setInputChoiceSetDropDownConfig(getInputChoiceSetDropDownConfig(isDark));
    renderConfig->setToggleButtonConfig(getToggleButtonConfig(isDark));
    renderConfig->setInputDateConfig(getInputDateConfig(isDark));
    renderConfig->setActionButtonsConfig(getActionButtonsConfig(isDark));
    return renderConfig;
}

template <typename InputConfig>
InputConfig SampleCardModel::getInputFieldConfig(InputConfig inputConfig, const bool isDark)
{
    //Dark Values are default in the struct
    if (!isDark)
    {
        inputConfig.backgroundColorNormal = "#FFFFFFFF";
        inputConfig.backgroundColorOnHovered = "#0A000000";
        inputConfig.backgroundColorOnPressed = "#4D000000";
        inputConfig.borderColorNormal = "#80000000";
        inputConfig.borderColorOnFocus = "#FF1170CF";
        inputConfig.placeHolderColor = "#99000000";
        inputConfig.textColor = "#F2000000";
        inputConfig.clearIconColorNormal = "#99000000";
        inputConfig.clearIconColorOnFocus = "#FF1170CF";
    }

    return inputConfig;
}

InputTextConfig SampleCardModel::getInputTextConfig(const bool isDark)
{
    InputTextConfig textInputConfig;
    textInputConfig = getInputFieldConfig(textInputConfig, isDark);
    return textInputConfig;
}

InputNumberConfig SampleCardModel::getInputNumberConfig(const bool isDark)
{
    InputNumberConfig numberInputConfig;
    numberInputConfig = getInputFieldConfig(numberInputConfig, isDark);

    if (!isDark)
    {
        numberInputConfig.upDownIconColor = "#F2000000";
    }

    return numberInputConfig;
}

InputTimeConfig SampleCardModel::getInputTimeConfig(const bool isDark)
{
    InputTimeConfig timeInputConfig;
    timeInputConfig = getInputFieldConfig(timeInputConfig, isDark);

    if (!isDark)
    {
        timeInputConfig.timeIconColorNormal = "#F2000000";
        timeInputConfig.timeIconColorOnFocus = "#FF1170CF";
        timeInputConfig.timePickerBorderColor = "#80000000";
        timeInputConfig.timePickerBackgroundColor = "#FFFFFFFF";
        timeInputConfig.timePickerElementColorNormal = "#FFFFFFFF";
        timeInputConfig.timePickerElementColorOnHover = "#12000000";
        timeInputConfig.timePickerElementColorOnFocus = "#FF1170CF";
        timeInputConfig.timePickerElementTextColorNormal = "#F2000000";
    }

    return timeInputConfig;
}

InputDateConfig SampleCardModel::getInputDateConfig(const bool isDark)
{
    InputDateConfig dateInputConfig;
    dateInputConfig = getInputFieldConfig(dateInputConfig, isDark);

    if (!isDark)
    {
        dateInputConfig.dateIconColorNormal = "#F2000000";
        dateInputConfig.dateIconColorOnFocus = "#FF1170CF";
        dateInputConfig.calendarBorderColor = "#80000000";
        dateInputConfig.calendarBackgroundColor = "#FFFFFFFF";
        dateInputConfig.dateElementColorNormal = "#FFFFFFFF";
        dateInputConfig.dateElementColorOnHover = "#12000000";
        dateInputConfig.dateElementColorOnFocus = "#FF1170CF";
        dateInputConfig.dateElementTextColorNormal = "#F2000000";
        dateInputConfig.notAvailabledateElementTextColor = "#99000000";
    }

    return dateInputConfig;
}

InputChoiceSetDropDownConfig SampleCardModel::getInputChoiceSetDropDownConfig(const bool isDark)
{
    InputChoiceSetDropDownConfig choiceSetDropdownInputConfig;
    choiceSetDropdownInputConfig = getInputFieldConfig(choiceSetDropdownInputConfig, isDark);

    if (!isDark)
    {
        choiceSetDropdownInputConfig.arrowIconColor = "#F2000000";
        choiceSetDropdownInputConfig.dropDownElementColorPressed = "#4D000000";
        choiceSetDropdownInputConfig.dropDownElementColorHovered = "#0A000000";
        choiceSetDropdownInputConfig.dropDownElementColorNormal = "#FFFFFFFF";
        choiceSetDropdownInputConfig.dropDownBorderColor = "#80000000";
        choiceSetDropdownInputConfig.dropDownBackgroundColor = "#FFFFFFFF";
    }

    return choiceSetDropdownInputConfig;
}

ToggleButtonConfig SampleCardModel::getToggleButtonConfig(const bool isDark)
{
    ToggleButtonConfig toggleButtonConfig;

    if (!isDark)
    {
        toggleButtonConfig.colorOnCheckedAndPressed = "#FF063A75";
        toggleButtonConfig.colorOnCheckedAndHovered = "#FF0353A8";
        toggleButtonConfig.colorOnChecked = "#FF1170CF";
        toggleButtonConfig.colorOnUncheckedAndPressed = "#33000000";
        toggleButtonConfig.colorOnUncheckedAndHovered = "#33000000";
        toggleButtonConfig.colorOnUnchecked = "#1C000000";
        toggleButtonConfig.borderColorOnCheckedAndPressed = "#FF063A75";
        toggleButtonConfig.borderColorOnCheckedAndHovered = "#FF0353A8";
        toggleButtonConfig.borderColorOnChecked = "#FF1170CF";
        toggleButtonConfig.borderColorOnUncheckedAndPressed = "#33000000";
        toggleButtonConfig.borderColorOnUncheckedAndHovered = "#33000000";
        toggleButtonConfig.borderColorOnUnchecked = "#1C000000";
        toggleButtonConfig.textColor = "#F2000000";
        toggleButtonConfig.radioButtonInnerCircleColorOnChecked = "#FFFFFFFF";
    }

    return toggleButtonConfig;
}

ActionButtonsConfig SampleCardModel::getActionButtonsConfig(const bool isDark)
{
    ActionButtonsConfig actionButtonsConfig;

    if (!isDark)
    {
        actionButtonsConfig.primaryColorConfig.buttonColorNormal = "#F2000000";
        actionButtonsConfig.primaryColorConfig.buttonColorHovered = "#CC000000";
        actionButtonsConfig.primaryColorConfig.buttonColorPressed = "#B3000000";
        actionButtonsConfig.primaryColorConfig.borderColorNormal = "#F2000000";
        actionButtonsConfig.primaryColorConfig.borderColorHovered = "#F2000000";
        actionButtonsConfig.primaryColorConfig.borderColorPressed = "#F2000000";
        actionButtonsConfig.primaryColorConfig.borderColorFocussed = "#FF1170CF";
        actionButtonsConfig.primaryColorConfig.textColorNormal = "#F2FFFFFF";
        actionButtonsConfig.primaryColorConfig.textColorHovered = "#F2FFFFFF";
        actionButtonsConfig.primaryColorConfig.textColorPressed = "#F2FFFFFF";

        actionButtonsConfig.secondaryColorConfig.buttonColorNormal = "#00000000";
        actionButtonsConfig.secondaryColorConfig.buttonColorHovered = "#12000000";
        actionButtonsConfig.secondaryColorConfig.buttonColorPressed = "#33000000";
        actionButtonsConfig.secondaryColorConfig.borderColorNormal = "#4D000000";
        actionButtonsConfig.secondaryColorConfig.borderColorHovered = "#4D000000";
        actionButtonsConfig.secondaryColorConfig.borderColorPressed = "#4D000000";
        actionButtonsConfig.secondaryColorConfig.borderColorFocussed = "#FF1170CF";
        actionButtonsConfig.secondaryColorConfig.textColorNormal = "#F2000000";
        actionButtonsConfig.secondaryColorConfig.textColorHovered = "#F2000000";
        actionButtonsConfig.secondaryColorConfig.textColorPressed = "#F2000000";

        actionButtonsConfig.positiveColorConfig.buttonColorNormal = "#00000000";
        actionButtonsConfig.positiveColorConfig.buttonColorHovered = "#FF185E46";
        actionButtonsConfig.positiveColorConfig.buttonColorPressed = "#FF134231";
        actionButtonsConfig.positiveColorConfig.borderColorNormal = "#FF185E46";
        actionButtonsConfig.positiveColorConfig.borderColorHovered = "#FF185E46";
        actionButtonsConfig.positiveColorConfig.borderColorPressed = "#FF134231";
        actionButtonsConfig.positiveColorConfig.borderColorFocussed = "#FF1170CF";
        actionButtonsConfig.positiveColorConfig.textColorNormal = "#FF185E46";
        actionButtonsConfig.positiveColorConfig.textColorHovered = "#F2FFFFFF";
        actionButtonsConfig.positiveColorConfig.textColorPressed = "#F2FFFFFF";

        actionButtonsConfig.destructiveColorConfig.buttonColorNormal = "#00000000";
        actionButtonsConfig.destructiveColorConfig.buttonColorHovered = "#FFAB0A15";
        actionButtonsConfig.destructiveColorConfig.buttonColorPressed = "#FF780D13";
        actionButtonsConfig.destructiveColorConfig.borderColorNormal = "#FFAB0A15";
        actionButtonsConfig.destructiveColorConfig.borderColorHovered = "#FFAB0A15";
        actionButtonsConfig.destructiveColorConfig.borderColorPressed = "#FF780D13";
        actionButtonsConfig.destructiveColorConfig.borderColorFocussed = "#FF1170CF";
        actionButtonsConfig.destructiveColorConfig.textColorNormal = "#FFAB0A15";
        actionButtonsConfig.destructiveColorConfig.textColorHovered = "#F2FFFFFF";
        actionButtonsConfig.destructiveColorConfig.textColorPressed = "#F2FFFFFF";
    }

    return actionButtonsConfig;
}
