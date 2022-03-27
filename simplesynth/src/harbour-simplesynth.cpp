#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>

#include "synthesizer.h"
#include "../libsynth/include/libsynth.hpp"

void makeAsound() {

    // initial instrument definition for testing
    //string input = "fm 100 150 am 0 100 square 100:20 square 39 adsr 1:0 1000:0 2000:100 5001:100 6000:-100 8000:0 loop level 1";
    //string input = "1000 fm 100 150 am 0 100";
    string input = "fm 60 140 { fm 60 140 modulator sinus 200 sinus 10 } sinus 1";

    long duration = 600;
    uint32_t ech = 48000;
    const int BUF_LENGTH = 1024;
    const int fade_time=50;

    //SoundGenerator::play(SoundGenerator::factory("fm 50 150 sinus 440 hook_speed"));

    SoundGenerator::setVolume(0);   // Avoid sound clicks at start
    SoundGenerator::fade_in(10);
    SoundGenerator::setVolume(0.6);

    SoundGenerator* g = SoundGenerator::factory(input);
    SoundGenerator::play(g);


    if (duration > fade_time) {
            SDL_Delay(duration-fade_time); // Play for ms
            SoundGenerator::fade_out(fade_time);
            SDL_Delay(fade_time); // Play for 100 ms (while fade out)
    } else {
            SoundGenerator::fade_out(fade_time);
            SDL_Delay(fade_time); // Play for ms (while fading out)
    }
    SDL_Delay(1000); // Wait till the end of buffer is played (avoid clicks) TODO this is buffer size dependant

    //SoundGenerator::stop(g);
}

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

    //QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QGuiApplication *app(SailfishApp::application(argc, argv));
    QCoreApplication::setOrganizationName("harbour-simplesynth");
    QCoreApplication::setApplicationName("harbour-simplesynth");

    //makeAsound();

    QTranslator *appTranslator = new QTranslator;
    appTranslator->load("harbour-simplesynth-" + QLocale::system().name(), SailfishApp::pathTo("translations").path());
    app->installTranslator(appTranslator);

    qmlRegisterType<Synthesizer>("de.poetaster.sailsynth", 1, 0, "Synthesizer");

    QQuickView *view(SailfishApp::createView());
    //QScopedPointer<QQuickView> view(SailfishApp::createView());
    // register the type for qml
    Synthesizer synth;
    view->engine()->rootContext()->setContextProperty("synth", &synth);

    view->setSource(SailfishApp::pathTo("qml/harbour-simplesynth.qml"));
    view->show();
    return app->exec();
}
