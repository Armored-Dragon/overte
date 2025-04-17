//
//  Created by Armored Dragon on April 17, 2025
//  Copyright 2025 Overte e.V.
//
//
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#include <QtCore/QObject>

class DashboardProxy : public QObject {
    Q_OBJECT
private:
    static QString buildDNFromUsername(const QString& username);
    static QString ldapServerURL;
    static QString readLDAPServerURL() {return ldapServerURL;}

public:

    /**
    * @brief Go to the main menu of the dashboard
    */
    static void gotoMenuScreen();

    /**
    * @brief Go to a web screen
    */
    static void gotoWebScreen();

    /**
    * @brief Go to a qml screen
    */
    static void gotoQMLScreen();

    /**
    * @brief Send a message to the web page
    */
    static void emitScriptEvent();

    /**
    * @brief Send a message to the QML page
    */
    static void sendToQml();

signals:
	void webEventReceived(QVariant msg);
	void fromQml(QVariant msg);
	void screenChanged(QVariant type, QVariant url);
	void dashboardShownChanged();
};