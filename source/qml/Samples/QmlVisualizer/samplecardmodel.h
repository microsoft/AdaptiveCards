#ifndef SAMPLECARDMODEL_H
#define SAMPLECARDMODEL_H

#include <AdaptiveCardQmlRenderer.h>
#include <RenderedQmlAdaptiveCard.h>

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
    void actionButtonClicked(const QString& title, const QString& type, const QString& data);
};

#endif // SAMPLECARDMODEL_H
