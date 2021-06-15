#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include "../libsynth/include/libsynth.hpp"
void makeAsound() {
    // initial instrument definition for testing
    string input = "fm 100 150 am 0 100 square 100:20 square 39 adsr 1:0 1000:0 2000:100 5001:100 6000:-100 8000:0 loop level 1";

    long duration = 30000;
    uint32_t ech = 48000;
    const int BUF_LENGTH = 1024;

    //SoundGenerator::play(SoundGenerator::factory("fm 50 150 sinus 440 hook_speed"));

    SoundGenerator* g = SoundGenerator::factory(input);
    SoundGenerator::play(g);

    SoundGenerator::setVolume(0);   // Avoid sound clicks at start
    SoundGenerator::fade_in(10);
    SoundGenerator::setVolume(0);   // Avoid sound clicks at start
    SoundGenerator::fade_in(10);

    const int fade_time=50;

    if (duration > fade_time) {
            SDL_Delay(duration-fade_time); // Play for ms
            SoundGenerator::fade_out(fade_time);
            SDL_Delay(fade_time); // Play for 100 ms (while fade out)
    } else {
            SoundGenerator::fade_out(fade_time);
            SDL_Delay(fade_time); // Play for ms (while fading out)
    }
    SDL_Delay(1000); // Wait till the end of buffer is played (avoid clicks) TODO this is buffer size dependant

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

    // Exemple of external event that can modify the
    // generated sound (see mousewheel.synth)

    /*
     QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointrer<QQuickView> view(SailfishApp::createView());
    view->setSource(SailfishApp::pathTo("qml/harbour-simplesynth.qml"));
    view->setTitle("Simplesynth");
    view->showFullScreen();
    return app->exec();
    */
    makeAsound();
    return SailfishApp::main(argc, argv);
}

