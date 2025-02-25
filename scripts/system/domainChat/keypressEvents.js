function keyPressEvent(event) {
	switch (JSON.stringify(event.key)) {
		case "16777220": // Enter key
			if (HMD.active) return; // Don't allow in VR

			quickMessage.sendToQml({
				type: "change_visibility",
				value: true,
			});
	}
}