/*
 * This file is part of harbour-simplesynth
 * Copyright (C) 2026 <blueprint@poetaster.de> Mark Washeim
 *
 * harbour-simplesynth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * harbour-dwd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with harbour-meteoswiss.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

import QtQuick 2.6
import Sailfish.Silica 1.0

import "../js/loader.js" as Locs
//import "../delegates"

Page {
    property var presets
    property bool debug: true

    id: searchPage
    allowedOrientations: Orientation.All

    Component.onCompleted: {
        //searchField.forceActiveFocus();
        fetchLocal();
    }
    function fetchLocal(){
        Locs.loadJSON("../js/presets.json", function(doc) {
            var response = JSON.parse(doc.responseText);
            listModel.clear();
            presets = response;
            for (var i = 0; i < response.length ; i++) {
                listModel.append(response[i]);
                 presets[i] = response[i];
                if (debug) console.debug(JSON.stringify(presets[i]))
            };
        });
    }

    function search(string) {
        var ret = [];
        //console.debug(JSON.stringify(presets));
        listModel.clear();
        for (var i = 0; i < presets.length; i++) {
            if (string !== "" && presets[i].name.indexOf(string) >= 0) {
                ret.push({"name": presets[i].name});
                listModel.append(presets[i])
                if(debug) console.debug(JSON.stringify(i));
                if(debug) console.debug(JSON.stringify(presets[i].name));
                if(debug) console.debug(JSON.stringify(listModel.count));
            }
            if (ret.length === 50) break;
        }
        return ret;
    }

    anchors.fill: parent

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        PageHeader {
            id: header
            title: qsTr("Choose Preset")
        }
/*
        SearchField {
            placeholderText: qsTr("Search")
            id: searchField
            width: parent.width
            anchors.top: header.bottom
            inputMethodHints: Qt.ImhNoPredictiveText

            onTextChanged: listModel.update()
            EnterKey.onClicked: {
                if (text != "") searchField.focus = false
            }
        }*/

        Column {
            id: column
            width: parent.width
            //anchors.top: searchField.bottom

            SilicaListView {
                id:sListview
                 anchors.fill: parent
                x: Theme.horizontalPageMargin
                //spacing: Theme.paddingSmall
                model:   ListModel {
                    id: listModel
                    /*
                    function update() {
                        clear()
                        if (searchField.text != "") {
                            searchPage.search(searchField.text);
                        }
                    }*/
                    //Component.onCompleted:update()
                }
                delegate: ListItem {
                    Label {
                        text: model.name
                        truncationMode: TruncationMode.Fade
                    }
                    Label {
                        text: model.def
                        truncationMode: TruncationMode.Fade
                    }
                    onClicked: {
                        //Store.addLocation(model);
                        currentEngine = model.def
                        pageStack.pop()
                       /* pageStack.push(Qt.resolvedUrl("OverviewPage.qml"), {
                                           "name": name,
                                           "lat": lat,
                                           "lon": lon}); */
                    }
                }
                spacing: 2
                VerticalScrollDecorator { flickable: sListview}
            }
        }
    }
}
