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
                "type" : "AdaptiveCard",
                "version" : "1.2",
				"body": [
				]
            })";

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
