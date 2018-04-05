#pragma once

#include <QString>
#include <QtMultimedia/QMediaPlayer>

class Alert
{
public:
	Alert();
	Alert(const QString& file_path);
	void set_file_path(const QString& file_path);
	const QString& get_file_path() const;
	 
	bool alert_sound() const;
	~Alert();

private:
	QString file_path;
	QMediaPlayer *media_player;
};

