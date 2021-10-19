#include "samplecardlist.h"
#include "SampleCardJson.h"

SampleCardList::SampleCardList(QObject *parent) : QObject(parent)
{
    mCards.append({ QStringLiteral("Empty card"), QString::fromStdString(Samples::card_Empty) });
    mCards.append({ QStringLiteral("TextBlock"), QString::fromStdString(Samples::card_TextBlock) });
    mCards.append({ QStringLiteral("Rich text"), QString::fromStdString(Samples::card_richText) });
    mCards.append({ QStringLiteral("Input text"), QString::fromStdString(Samples::card_InputText) });
    mCards.append({ QStringLiteral("Action Inline"), QString::fromStdString(Samples::card_Action_Inline) });
    mCards.append({ QStringLiteral("Input number"), QString::fromStdString(Samples::card_InputNumber) });
    mCards.append({ QStringLiteral("Input date"), QString::fromStdString(Samples::card_dateInput) });
    mCards.append({ QStringLiteral("Input Toggle"), QString::fromStdString(Samples::card_CheckboxInput) });
    mCards.append({ QStringLiteral("Input ChoiceSet"), QString::fromStdString(Samples::card_ChoiceSetInput) });
    mCards.append({ QStringLiteral("Image"), QString::fromStdString(Samples::card_Image) });
    mCards.append({ QStringLiteral("Fact Set"), QString::fromStdString(Samples::card_FactSet) });
	mCards.append({ QStringLiteral("Container"), QString::fromStdString(Samples::card_Container) });
	mCards.append({ QStringLiteral("Input Time"), QString::fromStdString(Samples::card_timeInput) });
	mCards.append({ QStringLiteral("Image Set"), QString::fromStdString(Samples::card_ImageSet) });
	mCards.append({ QStringLiteral("Seperator and Spacing"), QString::fromStdString(Samples::card_Separator) });
	mCards.append({ QStringLiteral("ColumnSet"), QString::fromStdString(Samples::card_columnSet) });
    mCards.append({ QStringLiteral("Action Open URL"), QString::fromStdString(Samples::card_Action_OpenUrl) });
	mCards.append({ QStringLiteral("Action Submit 1"), QString::fromStdString(Samples::card_Action_Submit) });
	mCards.append({ QStringLiteral("Flight Iternery"), QString::fromStdString(Samples::card_flight) });
	mCards.append({ QStringLiteral("Weather Card"), QString::fromStdString(Samples::card_weather) });
	mCards.append({ QStringLiteral("Action Show Card 1"), QString::fromStdString(Samples::card_Action_ShowCard_1) });
    mCards.append({ QStringLiteral("Action Show Card 2"), QString::fromStdString(Samples::card_Action_ShowCard_2) });
	mCards.append({ QStringLiteral("Action Toggle Visibility"), QString::fromStdString(Samples::card_Action_ToggleVisibility) });
    mCards.append({ QStringLiteral("Action Set"), QString::fromStdString(Samples::card_ActionSet) });
    mCards.append({ QStringLiteral("Select Action - Card"), QString::fromStdString(Samples::card_CardSelectAction) });
    mCards.append({ QStringLiteral("Select Action - Image"), QString::fromStdString(Samples::card_ImageSelectAction) });
    mCards.append({ QStringLiteral("Select Action - TextRun"), QString::fromStdString(Samples::card_TextRunSelectAction) });
    mCards.append({ QStringLiteral("Select Action - Container"), QString::fromStdString(Samples::card_ContainerSelectAction) });
    mCards.append({ QStringLiteral("Select Action - ColumnSet"), QString::fromStdString(Samples::card_ColumnSetSelectAction) });
    mCards.append({ QStringLiteral("Food order"), QString::fromStdString(Samples::card_FoodOrder) });
    mCards.append({ QStringLiteral("Show card wizard"), QString::fromStdString(Samples::card_ShowCardWiz) });
	mCards.append({ QStringLiteral("Toggle Visibility wizard"), QString::fromStdString(Samples::card_ToggleVisibilityWiz) });
	mCards.append({ QStringLiteral("Background Image"), QString::fromStdString(Samples::card_BackgroundImage) });
	mCards.append({ QStringLiteral("Bleed Properties"), QString::fromStdString(Samples::card_Bleed) });
	mCards.append({ QStringLiteral("Input Elements"), QString::fromStdString(Samples::inputElements) });

}

QVector<Card> SampleCardList::cardList() const
{
    return mCards;
}
