import QtQuick 2.0
import Sailfish.Silica 1.0

//import de.poetaster.sailsynth 1.0

Page {

    id: page
    //property var model: synth
    function updateSound(){
        synth.voiceDesc = voiceText.text;
        synth.makeAsound();
        //synth.play(voiceText.text)
    }

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
   allowedOrientations: Orientation.All

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Show Page 2")
                onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("Synthesizer")
            }
            Label {
                x: Theme.horizontalPageMargin
                width: parent.width
                text: qsTr("Enter Voice Description")
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
            }
            TextArea {
                id: voiceText
                width: parent.width
                x: Theme.horizontalPageMargin
                text: "reverb 100:50 fm 90 100 sinus 1440:50 sinus 1.5 \n\n" +
                       "fm 60 140 { fm 60 140 modulator sinus 200 sinus 10 } sinus 1"
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeSmall
            }
            Button{
                x: Theme.horizontalPageMargin
                width: parent.width /2
                text: qsTr("Submit Voice Description to Engine")
                color: Theme.secondaryHighlightColor
                onClicked:  updateSound();

            }
            Label {
                x: Theme.horizontalPageMargin
                width: parent.width
                text: synth.voiceDesc
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
            }
        }
    }
}
