import QtQuick 2.6
import Sailfish.Silica 1.0
import de.poetaster.sailsynth 1.0

import "pages"
import "cover"

ApplicationWindow
{
    id:root
    property bool debug: true
    property bool playing: false
    property string currentEngine: "{ { fm 50 150 { fm 20 120 generator sq 120:12 s1 } s1 } { fm 60 140 { fm 60 140 generator sin 440:60 f1 } s1 } }"

    initialPage: Component { FirstPage { } }

    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: Orientation.All

    QtObject {
        id: playerState
        property bool playing: false
        signal stoppedPlaying(bool playing)
    }
    Game {}

    SynthController {
        id: synth
        onVoiceDescChanged:  {
            // console.log("progress " + progress)
        }
        onDone: {
            if (debug) console.log("done")
            root.playing = false
            playerState.stoppedPlaying(false)
        }
    }
}
