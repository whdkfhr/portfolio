#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_graduation.h"
#include "opencv2/opencv.hpp"
#include "Alert.h"
#include <Player.h>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QtMultimedia/QMediaPlayer>
#include <QSettings>
#include <description.h>
#include <chartView.h>

const QString INFO_FILE = "information.ini";

const QString DETECTION_SETTING_GROUP = "Detection_Settings";
const QString DETECT_TURTLE_NECK = "turtle_neck";
const QString DETECT_TWISTED_BACK = "twisted_back";
const QString DETECT_HAND_ON_FACE = "hand_on_face";

const QString ALERT_FILE_GROUP = "Alert_Files";
const QString TURTLE_NECK_FILE_SETTING = "turtle_neck";
const QString TWISTED_BACK_FILE_SETTING = "twisted_back";
const QString HAND_ON_FACE_FILE_SETTING = "hand_on_face";

// button img files
const QString CONNECT_BTN = "QPushButton { border-style: none; image: url(image/btn_connect.png); }";
const QString PLAY_BTN_DISABLED = "QPushButton { border-style: none; image: url(image/btn_play_gray.png); }";
const QString PLAY_BTN = "QPushButton { border-style: none; image: url(image/btn_play.png); }";
const QString PAUSE_BTN = "QPushButton { border-style: none; image: url(image/btn_pause.png); }";
const QString RECORD_BTN = "QPushButton { border-style: none; image: url(image/btn_record.png); }";
const QString RECORD_BTN_DISABLED = "QPushButton { border-style: none; image: url(image/btn_record_gray.png); }";

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	// slots for Player thread
	void update1stWidget(const QImage&);
	void update2ndWidget(const QImage&);
	void update3rdWidget(const QImage&);
	
	void update1stSummary(const int);
	void update2ndSummary(const qreal);
	void update3rdSummary(const int);

	void updateForwardHeadChart(const qreal, const qint16);
	void updateTwistedBackChart(const qreal, const qreal);
	void updateHandOnFaceChart(const qreal, const bool);

	void updateChartScroll(const qreal);

	void alert_hand_on_face();
	void alert_turtle_neck();
	void alert_twisted_back();

private slots:
	// whether to detect checkbox slots
	void turtle_neck_checkbox_changed(bool checkstate);
	void twisted_back_checkbox_changed(bool checkstate);
	void hand_on_face_checkbox_changed(bool checkstate);

	// connect, play/stop, record/save button slots
	void on_connect_btn_clicked();
	void on_play_stop_btn_clicked();
	void on_record_save_btn_clicked();

	// alert file setting button slots
	void on_turtle_neck_file_set_btn_clicked();
	void on_twisted_back_file_set_btn_clicked();
	void on_hand_on_face_file_set_btn_clicked();

	// displaying QDialog
	void echo(const QString& message);

private:
	// init functions
	void set_button_signal_slots();
	void set_thread_signal_slots();
	void set_alert_signal_slots();

	void set_turtle_neck_tooltips();

	void set_setting_from_file();

	void set_charts();

	QString get_video_file_name();
	QString get_audio_file_name();

	void load_video_from_BasicCam();
	void load_video_from_local();
	void load_video_from_kinect();

	const QString get_filename_from_filepath(const QString& file_path);

	

	Ui::graduation ui;
	Player *myPlayer;

	Alert alertHandOnFace;
	Alert alertTurtleNeck;
	Alert alertTwistedBack;
	
	ChartView *chartView;
};

#endif // MAINWINDOW_H