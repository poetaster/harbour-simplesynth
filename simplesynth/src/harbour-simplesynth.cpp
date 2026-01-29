#include <sailfishapp.h>
#include <QQuickView>
#include <QtQml>
#include <QScopedPointer>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QQmlContext>
#include <QCoreApplication>

#include "synthesizer.h"
#include "synthcontroller.h"
#include "../libsynth/include/libsynth.hpp"

int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/template.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //
    // To display the view, call "show()" (will show fullscreen on device).

    //return SailfishApp::main(argc, argv);

    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    //QGuiApplication *app(SailfishApp::application(argc, argv));
    //QCoreApplication::setOrganizationName("harbour-simplesynth");
    //QCoreApplication::setApplicationName("harbour-simplesynth");

    QQuickView *view(SailfishApp::createView());
    //QQmlEngine* engine = view->engine();

    QTranslator *appTranslator = new QTranslator;
    appTranslator->load("harbour-simplesynth-" + QLocale::system().name(), SailfishApp::pathTo("translations").path());
    app->installTranslator(appTranslator);

    qmlRegisterType<Synthesizer>("de.poetaster.sailsynth", 1, 0, "Synthesizer");
    qmlRegisterType<SynthController>("de.poetaster.sailsynth", 1, 0, "SynthController");

    // direct object inclusion
    //Synthesizer synth;
    //view->engine()->rootContext()->setContextProperty("synth", &synth);

    view->setSource(SailfishApp::pathTo("qml/harbour-simplesynth.qml"));
    view->show();
    return app->exec();
}
