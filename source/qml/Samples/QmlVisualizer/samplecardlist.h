#ifndef SAMPLECARDLIST_H
#define SAMPLECARDLIST_H

#include <QObject>
#include <QVector>

struct Card
{
    QString CardName;
    QString CardJson;
};

class SampleCardList : public QObject
{
public:
    explicit SampleCardList(QObject *parent = nullptr);
    QVector<Card> cardList() const;

signals:

public slots:


private:
    QVector<Card> mCards;

};

#endif // SAMPLECARDLIST_H
