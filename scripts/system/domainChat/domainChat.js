//
//  domainChat.js
//
//  Created by Armored Dragon, May 17th, 2024.
//  Copyright 2024 Overte e.V.
//
//	Uses the message mixer to facilitate text based communication between users 
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html

Script.include([
	"avatarList.js",		// Avatar leaving and joining
	"formatting.js",		// Message formatting and data parsing
	"messageMixer.js",		// Message mixer handing
	"keypressEvents.js",	// Keybinds
	"compatibility.js",		// Backwards compatibility
	"ui.js"					// User interface
]);

let app = {
	isVisible: false,
	info: {
		tabletButton: null,
		palData: null
	},
	settings: {},
	windows: {},
	history: [],
}
let tablet = Tablet.getTablet("com.highfidelity.interface.tablet.system");

Controller.keyPressEvent.connect(keyPressEvent);
Messages.messageReceived.connect(messageMixer.messageReceived);
Messages.subscribe("Chat"); // Floofchat
Messages.subscribe("chat");

// TODO: Uninstall - Clear settings & message history
// TODO: Launch - Load settings & message history
// TODO: Send messages - Add to message history & update UI

function loadSettings() { }
function saveSettings() { }
function uninstall() { }