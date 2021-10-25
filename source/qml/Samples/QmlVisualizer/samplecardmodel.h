#ifndef SAMPLECARDMODEL_H
#define SAMPLECARDMODEL_H

#include "AdaptiveCardQmlRenderer.h"
#include "RenderedQmlAdaptiveCard.h"
#include "ImageDownloader.h"
#include "Utils.h"

#include <QAbstractListModel>

using namespace RendererQml;

class SampleCardList;

class SampleCardModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(SampleCardList *list READ list WRITE setList)

public:
    explicit SampleCardModel(QObject *parent = nullptr);

    enum {
        CardNameRole = Qt::UserRole,
        CardJsonString
    };

	// Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    SampleCardList *list() const;
    void setList(SampleCardList *list);

    std::shared_ptr<AdaptiveCards::HostConfig> getHostConfig();

    Q_INVOKABLE QString generateQml(const QString& cardQml);
    Q_INVOKABLE void setTheme(const QString& theme);
    Q_INVOKABLE void onAdaptiveCardButtonClicked(const QString& title, const QString& type, const QString& data);

signals:
    void reloadCardOnThemeChange();
    void sendCardResponseToQml(const QString& output);

private:
    SampleCardList *mList;
    std::shared_ptr<AdaptiveCardQmlRenderer> renderer_ptr;

    static std::wstring toWString(const std::string& input);
    void actionOpenUrlButtonClicked(const QString& title, const QString& type, const QString& data);
    void actionSubmitButtonClicked(const QString& title, const QString& type, const QString& data);
	static const std::map<std::string, std::string> rehostImage(const std::map<std::string, std::string>& urls);

    static std::map<int, std::string> GetImageUrls(std::shared_ptr<AdaptiveCards::AdaptiveCard> card, std::map<int, std::string> urls);
    static std::pair<std::map<int, std::string>, std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCard>>> GetCardImageUrls(std::shared_ptr<AdaptiveCards::BaseCardElement> cardElement, std::map<int, std::string> urls, std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCard>> showCards);
    static std::pair<std::map<int, std::string>, std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCard>>> GetActionImageUrls(std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>> cardElement, std::map<int, std::string> urls, std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCard>> showCards);

    std::shared_ptr<AdaptiveCardRenderConfig> getRenderConfig(const bool isDark);
    template<typename InputConfig>
    InputConfig getInputFieldConfig(InputConfig inputConfig, const bool isDark);
    InputTextConfig getInputTextConfig(const bool isDark);
    InputNumberConfig getInputNumberConfig(const bool isDark);
    InputTimeConfig getInputTimeConfig(const bool isDark);
    InputChoiceSetDropDownConfig getInputChoiceSetDropDownConfig(const bool isDark);
    ToggleButtonConfig getToggleButtonConfig(const bool isDark);
    InputDateConfig getInputDateConfig(const bool isDark);
    ActionButtonsConfig getActionButtonsConfig(const bool isDark);
};

#endif // SAMPLECARDMODEL_H
