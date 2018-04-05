#include "Alert.h"

Alert::Alert()
{
	media_player = new QMediaPlayer;
	this->file_path = "";
}

Alert::Alert(const QString& file_path)
{
	media_player = new QMediaPlayer;
	set_file_path(file_path);
}

void Alert::set_file_path(const QString& file_path)
{
	media_player->setMedia(QUrl::fromLocalFile(file_path));
	this->file_path = file_path;
}

const QString& Alert::get_file_path() const
{
	return file_path;
}

bool Alert::alert_sound() const
{
	media_player->play();
	return media_player->isAudioAvailable();
}

Alert::~Alert()
{
	delete media_player;
}