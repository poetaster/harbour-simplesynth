import QtQuick 2.6
import Sailfish.Silica 1.0


import "../js/settings.js" as Settings
import "../js/gameoflife.js" as Game
import "../js/notes.js" as Notes

Page {

    id: gamepage

    Connections {
        target:playerState
        onStoppedPlaying: {
            if (gamepage.activeFocus) {
            synth.play()
            if (debug) console.log("start")
            }
        }
    }

    property bool debug: false
    property int mode: 1
    property var notes: []

    function sv() {
        var text = "1111111111111";
        var filename = "textfile";
        var blob = new Blob([text], {type: "text/plain;charset=utf-8"});
        saveAs(blob, filename+".txt");
    }

    function startAudio() {

      synth.setDuration(parseInt(50000));
      //synth.setVoiceDesc(voiceText.text);
      synth.play();
      playing = true;

    }

    function updateSoundOne(){
      var generationsCounter = Game.generationsCounter
      var birthsCounter = 0
      var deathsCounter = 0
      var population = Game.population

        for ( var i = 0; i < Game.maxColumn; i++) {
            for (var j = 0; j < Game.maxRow; j++) {
                var n = Game.index(i,j);
                if (Game.cells[n].mustdie && Game.cells[Game.index(i,j)].isLive ) {
                    if ( j > Game.maxRow / 2)
                        deathsCounter ++;

                }
                if (Game.cells[n].mustbirth && !Game.cells[Game.index(i,j)].isLive) {
                    if ( j < Game.maxRow / 2)
                        birthsCounter ++;
                }
            }
        }
        var deathsRelative = (deathsCounter/population) * 700
        var birthsRelative = (birthsCounter/population)*1300
        //if (debug) console.log(deathsRelative)
        //if (debug) console.log(birthsRelative)

       synth.setSpeedOne(deathsRelative)
       synth.setFreqOne(birthsRelative)
        //var msg = {'action': 'play', 'sy': synth};
        //worker.sendMessage(msg);
    }

    function updateSoundTwo(){

      var song = ['F#', 'E', 'D', 'E', 'B', 'F#', 'E', 'D', 'B', 'F#' ] // eightdays a week
      var deathFreq = Notes.frequency('F#2')
      var birthFreq = Notes.frequency('F#2')
      var octave = 2
        for ( var i = 0; i < Game.maxColumn; i++) {
            for (var j = 0; j < Game.maxRow; j++) {
                var n = Game.index(i,j);
                if (Game.cells[n].mustdie && Game.cells[Game.index(i,j)].isLive ) {
                    if ( j < Game.maxRow / 2) {
                        for (var x = 0; x < 10; x++) {
                            // select octave from row
                            if (j % 10 === 0 &&  j < 50) octave = j /10
                            //select note from column position
                            if ( i % x === 0)  {
                                var note =song[x] + octave
                                birthFreq = Notes.frequency(note)
                            }
                        }
                    }
                }
                if (Game.cells[n].mustbirth && !Game.cells[Game.index(i,j)].isLive) {
                    if ( j > Game.maxRow / 2) {
                        for (var x = 0; x < 10; x++) {
                            // select octave from row
                             if (j % 10 === 0 ) octave = j / 10
                             if (octave > 4) octave = 4
                             if (octave < 2) octave = 2
                            //select note from column position
                            if ( i % x === 0)  {
                                var note =song[x] + octave
                                deathFreq = Notes.frequency(note)
                            }
                        }
                    }
                }
            }
        }
        if (debug) console.log(birthFreq)
        if (debug) console.log(deathFreq)
        //if (debug) console.log("two")

       synth.setSpeedOne(deathFreq)
       synth.setFreqOne(birthFreq)

    }
    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.Portrait

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("Mode 1")
                onClicked: mode = 0
            }
            MenuItem {
                text: qsTr("Mode 2")
                onClicked: mode = 1
            }
        }


        Grid  {
            id: gridButtons
            width: parent.width
            height: butClear.height * 2
            columns: 4
            spacing: 2
            z: canvas.z+1

            Column {
                width: (parent.width/gridButtons.columns) - gridButtons.spacing
                height: butClear.height * 2
                spacing: 2
                Button {
                    id: butClear
                    width:  parent.width
                    text: qsTr("Clear")
                    onClicked:  {
                        if(Game.Inited) {
                            Game.clear()
                            canvas.requestPaint()
                        }
                    }
                }
                Button {
                    width:  parent.width
                    text: qsTr("Random")
                    onClicked:  {
                        if(Game.Inited) {
                            Game.clear()
                            Game.initRandom()
                            canvas.requestPaint()
                        }
                    }
                }
            }
            Column {
                width: (parent.width/gridButtons.columns) - gridButtons.spacing
                height: butClear.height * 2
                spacing: 2
                Button {
                    width:   parent.width
                    text: qsTr("Start")
                    onClicked: {
                        if(Game.Inited) {
                            timer.start()
                            startAudio()
                        }

                    }
                }
                Button {
                    id: butStop
                    width:  parent.width
                    text: qsTr("Stop/Edit")
                    onClicked: {
                        if(Game.Inited) {
                            timer.stop();
                            canvas.requestPaint();
                        }
                    }
                }
            }

            Column {
                width: (parent.width/gridButtons.columns) - gridButtons.spacing
                height: butClear.height * 2
                spacing: 2
                Button {
                    id: butSpeedUp
                    width:  parent.width
                    text: qsTr("Speed +")
                    onClicked: {
                        if(Game.Inited) {
                            timer.interval /=2;
                            if(timer.interval < 10)
                                timer.interval = 10;

                        }
                    }
                }
                Button {
                    id: butSpeedDown
                    width:   parent.width
                    text: qsTr("Speed -")
                    onClicked: {
                        if(Game.Inited) {
                            timer.interval *=2;
                            if(timer.interval > 4000)
                                timer.interval = 4000;
                        }
                    }
                }

            }

            Column {
                width: (parent.width/gridButtons.columns) - gridButtons.spacing
                height: butClear.height * 2
                spacing: 2
                Button {
                    id: butAreaUp
                    width:   parent.width
                    text: qsTr("Area +")
                    onClicked: {
                        Game.blockSize /= 1.5
                        if(Game.blockSize < 10)
                            Game.blockSize = 10;

                        Game.reInitArea( canvas.width, canvas.height )
                        canvas.requestPaint()
                    }
                }
                Button {
                    id: butAreaDown
                    width:  parent.width
                    text: qsTr("Area -")
                    onClicked: {
                        Game.blockSize *= 1.5
                        if(Game.blockSize > 50)
                            Game.blockSize = 50;

                        Game.reInitArea( canvas.width, canvas.height )
                        canvas.requestPaint()
                    }
                }
            }

        }




        Canvas {
            id:canvas
            y:  gridButtons.height + gridButtons.spacing * 2
            height: parent.height - gridButtons.height - gridButtons.spacing
            width: parent.width

            onPaint:  {
                var ctx = getContext("2d");
                ctx.reset();

                if(timer.running)
                    ctx.fillStyle = Qt.rgba(0,0,0,0.5);
                else
                    ctx.fillStyle = Qt.rgba(0.5,0.5,0.5,1);

                ctx.fillRect(0,0, width, height);

                if(Game.Inited) {
                    Game.gameDraw(ctx, width, height)
                }
            }
            MouseArea {
                id:area
                anchors.fill: parent
                onClicked: {

                    var ci = Math.floor(mouseX / Game.blockSize);
                    var cj = Math.floor(mouseY / Game.blockSize);

                    console.log(ci  + " " + cj);


                    if (ci >= 0 && ci < Game.maxColumn && cj >= 0 && cj < Game.maxRow) {
                        Game.changeCell(ci, cj);
                    }
                    canvas.requestPaint()
                }
            }

            Component.onCompleted: {
                canvas.requestPaint()
                Game.createCells()
                Game.reInitArea( width, height )
            }


        }

        Timer {
            id:timer
            repeat: true
            running: false
            interval:  200
            onTriggered: {
                Game.gameUpdate()
                canvas.requestPaint()
                if (mode === 0) updateSoundOne()
                if (mode === 1) updateSoundTwo()
            }
        }

        BusyIndicator {
            size: BusyIndicatorSize.Medium
            anchors.bottom:   parent.bottom
            anchors.bottomMargin: Theme.paddingMedium
            x: Theme.paddingMedium
            running:  timer.running
        }




    }
}
