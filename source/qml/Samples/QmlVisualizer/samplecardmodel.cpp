#include "samplecardmodel.h"
#include "samplecardlist.h"

using namespace RendererQml;

SampleCardModel::SampleCardModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
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
    std::shared_ptr<AdaptiveCards::ParseResult> mainCard = AdaptiveCards::AdaptiveCard::DeserializeFromString(cardQml.toStdString(), "2.0");

    std::shared_ptr<AdaptiveCards::HostConfig> hostConfig = getHostConfig();

    AdaptiveCardQmlRenderer renderer = AdaptiveCardQmlRenderer(hostConfig);
    std::shared_ptr<RenderedQmlAdaptiveCard> result = renderer.RenderCard(mainCard->GetAdaptiveCard(), nullptr);

    const auto generatedQml = result->GetResult();
    const QString generatedQmlString = QString::fromStdString(generatedQml->ToString());
    return generatedQmlString;
}
