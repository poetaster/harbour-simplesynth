/*
 * This file is part of harbour-simplesynth.
 * Copyright (C) 2026 blueprint@poetaster.de Mark Washeim
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
 * along with harbour-dwd.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

function httpRequest(url, callback) {
    var doc = new XMLHttpRequest();
    doc.onreadystatechange = function() {
        if (doc.readyState === XMLHttpRequest.DONE) {
            callback(doc);
        }
    }
    doc.open("GET", url);
    doc.send();

}

function loadJSON(file, callback) {

   var xobj = new XMLHttpRequest();
   //xobj.overrideMimeType("application/json");
   xobj.open('GET', file, true);
   xobj.onreadystatechange = function () {
       if (xobj.readyState === XMLHttpRequest.DONE) {
           callback(xobj);
       }
         /*if (xobj.readyState == 4 && xobj.status == "200") {
           // Required use of an anonymous callback as .open will NOT return a value but simply returns undefined in asynchronous mode
           callback(xobj.responseText);
         }*/

   };
    xobj.open("GET",file)
   xobj.send();
}
/*  This json doc function takes and returns an index to the callback.
 * This permits it to be called in a loop.
 */

function httpRequestIndex(url, index, callback) {
    var doc = new XMLHttpRequest();
    doc.onreadystatechange = function() {
        if (doc.readyState === XMLHttpRequest.DONE) {
            callback(index,doc);
        }
    }
    doc.open("GET", url);
    doc.send();
}


