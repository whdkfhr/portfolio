#include "MainWindow.h"

// public

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	myPlayer = new Player();
	
	ui.setupUi(this);
	set_thread_signal_slots();
	set_button_signal_slots();
	set_alert_signal_slots();

	set_turtle_neck_tooltips();

	set_setting_from_file();
	
	set_charts();

	// for debugging
	connect(myPlayer, SIGNAL(player_echo(const QString&)), this, SLOT(echo(const QString&)));
}

MainWindow::~MainWindow()
{
	delete myPlayer;
	delete chartView;
}




////////////////////////////////////////////// private

void MainWindow::set_thread_signal_slots()
{
	// three image
	connect(myPlayer, SIGNAL(set1stWidget(const QImage&)), this, SLOT(update1stWidget(const QImage&)));
	connect(myPlayer, SIGNAL(set2ndWidget(const QImage&)), this, SLOT(update2ndWidget(const QImage&)));
	connect(myPlayer, SIGNAL(set3rdWidget(const QImage&)), this, SLOT(update3rdWidget(const QImage&)));

	// summary
	connect(myPlayer, SIGNAL(setForwardHeadProgressBar(const int)), this, SLOT(update1stSummary(const int)));
	connect(myPlayer, SIGNAL(setTwistedBackProgressBar(const qreal)), this, SLOT(update2ndSummary(const qreal)));
	connect(myPlayer, SIGNAL(setHandOnFaceCount(const int)), this, SLOT(update3rdSummary(const int)));
	
	// update chart signal
	connect(myPlayer, SIGNAL(update_forward_head_chart_signal(const qreal, const qint16)), this, SLOT(updateForwardHeadChart(const qreal, const qint16)));
	connect(myPlayer, SIGNAL(update_slant_posture_chart_signal(const qreal, const qreal)), this, SLOT(updateTwistedBackChart(const qreal, const qreal)));
	connect(myPlayer, SIGNAL(update_hand_on_face_chart_signal(const qreal, const bool)), this, SLOT(updateHandOnFaceChart(const qreal, const bool)));

	connect(myPlayer, SIGNAL(whether_to_scroll_signal(const qreal)), this, SLOT(updateChartScroll(const qreal)));
}

void MainWindow::set_button_signal_slots() {
	connect(ui.turtleNeck_CheckBox, SIGNAL(clicked(bool)), this, SLOT(turtle_neck_checkbox_changed(bool)));
	connect(ui.twistedBack_CheckBox, SIGNAL(clicked(bool)), this, SLOT(twisted_back_checkbox_changed(bool)));
	connect(ui.handOnFace_CheckBox, SIGNAL(clicked(bool)), this, SLOT(hand_on_face_checkbox_changed(bool)));

	connect(ui.connect_btn, SIGNAL(clicked()), ui.centralWidget, SLOT(on_connect_btn_clicked()));
	connect(ui.play_stop_btn, SIGNAL(clicked()), ui.centralWidget, SLOT(on_play_stop_btn_clicked()));
	connect(ui.record_save_btn, SIGNAL(clicked()), ui.centralWidget, SLOT(on_record_save_btn_clicked()));

	ui.play_stop_btn->setEnabled(false);
	ui.record_save_btn->setEnabled(false);

	// what's difference?
//	connect(ui.connect_btn, SIGNAL(clicked()), this, SLOT(on_connect_btn_clicked()));
//	connect(ui.play_stop_btn, SIGNAL(clicked()), this, SLOT(on_play_stop_btn_clicked()));
//	connect(ui.record_save_btn, SIGNAL(clicked()), this, SLOT(on_record_save_btn_clicked()));

	connect(ui.twisted_back_file_btn, SIGNAL(clicked()), this, SLOT(on_twisted_back_file_set_btn_clicked()));
	connect(ui.turtle_neck_file_btn, SIGNAL(clicked()), this, SLOT(on_turtle_neck_file_set_btn_clicked()));
	connect(ui.hand_on_face_file_btn, SIGNAL(clicked()), this, SLOT(on_hand_on_face_file_set_btn_clicked()));
}

void MainWindow::set_alert_signal_slots() {
	connect(myPlayer, SIGNAL(handOnFaceSignal()), this, SLOT(alert_hand_on_face()));
	connect(myPlayer, SIGNAL(turtleNeckSignal()), this, SLOT(alert_turtle_neck()));
	connect(myPlayer, SIGNAL(twistedBackSignal()), this, SLOT(alert_twisted_back()));
}

void MainWindow::set_turtle_neck_tooltips() {
	//ui.forward_head_grade1->setToolTip(TURTLENECK_GRADE_DESCRIPTION[0]);
	//ui.forward_head_grade2->setToolTip(TURTLENECK_GRADE_DESCRIPTION[1]);
	//ui.forward_head_grade3->setToolTip(TURTLENECK_GRADE_DESCRIPTION[2]);
	//ui.forward_head_grade4->setToolTip(TURTLENECK_GRADE_DESCRIPTION[3]);
	//ui.forward_head_grade5->setToolTip(TURTLENECK_GRADE_DESCRIPTION[4]);
}

void MainWindow::set_setting_from_file()
{
	QSettings setting(INFO_FILE, QSettings::IniFormat);

	// detection setting
	setting.beginGroup(DETECTION_SETTING_GROUP);

	if (setting.value(DETECT_TURTLE_NECK).toBool()) {
		ui.turtleNeck_CheckBox->setCheckState(Qt::Checked);
		myPlayer->set_whether_turtle_neck(true);
	}

	if (setting.value(DETECT_TWISTED_BACK).toBool()) {
		ui.twistedBack_CheckBox->setCheckState(Qt::Checked);
		myPlayer->set_whether_twisted_back(true);
	}
		
	if (setting.value(DETECT_HAND_ON_FACE).toBool()) {
		ui.handOnFace_CheckBox->setCheckState(Qt::Checked);
		myPlayer->set_whether_hand_on_face(true);
	}
		

	setting.endGroup();

	// alert file setting
	setting.beginGroup(ALERT_FILE_GROUP);
	
	QString alert_turtle_neck_file_path = setting.value(TURTLE_NECK_FILE_SETTING).toString();
	alertTurtleNeck.set_file_path(alert_turtle_neck_file_path);
	ui.turtle_neck_alert_file_label->setText(get_filename_from_filepath(alert_turtle_neck_file_path));

	QString alert_twisted_back_file_path = setting.value(TWISTED_BACK_FILE_SETTING).toString();
	alertTwistedBack.set_file_path(alert_twisted_back_file_path);
	ui.twisted_back_alert_file_label->setText(get_filename_from_filepath(alert_twisted_back_file_path));

	QString alert_hand_on_face_file_path = setting.value(HAND_ON_FACE_FILE_SETTING).toString();
	alertHandOnFace.set_file_path(alert_hand_on_face_file_path);
	ui.hand_on_face_alert_file_label->setText(get_filename_from_filepath(alert_hand_on_face_file_path));

	setting.endGroup();

}

void MainWindow::set_charts()
{
	chartView = new ChartView;
	ui.chart_layout->addWidget(chartView);
}

QString MainWindow::get_video_file_name()
{
	return QFileDialog::getOpenFileName(this,
		tr("Open Video"), ".",
		tr("Video Files (*.avi *.mpg *.mp4)"));
}

QString MainWindow::get_audio_file_name()
{
	return QFileDialog::getOpenFileName(this,
		tr("Open Video"), ".",
		tr("Video Files (*.mp3 *.wmv)"));
}

void MainWindow::load_video_from_BasicCam() {
	if (!myPlayer->isConnected())
	{
		if (!myPlayer->loadBasicCam())
		{
			QMessageBox msgBox;
			msgBox.setText("Can't open Basic Cam..");
			msgBox.exec();
		}
		else
		{
		//	ui.connect_btn->setText(tr("Disconnect"));
		}
	}
	else
	{
		myPlayer->disConnect();
	//	ui.connect_btn->setText(tr("Connect"));
		myPlayer->Stop();
		ui.play_stop_btn->setText(tr("Play"));
	}
}

void MainWindow::load_video_from_local()	// disconnect not implemented
{
//	QString filename = get_video_file_name();

//	if (!filename.isEmpty()){
	//	if (!myPlayer->loadLocalVideo(filename.toUtf8().data()))
		if (!myPlayer->loadLocalVideos())
		{
			echo("The selected video could not be opened!");
		}
		else
		{
			ui.play_stop_btn->setEnabled(true);
			ui.play_stop_btn->setStyleSheet(PLAY_BTN);

			ui.record_save_btn->setEnabled(true);
			ui.record_save_btn->setStyleSheet(RECORD_BTN);
		}
//	}
}

void MainWindow::load_video_from_kinect()
{
//	myPlayer->setKinectConnect(); need it?
	if (!myPlayer->isConnected())
	{
		if (!myPlayer->loadKinectCam())
		{
			echo("Can't open kinect cam");
		}
		else
		{
			ui.play_stop_btn->setEnabled(true);
			ui.play_stop_btn->setStyleSheet(PLAY_BTN);

			ui.record_save_btn->setEnabled(true);
			ui.record_save_btn->setStyleSheet(RECORD_BTN);
		}
	}
	else
	{
		myPlayer->Stop();
		myPlayer->disConnect();

		ui.play_stop_btn->setEnabled(false);
		ui.play_stop_btn->setStyleSheet(PLAY_BTN_DISABLED);

		ui.record_save_btn->setEnabled(false);
		ui.record_save_btn->setStyleSheet(RECORD_BTN_DISABLED);
	}
}

const QString MainWindow::get_filename_from_filepath(const QString& file_path)
{
	return file_path.split("/").back();
}

void MainWindow::echo(const QString& message)
{
	QMessageBox msgBox;
	msgBox.setText(message);
	msgBox.exec();
}




////////////////////////////////////////////////////////////////////////////
/////////////////////////////// public slots ///////////////////////////////
////////////////////////////////////////////////////////////////////////////

void MainWindow::update1stWidget(const QImage& image)
{
	if (!image.isNull())
	{
		//	ui.rgb_opengl_widget->update();
		ui.rgb_label->setAlignment(Qt::AlignCenter);
		ui.rgb_label->setPixmap(QPixmap::fromImage(image).scaled(ui.rgb_label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
	}
}

void MainWindow::update2ndWidget(const QImage& image)
{
	if (!image.isNull())
	{
		ui.ir_label->setAlignment(Qt::AlignCenter);
		ui.ir_label->setPixmap(QPixmap::fromImage(image).scaled(ui.ir_label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
	}
}

void MainWindow::update3rdWidget(const QImage& image)
{
	if (!image.isNull())
	{
		ui.depth_label->setAlignment(Qt::AlignCenter);
		ui.depth_label->setPixmap(QPixmap::fromImage(image).scaled(ui.depth_label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
	}
}

void MainWindow::update1stSummary(const int degree)
{
	ui.turtle_neck_progress_bar->setValue(degree);
	ui.forward_head_posture_progressbar_text->setText(QString::number(degree) + " grade");

	// works fine but i hate this style
/*	ui.turtle_neck_progress_bar->setStyleSheet(ui.turtle_neck_progress_bar->property("defaultStyleSheet").toString() +
		" QProgressBar::chunk { background: red; }");*/	


//	QPalette p;// = ui.turtle_neck_progress_bar->palette();
////	p.setColor(QPalette::Base, QColor(Qt::darkYellow));
////	p.setColor(QPalette::Background, Qt::green);
//	p.setColor(QPalette::Base, QColor(Qt::red));
//	ui.turtle_neck_progress_bar->setPalette(p);

	//if (degree >= 3) {
	//	ui.turtle_neck_progress_bar->setStyleSheet(ui.turtle_neck_progress_bar->property("defaultStyleSheet").toString() +
	//	" QProgressBar::chunk { background: red; }");
	//}
	//else {
	//	ui.turtle_neck_progress_bar->setStyleSheet(ui.turtle_neck_progress_bar->property("defaultStyleSheet").toString() +
	//	" QProgressBar::chunk { background: lightgreen; }");
	//}


	// pre-used code
	//ui.turtle_neck_progress_bar->setStyleSheet(ui.turtle_neck_progress_bar->property("defaultStyleSheet").toString() +
	//	" QProgressBar::chunk { background: " + TUTTLENECK_DEGREE_COLOR[degree - 1] + "; }");
	

	//ui.turtle_neck_progress_bar->setToolTipDuration(-1);
	//ui.turtle_neck_progress_bar->setToolTip("hey u!!");

//	ui.label->setText("this is text");
//	ui.label->setToolTip(tr("dsfafa"));
	
	/*ui.turtle_neck_progress_bar->setStyleSheet("::chunk {"
		"background-color: "
		"qlineargradient(x0: 0, x2: 1, "
		"stop: 0 green, stop: 0.3 lightgreen, "
		"stop: 0.45 yellow, stop: 0.6 orange, "
		"stop: 1 red"
		")}");*/
//	ui.turtle_neck_progress_bar->setText(s);
}

void MainWindow::update2ndSummary(const qreal value)
{
	ui.twisted_back_progress_bar->setValue(value);
	ui.slant_posture_progressbar_text->setText(QString::number(value, 'f', 2));
}

void MainWindow::update3rdSummary(const int value)
{
	ui.hand_on_face_count->setText("Count : " + QString::number(value));
}

void MainWindow::updateForwardHeadChart(const qreal time, const qint16 grade)
{
	chartView->update_forward_head_chart(time, grade);
}

void MainWindow::updateTwistedBackChart(const qreal time, const qreal value)
{
	chartView->update_slant_posture_chart(time, value);
}

void MainWindow::updateHandOnFaceChart(const qreal time, const bool is_detected)
{
	chartView->update_hand_on_face_chart(time, is_detected);
}

void MainWindow::updateChartScroll(const qreal time)
{
	chartView->update_chart_scroll(time);
}

void MainWindow::alert_hand_on_face()
{
	alertHandOnFace.alert_sound();
}

void MainWindow::alert_turtle_neck()
{
	alertTurtleNeck.alert_sound();
}

void MainWindow::alert_twisted_back()
{
	alertTwistedBack.alert_sound();
}



////////////////////////////////////////////////////////////////////////////
////////////////////////////// private slots ///////////////////////////////
////////////////////////////////////////////////////////////////////////////

void MainWindow::turtle_neck_checkbox_changed(bool checkstate)
{
	QSettings setting(INFO_FILE, QSettings::IniFormat);
	setting.beginGroup(DETECTION_SETTING_GROUP);

	myPlayer->set_whether_turtle_neck(checkstate);
	if (checkstate == true)
	{
		if (myPlayer->isRunning()) 
			myPlayer->start_turtle_neck_detect();
	}
	else
	{
		if (myPlayer->isRunning())
			myPlayer->stop_turtle_neck_detect();
	}
	setting.setValue(DETECT_TURTLE_NECK, checkstate);
	setting.endGroup();
}

void MainWindow::twisted_back_checkbox_changed(bool checkstate)
{
	QSettings setting(INFO_FILE, QSettings::IniFormat);
	setting.beginGroup(DETECTION_SETTING_GROUP);

	myPlayer->set_whether_twisted_back(checkstate);
	if (checkstate == true)
	{	
		if (myPlayer->isRunning())
			myPlayer->start_twisted_back_detect();
	}
	else
	{
		if (myPlayer->isRunning())
			myPlayer->stop_twisted_back_detect();
	}
	setting.setValue(DETECT_TWISTED_BACK, checkstate);
	setting.endGroup();
}

void MainWindow::hand_on_face_checkbox_changed(bool checkstate)
{
	QSettings setting(INFO_FILE, QSettings::IniFormat);
	setting.beginGroup(DETECTION_SETTING_GROUP);

	myPlayer->set_whether_hand_on_face(checkstate);
	if (checkstate == true)
	{
		if (myPlayer->isRunning())
			myPlayer->start_hand_on_face_detect();
	}
	else
	{
		if (myPlayer->isRunning())
			myPlayer->stop_hand_on_face_detect();
	}
	setting.setValue(DETECT_HAND_ON_FACE, checkstate);
	setting.endGroup();
}

void MainWindow::on_connect_btn_clicked() {
//	load_video_from_BasicCam();
//	load_video_from_local();
	load_video_from_kinect();
}

void MainWindow::on_play_stop_btn_clicked() {

	if (myPlayer->isConnected() && myPlayer->isStopped())
	{
		myPlayer->Play();
		ui.play_stop_btn->setStyleSheet(PAUSE_BTN);
	}
	else
	{
		myPlayer->Stop();
		ui.play_stop_btn->setStyleSheet(PLAY_BTN);
	}
}

// not done
void MainWindow::on_record_save_btn_clicked()
{
	if (myPlayer->isConnected() && myPlayer->isRunning())
	{
		if (!myPlayer->getIsRecording())
		{
			myPlayer->startRecording();
		}
		else
		{
			myPlayer->stopRecording();
		}
	}
	else
	{
		echo("fuck off");
	}
}

void MainWindow::on_turtle_neck_file_set_btn_clicked()
{
	QString file_path = get_audio_file_name();

	if (file_path == NULL) return;

	alertTurtleNeck.set_file_path(file_path);
	ui.turtle_neck_alert_file_label->setText(get_filename_from_filepath(file_path));

	QSettings setting(INFO_FILE, QSettings::IniFormat);

	setting.beginGroup(ALERT_FILE_GROUP);
	setting.setValue(TURTLE_NECK_FILE_SETTING, file_path);
	setting.endGroup();
}

void MainWindow::on_twisted_back_file_set_btn_clicked()
{
	QString file_path = get_audio_file_name();

	if (file_path == NULL) return;

	alertTwistedBack.set_file_path(file_path);
	ui.twisted_back_alert_file_label->setText(get_filename_from_filepath(file_path));

	QSettings setting(INFO_FILE, QSettings::IniFormat);

	setting.beginGroup(ALERT_FILE_GROUP);
	setting.setValue(TWISTED_BACK_FILE_SETTING, file_path);
	setting.endGroup();
}



void MainWindow::on_hand_on_face_file_set_btn_clicked()
{
	QString file_path = get_audio_file_name();

	if (file_path == NULL) return;

	alertHandOnFace.set_file_path(file_path);
	ui.hand_on_face_alert_file_label->setText(get_filename_from_filepath(file_path));

	QSettings setting(INFO_FILE, QSettings::IniFormat);

	setting.beginGroup(ALERT_FILE_GROUP);
	setting.setValue(HAND_ON_FACE_FILE_SETTING, file_path);
	setting.endGroup();
}


