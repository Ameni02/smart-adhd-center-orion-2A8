import QtQuick 2.0
import QtQuick.Controls 2.2
import QtLocation 5.3
import QtPositioning 5.0





Item {
    property variant coordonneeCentre: QtPositioning.coordinate(36.80028, 10.18615) // Avignon




    Plugin
    {
        id: mapPlugin
        locales: "fr_FR"
        name: "osm" // OpenStreetMap
        PluginParameter { name: "osm.geocoding.host"; value: "https://nominatim.openstreetmap.org/" }
        PluginParameter { name: "osm.useragent"; value: "My great Qt OSM application" }
        PluginParameter { name: "osm.mapping.host"; value: "http://osm.tile.server.address/" }
        PluginParameter { name: "osm.mapping.copyright"; value: "All mine" }
        PluginParameter { name: "osm.routing.host"; value: "http://osrm.server.address/viaroute" }
        PluginParameter { name: "osm.geocoding.host"; value: "http://geocoding.server.address" }

    }

    Map
    {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: coordonneeCentre
        //center:QtPositioning.coordinate(25.6585,125.368)
        minimumZoomLevel: 5
        zoomLevel: 15

        MapQuickItem
        {
            id: indicateurPosition
            objectName: "indicateurPosition"
            sourceItem: Rectangle {width: 24; height: 24; color: "red"; border.width: 2; border.color: "blue"; smooth: true; radius: 15;}
            coordinate: coordonneeCentre
            function aller(latitude, longitude)
            {
                console.log("aller")
                map.clearMapItems();
                indicateurPosition.coordinate.latitude = latitude;
                indicateurPosition.coordinate.longitude = longitude;
                map.addMapItem(indicateurPosition);
                map.center.latitude = latitude;
                map.center.longitude = longitude;
                map.update();
            }
        }
    }

    Button
    {
        id: zoomPlus
        text: 'Zoom +'
        width: implicitWidth * 1.5
        height: implicitHeight * 1.5
        anchors {
            left: parent.left
            leftMargin: 4
            bottom: parent.bottom
            bottomMargin: 30
        }
        font.bold: true
        background: Rectangle {
            color: "lightgray"
            opacity: 0.5
            radius: 10
        }
        onClicked: map.zoomLevel++
    }

    Button
    {
        id: zoomMoins
        text: 'Zoom -'
        width: implicitWidth * 1.5
        height: implicitHeight * 1.5
        anchors {
            left: zoomPlus.right
            leftMargin: 10
            bottom: parent.bottom
            bottomMargin: 30
        }
        font.bold: true
        background: Rectangle {
            color: "lightgray"
            opacity: 0.5
            radius: 10
        }
        onClicked: map.zoomLevel--
    }

    Button
    {
        id: bouttonCentre
        text: "Centrer"
        width: implicitWidth * 1.5
        height: implicitHeight * 1.5
        anchors {
            left: zoomMoins.right
            leftMargin: 10
            bottom: parent.bottom
            bottomMargin: 30
        }
        font.bold: true
        background: Rectangle {
            color: "lightgray"
            opacity: 0.5
            radius: 10
        }
        onClicked: {
            map.clearMapItems();
            indicateurPosition.coordinate = coordonneeCentre;
            map.addMapItem(indicateurPosition);
            map.center = coordonneeCentre
            map.update();
        }
    }

    GeocodeModel
    {
        id: geocodage
        objectName: "geocodage"
        plugin: mapPlugin
        signal afficherInformations(string adresse, string coordonnee)
        onLocationsChanged:
        {
            if(error)
                console.log("Erreur GeocodeModel : " + error + " - " + errorString)
            if (count>=1)
            {
                console.log("Adresse : " + get(0).address.text + "\n" + get(0).coordinate)
                geocodage.afficherInformations(get(0).address.text, get(0).coordinate)
            }
        }
     }
    MouseArea
    {
        id: mouseArea
        objectName: "mouseArea"
        width: parent.width
        height: parent.height - (zoomMoins.height * 1.5)
        //anchors.fill: map
        hoverEnabled: true
        property var coordonnee: map.toCoordinate(Qt.point(mouseX, mouseY))
        signal afficherPosition(string latitude, string longitude)
        onClicked:
        {
            console.log(coordonnee.latitude + " " + coordonnee.longitude)
            geocodage.query = coordonnee
            geocodage.update()
            mouseArea.afficherPosition(coordonnee.latitude, coordonnee.longitude)
        }

    }

}
