import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
	height: 60
	width: parent.width
	id: root
	z: 1 // FIXME: Layout issue? Shouldn't need to adjust the z-index but I do.

	Rectangle {
		anchors.fill: parent;
		color: "black"
	}

	Image {
		source: "../img/back_arrow.png"
		anchors.verticalCenter: parent.verticalCenter
		height: 40
		width: 40
		x: current_page == "Settings" ? -40 : 10

		Behavior on x {
			NumberAnimation {
				duration: 200
				easing.type: Easing.InOutCubic
			}
		}

		MouseArea {
			anchors.fill: parent
			onClicked: {
				current_page = "Settings";
			}
		}
	}

	Text {
		text: current_page
		color: "white"
		font.pointSize: 18
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		horizontalAlignment: Text.AlignHCenter
	}
}
