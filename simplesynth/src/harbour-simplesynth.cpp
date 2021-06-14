#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include "../libsynth/libsynth.hpp"

// Exemple of external event that can modify the
// generated sound (see mousewheel.synth)
class SoundGeneratorMouseWheelLevel : public SoundGenerator {
  public:
                SoundGeneratorMouseWheelLevel() : SoundGenerator("mouse_hook") {
                        init();
                }

                SoundGeneratorMouseWheelLevel(istream &in) {
                        in >> min;
                        in >> max;
                }

                virtual void help(ostream &out)
                { out << "mouse_hook min max" << endl; }

                virtual void next(float &left, float &right, float speed) {
                        int x,y;
                        SDL_PumpEvents();
                        if (SDL_GetMouseState(&x,&y) & SDL_BUTTON(SDL_BUTTON_LEFT))
                                exit(1);
                        left += min + (max-min)*(float)x/640.0;
                        right += min + (max-min)*(float)y/480.0;
                }
  protected:
        virtual SoundGenerator* build(istream &in) const
        { return new SoundGeneratorMouseWheelLevel(in); }

        void init() {
                static bool done=false;
                if (done) return;

                if (SDL_Init( SDL_INIT_VIDEO ) == -1) {
                        cerr << "Cannot init video" << endl;
                        exit(1);
                }
                SDL_Window *win = SDL_CreateWindow("Move the mouse here, click to exit", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
                if (win == 0) exit(1);
        }

  private:
        float min;
        float max;
};


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

    //return static SoundGeneratorMouseWheelLevel gen_mouse;
    return SailfishApp::main(argc, argv);
}

