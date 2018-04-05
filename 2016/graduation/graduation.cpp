#include "graduation.h"

// public



graduation::graduation(QWidget *parent)
	: QMainWindow(parent)
{
	myPlayer = new Player();
	QObject::connect(myPlayer, SIGNAL(processedRGBImage(QImage)), this, SLOT(updateRGBWidget(QImage)));
	QObject::connect(myPlayer, SIGNAL(processedDepthImage(QImage)), this, SLOT(updateDepthWidget(QImage)));
	ui.setupUi(this);
	set_button();
}

void graduation::set_button() {
	connect(ui.connect_btn, SIGNAL(clicked()), ui.centralWidget, SLOT(on_start_btn_clicked()));
	connect(ui.play_stop_btn, SIGNAL(clicked()), ui.centralWidget, SLOT(on_end_btn_clicked()));
}

void graduation::updateRGBWidget(QImage rgb_image)
{
	if (!rgb_image.isNull())
	{
		ui.rgb_label->setAlignment(Qt::AlignCenter);
		ui.rgb_label->setPixmap(QPixmap::fromImage(rgb_image).scaled(ui.rgb_label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
	}
}

void graduation::updateDepthWidget(QImage depth_image)
{
	if (!depth_image.isNull())
	{
		ui.depth_label->setAlignment(Qt::AlignCenter);
		ui.depth_label->setPixmap(QPixmap::fromImage(depth_image).scaled(ui.depth_label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
	}
}

graduation::~graduation()
{
	delete myPlayer;
}



// private slots

void graduation::on_connect_btn_clicked() {

	/*
	QString filename = QFileDialog::getOpenFileName(this,
		tr("Open Video"), ".",
		tr("Video Files (*.avi *.mpg *.mp4)"));

	if (!filename.isEmpty()){
		if (!myPlayer->loadVideo(filename.toUtf8().data()))
		{
			QMessageBox msgBox;
			msgBox.setText("The selected video could not be opened!");
			msgBox.exec();
		}
	}
	*/
	if (!myPlayer->isConnected() )
	{
		if (!myPlayer->loadVideo("Kinect"))
		{
			QMessageBox msgBox;
			msgBox.setText("Can't open cam..");
			msgBox.exec();
		}
		else {
			ui.connect_btn->setText(tr("Disconnect"));
		}
	}
	else 
	{
		myPlayer->disConnect();
		ui.connect_btn->setText(tr("Connect"));
		myPlayer->Stop();
		ui.play_stop_btn->setText(tr("Play"));
	}
	
}

void graduation::on_play_stop_btn_clicked() {
	if ( myPlayer->isConnected() && myPlayer->isStopped())
	{
		myPlayer->Play();
		ui.play_stop_btn->setText(tr("Stop"));
	}
	else
	{
		myPlayer->Stop();
		ui.play_stop_btn->setText(tr("Play"));
	}
}



// private

/*

void graduation::load_rgb_capture() {
	this->rgb_capture.open("test.wmv");
}

void graduation::load_depth_capture() {
	this->depth_capture.open("test.wmv");
}

bool graduation::check_rgb_capture() {
	if (!rgb_capture.isOpened())
		return false;
	return true;
}

void graduation::check_opened() {
	const QString NO_RGB = "no rgb";
	const QString NO_DEPTH = "no depth";

	if (!check_rgb_capture()) {
		ui.statusBar->showMessage(NO_RGB);
	}

	if (!check_depth_capture()) {
		ui.statusBar->showMessage(NO_DEPTH);
	}
}

bool graduation::check_depth_capture() {
	if (!rgb_capture.isOpened())
		return false;
	return true;
}

*/

