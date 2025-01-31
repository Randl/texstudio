#include "utilsSystem.h"
#include "utilsUI.h"


QString getTerminalCommand()
{
#ifdef Q_OS_MAC
	QString command = "open -a /Applications/Utilities/Terminal.app/";
	return command;
#else // Linux
	// Linux does not have a uniform way to determine the default terminal application
	// gnome
	QString command = execCommand("gsettings get org.gnome.desktop.default-applications.terminal exec");
	command = command.replace('\'', "");
	if (!command.isEmpty()) {
		return command;
	}
	// fallback
	QStringList fallbacks = QStringList() << "konsole" << "xterm";
	foreach (const QString &fallback, fallbacks) {
		QString command = execCommand("which " + fallback);
		if (!command.isEmpty()) {
			return command;
		}
	}
	return QString();
#endif
}

bool startTerminalEmulator(const QString &workingDir)
{
	QString command = getTerminalCommand();
	if (command.isEmpty()) {
		UtilsUi::txsCritical("Unable to detect a terminal application.");
		return false;
	}
	QStringList args;
	args = command.split(' ');
	command = args.takeFirst();
#ifdef Q_OS_MAC
	// for Terminal.app to open in a specific path it is not sufficent that the
	// workingDir is set. We have to pass it explicitly as argument.
	args << workingDir;
	return QProcess::startDetached(command, args, workingDir);
#else
	return QProcess::startDetached(command, args, workingDir);
#endif
}
