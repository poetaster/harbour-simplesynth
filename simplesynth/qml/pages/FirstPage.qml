import QtQuick 2.6
import Sailfish.Silica 1.0

import de.poetaster.sailsynth 1.0

Page {

    property bool debug: true

    id: player
    //property var model: synth
    function updateSound(){
        if (!playing) {
          playing = true;
          synth.setDuration(parseInt(duration.text));
          synth.setVoiceDesc(filterVariables(voiceText.text));
          synth.play();
        }
        //var msg = {'action': 'play', 'sy': synth};
        //worker.sendMessage(msg);
    }
    /* strip var from the result formula to present */
    function filterVariables(text) {
        //const re0 = /·/g;
        //const re1 = /π/g;
        //const re2 = /√/g;
        //const re3 = /φ/g;
        // rad2deg in exprtk
        //const re5 = /deg/g;
        // log is ln natural e in exprtk
        const re0 = /}/g;
        const re1 = /{/g;
        const newtxt = text.replace(re0, " } ")
        newtxt = newtxt.replace(re1, " { ")
        return newtxt
    }


    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    WorkerScript {
        id: worker
        source: "worker.js"
    }
    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Game of Life")
                onClicked: pageStack.push(Qt.resolvedUrl("Game.qml"))
            }
            MenuItem {
                text: qsTr("Presets")
                onClicked: pageStack.push(Qt.resolvedUrl("Presets.qml"))
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: player.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("Synthesizer")
            }
            Label {
                x: Theme.horizontalPageMargin
                width: parent.width
                text: qsTr("Voice Description")
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeLarge
            }
            TextArea {
                id: voiceText
                width: parent.width
                x: Theme.horizontalPageMargin
                text: currentEngine //"fm 60 140 { fm 60 140 generator sinus 400 sinus 10 } sinus 1"
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeSmall

            }
            TextField {
                id:duration
                width:parent.width - Theme.horizontalPageMargin
                text: "3000"
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeSmall

            }
            Row {
                width: parent.width
                x: Theme.horizontalPageMargin
                spacing: 20
            Button{
                id: playButton
                width: parent.width /3
                text: qsTr("Play")
                color: Theme.secondaryHighlightColor
                onClicked:  updateSound();
            }
            Button{
                id: stopButton
                //x: playButton.right +  10
                //y: playButton.ght
                width: parent.width /3
                text: qsTr("Stop")
                color: Theme.secondaryHighlightColor
                onClicked:  synth.stop();
            }
            }
            Slider {
                id: speedSlider
                value: 1
                label:"SpeedOne"
                minimumValue: 0
                maximumValue: 200
                stepSize: 1
                width: parent.width
                valueText: value
                onValueChanged: synth.setSpeedOne(value)
            }
            Slider {
                id: f1Slider
                value: 30
                width: parent.width
                minimumValue: 1
                maximumValue: 1000
                stepSize: 1
                //width: parent.width
                //handleVisible: highlightToggle.checked
                valueText: value //valueIndicatorToggle.checked ? value : ""
                label: "FreqOne"
                //Rectangle { anchors.fill: parent; color: "red"; opacity: Theme.highlightBackgroundOpacity; z:-1; visible: sizeToggle.checked }
                onValueChanged: synth.setFreqOne(value)
            }


            /*
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
