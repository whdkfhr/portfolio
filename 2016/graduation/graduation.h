#ifndef GRADUATION_H
#define GRADUATION_H

#include <QtWidgets/QMainWindow>
#include "ui_graduation.h"
#include "opencv2/opencv.hpp"
#include <Player.h>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <player.h>

class graduation : public QMainWindow
{
	Q_OBJECT

public:
	graduation(QWidget *parent = 0);
	~graduation();

private slots:
	void updateRGBWidget(QImage rgb_image);
	void updateDepthWidget(QImage depth_image);
	void on_connect_btn_clicked();
	void on_play_stop_btn_clicked();

private:
	void set_button();
	/*
	void load_rgb_capture();
	void load_depth_capture();
	bool check_rgb_capture();
	bool check_depth_capture();
	void check_opened();
	*/
	Ui::graduationClass ui;
	Player *myPlayer;
};

#endif // GRADUATION_H
