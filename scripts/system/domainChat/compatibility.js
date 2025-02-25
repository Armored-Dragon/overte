//
//  compatibility.js
//
//  Created by Armored Dragon, May 17th, 2024.
//  Copyright 2024 Overte e.V.
//
//	This provides functions for backwards compatibility for messages.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html

const compatibility = {
	fromArmoredChat: (messagePacket) => {
		let newMessagePacket = {
			author: messagePacket.displayName || messagePacket.author || null,
			channel: messagePacket.channel.toLowerCase(),
			message: messagePacket.message,
			position: messagePacket.position
		}

		return newMessagePacket;
	}
}