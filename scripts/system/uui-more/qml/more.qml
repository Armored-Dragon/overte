import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import "./widgets"

Rectangle {
    signal sendToScript(var message);
	color: Qt.rgba(0.1,0.1,0.1,1);
	width: parent.width;
	height: parent.height;
	anchors.centerIn: parent;
	anchors.horizontalCenter: parent.horizontalCenter

	property var pages: [
		{name: "Browse", icon: "../img/overte.svg" }, 
		{name: "View Installed", icon: "../img/overte.svg" }, 
		{name: "Repositories", icon: "../img/overte.svg" }, 
	];
	property string current_page: "More"

	ColumnLayout {
		width: parent.width
		height: parent.height
		anchors.horizontalCenter: parent.horizontalCenter
		id: root

		// Navigation Header
		HeaderElement {
			id: header
		}

		// Home page
		SettingCenterContainer {
			id: home_page
			visible: current_page == "More"
			Layout.fillHeight: true

			Repeater {
				model: pages.length;
				delegate: SettingSubviewListElement {
					property string page_name: pages[index].name;
					property string page_icon: pages[index].icon;
				}
			}
		}
	}

}