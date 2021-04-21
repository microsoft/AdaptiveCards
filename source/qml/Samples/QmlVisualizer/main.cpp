#include "stdafx.h"
#include "samplecardmodel.h"
#include "samplecardlist.h"
#include "SampleCardJson.h"

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SampleCardModel>("SampleCard", 1, 0, "SampleCardModel");
    qmlRegisterUncreatableType<SampleCardList>("SampleCard", 1, 0, "SampleCardList",
        QStringLiteral("SampleCardList should not be created in QML"));

    QQuickView view;
    QQmlContext* context = view.engine()->rootContext();

    SampleCardList cardList;
    SampleCardModel model;
    model.setList(&cardList);

    const QString qmlString = model.generateQml(QString::fromStdString(Samples::card_Empty));

	context->setContextProperty("_aQmlCard", qmlString);
    context->setContextProperty("_aModel", &model);

    view.setSource(QUrl("qrc:main.qml"));
	view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}
