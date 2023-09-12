import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import ACU.Dialogs 1.0

Popup {
    parent: Overlay.overlay
    width: parent.width / 1.5
    height: parent.height / 1.5
    modal: true
    closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape
    visible: true
    font.family: null
    clip: true
    padding: 0

    Overlay.modal: Rectangle { color: "#66000000" }

    Page {
        anchors.fill: parent
        padding: 0
        leftInset: 0
        rightInset: 0
        topInset: 0
        bottomInset: 0
        header: ToolBar {
            Material.primary: theme.surface0

            height: 24
            contentHeight: 24
            RowLayout {
                anchors.fill: parent
                ToolButton {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 24
                    text: "Имя"
                }
                ToolButton {
                    Layout.preferredHeight: 24
                    Layout.preferredWidth: 200
                    text: "Дата изменения"
                }
                ToolButton {
                    Layout.preferredHeight: 24
                    Layout.preferredWidth: 200
                    text: "Тип"
                }
                ToolButton {
                    Layout.preferredHeight: 24
                    Layout.preferredWidth: 200
                    text: "Размер"
                }
            }
        }

        ListView {
            anchors.fill: parent
            model: ACUFileDialogImpl {}
            delegate: ItemDelegate {
                required property int index
                required property bool isDirectory
                required property string name
                required property string size
                required property date lastChanged
                required property string extension
                required property string iconPath

                width: parent.width
                height: 24
                icon {
                    source: iconPath
                    width: 30
                    height: 30
                }

                RowLayout {
                    anchors.fill: parent

                    Label {
                        Layout.leftMargin: 50
                        Layout.fillWidth: true
                        Layout.preferredHeight: 24
                        text: name
                        font {
                            weight: Font.DemiBold
                        }
                    }

                    Label {
                        Layout.preferredHeight: 24
                        Layout.preferredWidth: 200
                        text: lastChanged.toLocaleDateString(Qt.locale("ru_RU"))
                        color: theme.subtext0
                    }

                    Label {
                        Layout.preferredHeight: 24
                        Layout.preferredWidth: 200
                        text: isDirectory ? "Папка с файлами"
                                          : "Файл \"" + extension + "\""
                        color: theme.subtext0
                    }

                    Label {
                        Layout.preferredHeight: 24
                        Layout.preferredWidth: 200
                        text: size
                        color: theme.subtext0
                    }
                }
            }
        }
    }
}