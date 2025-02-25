//
//  avatarList.js
//
//  Created by Armored Dragon, 2025.
//  Copyright 2024 Overte e.V.
//
//	Handles user joining and leaving events and emits messages to the message display
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html

AvatarManager.avatarAddedEvent.connect((sessionId) => { _avatarAction("connected", sessionId) });
AvatarManager.avatarRemovedEvent.connect((sessionId) => { _avatarAction("left", sessionId) });

function _avatarAction(type, sessionId) {
	Script.setTimeout(() => {
		if (type == "connected") {
			app.info.palData = AvatarManager.getPalData().data;
		}

		// Get the display name of the user
		let displayName = "";
		displayName = AvatarManager.getPalData([sessionId])?.data[0]?.sessionDisplayName || null;
		if (displayName == null) {
			for (let i = 0; i < app.info.palData.length; i++) {
				if (app.info.palData[i].sessionUUID == sessionId) {
					displayName = app.info.palData[i].sessionDisplayName;
				}
			}
		}

		// Format the packet
		let message = {};
		// FIXME: Date / Time formatting
		// const timeArray = _formatTimestamp(_getTimestamp());
		// message.timeString = timeArray[0];
		// message.dateString = timeArray[1];
		message.timeString = Date.now();
		message.dateString = Date.now();
		message.message = `${displayName} ${type}`;

		// Show new message on screen
		Messages.sendLocalMessage(
			"Floof-Notif",
			JSON.stringify({
				sender: displayName,
				text: type,
			})
		);

		// _emitEvent({ type: "notification", ...message });
	}, 1500);
}