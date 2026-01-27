import QtQuick 2.6
import Sailfish.Silica 1.0

import de.poetaster.sailsynth 1.0

Page {

    id: page
    //property var model: synth
    function updateSound(){

        synth.setDuration(parseInt(duration.text));
        synth.setVoiceDesc(voiceText.text);
        //synth.makeAsound();
        synth.play()
    }

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
   allowedOrientations: Orientation.All

   Synthesizer {
       id: synth
       onVoiceDescChanged:  {
           // console.log("progress " + progress)
       }
   }

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
                font.pixelSize: Theme.fontSizeLarge
            }
            TextArea {
                id: voiceText
                width: parent.width
                x: Theme.horizontalPageMargin
                text: "fm 60 140 { fm 60 140 generator sinus 800 sinus 10 } sinus 1"
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeSmall
            }
            TextField {
                id:duration
                width:parent.width
                text: "1000"
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeSmall

            }

            Button{
                x: Theme.horizontalPageMargin
                width: parent.width /2
                text: qsTr("Submit Voice Description to Engine")
                color: Theme.secondaryHighlightColor
                onClicked:  updateSound();

            }/*
            Label {
                x: Theme.horizontalPageMargin
                width: parent.width
                text: Synthesizer.voiceDesc
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
            }*/
        }
    }
}
