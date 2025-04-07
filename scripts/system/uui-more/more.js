"use strict";

let installedScripts = Settings.getValue("more.installedScripts", []) || []; 			// All scripts installed though more.js
let installedRepositories = Settings.getValue("more.installedRepositories", []) || []; 	// All repositories installed though more.js
let isFirstRun = Settings.getValue("more.firstRun", true); 								// Check if this app has ran before

let tablet = Tablet.getTablet("com.highfidelity.interface.tablet.system");
let active = false;

let appButton = tablet.addButton({
	icon: Script.resolvePath("./img/icon_white.png"),
	activeIcon: Script.resolvePath("./img/icon_black.png"),
	text: "MORE",
	isActive: active,
});

appButton.clicked.connect(toolbarButtonClicked);

tablet.fromQml.connect(fromQML);
tablet.screenChanged.connect(onScreenChanged);
Script.scriptEnding.connect(shutdownScript);

if (isFirstRun) {
	installRepo("https://more.overte.org/applications/metadata.js");
	Settings.setValue("ArmoredMore-FirstRun", false);
	isFirstRun = false;
}

function toolbarButtonClicked() {
	if (active) {
		tablet.gotoHomeScreen();
		active = !active;
		appButton.editProperties({ isActive: active });
	} else {
		// getLists();
		tablet.loadQMLSource(Script.resolvePath("./qml/more.qml"));
		active = !active;
		appButton.editProperties({ isActive: active });
	}
}

function installRepo(url) {

}

function onScreenChanged(type, url) {
	if (url != Script.resolvePath("./more.qml")) {
		active = false;
		appButton.editProperties({
			isActive: active,
		});
	}
}

function fromQML(event) {
	console.log(`New QML event:\n${JSON.stringify(event)}`);

	switch (event.type) {
		case "initialized":
			getLists();
			break;
		case "install_application":
			installApp(event);
			break;
		case "remove_application":
			uninstallApp(event.url);
			break;
		case "install_repo":
			installRepo(event.url);
			break;
		case "remove_repo":
			uninstallRepo(event.url);
			break;
	}
}

function shutdownScript() {
	// Script has been removed.
	console.log("Shutting Down");
	tablet.removeButton(appButton);
}