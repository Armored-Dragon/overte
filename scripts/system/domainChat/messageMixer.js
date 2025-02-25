function messageReceived(channel, message) {
	// Parse the message packet
	let parsedMessage = _parseJSON(message);
	if (parsedMessage === null) return;

	// Check if the message is a chat message
	if (!_isAChatMessage()) return;

	// Compatibility
	console.log("\n------------ NEW MESSAGE -----------------")
	parsedMessage = compatibility.fromArmoredChat(parsedMessage);
	console.log(JSON.stringify(parsedMessage, null, 4));

	// Display the chat message
	ui.displayNotificationCore(parsedMessage);

	// Add to message history
	_addMessageToHistory(parsedMessage);

	function _isAChatMessage() {
		// Checks to see if this is a message for us, and if we can handle it
		let normalizedChannel = channel.toLowerCase();
		if (normalizedChannel != 'chat') return false;	// Make sure the message mixer was the right channel
		if (parsedMessage.type && parsedMessage.type === "TransmitChatMessage") return false; // Notification Core

		// if (!_validateMessage(parsedMessage)) return false; // FIXME: This is causing issues due to compatibility.fromArmoredChat(parsedMessage);

		return true;
	}
}
function sendMessage(message = "", channel = "") { }

const messageMixer = {
	sendMessage: sendMessage,
	messageReceived: messageReceived
}

function _parseJSON(message) {
	try {
		return JSON.parse(message);
	} catch (e) {
		console.log("Error parsing JSON from the message mixer");
		return null;
	}
}
function _validateMessage(message = {}) {

	// This is the structure of a message packet:
	//
	// const messageStructure = {
	// 	author: "",					// The author of this message
	// 	channel: "",				// The channel the message was sent in
	// 	message: "", 				// The content of the message
	// 	position: {} ,				// The position of the author of the message when it was sent
	// }

	const validChannels = ["domain", "local"];
	console.log(JSON.stringify(message, null, 4));

	if (!message.author) return false;				// Needs message author
	if (!message.channel) return false;				// Needs message channel (domain wide / local)
	if (!message.message) return false;				// Needs message content
	if (!message.position) return false;			// Needs message position

	if (validChannels.indexOf(message.channel.toLowerCase()) === -1) return false;

	return true;
}
function _addMessageToHistory(message = {}) {
	// Add the message to the history array
	app.history.push({ ...message, position: null });

	while (app.history.length > app.settings.maximumNumberOfSavedMessages) {
		app.history.shift();
	}

	Settings.setValue("DomainChat-Messages", messageHistory);
}