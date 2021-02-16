#include "stdafx.h"
#include <AdaptiveCardQmlRenderer.h>
#include <RenderedQmlAdaptiveCard.h>

#include "HostConfig.h"
#include "QmlTag.h"

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>

using namespace RendererQml;

const std::string card = R"({
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
  "type": "AdaptiveCard",
  "version": "1.0",
  "body": [
    {
      "type": "TextBlock",
      "text": "This is some text",
      "size": "large"
    },
    {
      "type": "TextBlock",
      "text": "It doesn't wrap by default",
      "weight": "bolder"
    },
    {
      "type": "TextBlock",
      "text": "So set **wrap** to true if you plan on showing a paragraph of text",
      "wrap": true
    },
    {
      "type": "TextBlock",
      "text": "You can also use **maxLines** to prevent it from getting out of hand",
      "wrap": true,
      "maxLines": 2
    },
    {
      "type": "TextBlock",
      "text": "You can even draw attention to certain text with color",
      "wrap": true,
      "color": "attention"
    },
    {
      "type": "TextBlock",
      "text": "color: default",
      "color": "default"
    },
    {
      "type": "TextBlock",
      "text": "color: accent",
      "color": "accent"
    },
    {
      "type": "TextBlock",
      "text": "color: good",
      "color": "good"
    },
    {
      "type": "TextBlock",
      "text": "color: warning",
      "color": "warning"
    },
    {
      "type": "TextBlock",
      "text": "color: attention",
      "color": "attention"
    },
    {
      "type": "TextBlock",
      "text": "color: light",
      "color": "light"
    },
    {
      "type": "TextBlock",
      "text": "color: dark",
      "color": "dark"
    },
    {
      "type": "TextBlock",
      "text": "**horizontalAlignment:left**",
      "horizontalAlignment": "left"
    },
    {
      "type": "TextBlock",
      "text": "**horizontalAlignment:center**",
      "horizontalAlignment": "center"
    },
    {
      "type": "TextBlock",
      "text": "**horizontalAlignment:right**",
      "horizontalAlignment": "right"
    },
    {
      "type": "TextBlock",
      "text": "isSubtle:false",
      "isSubtle": false
    },
    {
      "type": "TextBlock",
      "text": "isSubtle:true",
      "isSubtle": true
    },
    {
      "type": "TextBlock",
      "text": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.",
      "wrap": true,
      "maxLines": 1
    },
    {
      "type": "TextBlock",
      "text": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.",
      "wrap": true,
      "maxLines": 2
    },
    {
      "type": "TextBlock",
      "text": "size:default"
    },
    {
      "type": "TextBlock",
      "text": "size:small",
      "size": "small"
    },
    {
      "type": "TextBlock",
      "text": "size:default",
      "size": "default"
    },
    {
      "type": "TextBlock",
      "text": "size:medium",
      "size": "medium"
    },
    {
      "type": "TextBlock",
      "text": "size:large",
      "size": "large"
    },
    {
      "type": "TextBlock",
      "text": "size:extraLarge",
      "size": "extraLarge"
    },
    {
      "type": "TextBlock",
      "text": "weight: lighter",
      "weight": "lighter"
    },
    {
      "type": "TextBlock",
      "text": "weight: default",
      "weight": "default"
    },
    {
      "type": "TextBlock",
      "text": "weight: bolder",
      "weight": "bolder"
    },
    {
      "type": "TextBlock",
      "text": "**wrap: false** Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat",
      "wrap": false
    },
    {
      "type": "TextBlock",
      "text": "**wrap: true** Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.",
      "wrap": true
    },
    {
      "type": "TextBlock",
      "text": "Font type not set."
    },
    {
      "type": "TextBlock",
      "text": "Font type set to *default*.",
      "fontType": "default"
    },
    {
      "type": "TextBlock",
      "text": "Font type set to *monospace*.",
      "fontType": "monospace"
    }
  ]
}
)";

static std::shared_ptr<AdaptiveCards::HostConfig> GetHostConfig()
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

static std::string GenerateQml(std::string card)
{
    std::shared_ptr<AdaptiveCards::ParseResult> mainCard = AdaptiveCards::AdaptiveCard::DeserializeFromString(card, "2.0");

    std::shared_ptr<AdaptiveCards::HostConfig> hostConfig = GetHostConfig();

    AdaptiveCardQmlRenderer renderer = AdaptiveCardQmlRenderer(hostConfig);
    std::shared_ptr<RenderedQmlAdaptiveCard> result = renderer.RenderCard(mainCard->GetAdaptiveCard(), nullptr);

    const auto generatedQml = result->GetResult();
    return generatedQml->ToString();
}

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    QQmlContext* context = view.engine()->rootContext();

    const std::string qmlString = GenerateQml(card);
    context->setContextProperty("_aQmlCard", QString::fromStdString(qmlString));

    view.setSource(QUrl("qrc:main.qml"));
    view.show();

    return app.exec();
}
