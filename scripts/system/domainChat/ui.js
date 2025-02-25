const ui = {
	displayNotificationCore: (messagePacket) => {
		Messages.sendLocalMessage(
			"Floof-Notif",
			JSON.stringify({
				sender: messagePacket.author,
				text: messagePacket.message,
			})
		);
	},
	displayChatMessage: (messagePacket) => {
		// TODO
		console.log("displaychatMessage is not implemented");
	}
}