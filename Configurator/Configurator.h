#pragma once

#include <QMap>

class Configurator {
public:
    static void readConfigurations();

    static QString getHostName();
    static int getPort();


private:
	static QPair<QString, QString> handleLine(QString line);
    static void writeDefaultConfigurationsFile();

    static QMap<QString, QString> m_configurations;
};
