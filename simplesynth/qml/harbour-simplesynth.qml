import QtQuick 2.6
import Sailfish.Silica 1.0
import de.poetaster.sailsynth 1.0

import "pages"
import "cover"

ApplicationWindow
{
    id:root
    property string currentEngine: "fm 60 140 { fm 60 140 generator sinus 400 sinus 10 } sinus 1"

    initialPage: Component { FirstPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: Orientation.All
}
