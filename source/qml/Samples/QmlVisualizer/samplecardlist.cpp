#include "samplecardlist.h"
#include "SampleCardJson.h"

SampleCardList::SampleCardList(QObject *parent) : QObject(parent)
{
    mCards.append({ QStringLiteral("Empty card"), QString::fromStdString(Samples::card_Empty) });
    mCards.append({ QStringLiteral("TextBlock"), QString::fromStdString(Samples::card_TextBlock) });
    mCards.append({ QStringLiteral("Rich text"), QString::fromStdString(Samples::card_richText) });
    mCards.append({ QStringLiteral("Input text"), QString::fromStdString(Samples::card_InputText) });
    mCards.append({ QStringLiteral("Input number"), QString::fromStdString(Samples::card_InputNumber) });
    mCards.append({ QStringLiteral("Input date"), QString::fromStdString(Samples::card_dateInput) });
    mCards.append({ QStringLiteral("Input Toggle"), QString::fromStdString(Samples::card_CheckboxInput) });
    mCards.append({ QStringLiteral("Input ChoiceSet"), QString::fromStdString(Samples::card_ChoiceSetInput) });
    mCards.append({ QStringLiteral("Image"), QString::fromStdString(Samples::card_Image) });
    mCards.append({ QStringLiteral("Fact Set"), QString::fromStdString(Samples::card_FactSet) });
	mCards.append({ QStringLiteral("Container"), QString::fromStdString(Samples::card_Container) });
	mCards.append({ QStringLiteral("Input Time"), QString::fromStdString(Samples::card_timeInput) });
	mCards.append({ QStringLiteral("Image Set"), QString::fromStdString(Samples::card_ImageSet) });
}

QVector<Card> SampleCardList::cardList() const
{
    return mCards;
}
