import QtQuick 2.15
import QtQuick.Controls 2.15
import ACU.Dialogs 1.0

Popup {
    parent: Overlay.overlay
    width: parent.width / 1.5
    height: parent.height / 1.5
    modal: true
    closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape
    visible: true

    Overlay.modal: Rectangle { color: "#66000000" }
    ListView {
        anchors.fill: parent
        model: ACUFileDialogImpl {}
        delegate: Label {
            required property int index
            required property bool isDirectory
            required property string name
            required property string size
            required property date lastChanged
            required property string extension
            required property string icon

            text: name
        }
    }
}