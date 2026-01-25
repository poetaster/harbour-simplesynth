import QtQuick 2.6
import Sailfish.Silica 1.0
import de.poetaster.sailsynth 1.0

import "pages"
import "cover"

ApplicationWindow
{
    initialPage: Component { FirstPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: Orientation.All
}
