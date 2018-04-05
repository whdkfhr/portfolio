/********************************************************************************
** Form generated from reading UI file 'graduation.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRADUATION_H
#define UI_GRADUATION_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_graduation
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QPushButton *connect_btn;
    QPushButton *record_save_btn;
    QPushButton *play_stop_btn;
    QGroupBox *groupBox_3;
    QCheckBox *turtleNeck_CheckBox;
    QCheckBox *twistedBack_CheckBox;
    QCheckBox *handOnFace_CheckBox;
    QGroupBox *alert_file_setting_groupbox;
    QLabel *label_4;
    QLabel *label;
    QLabel *turtle_neck_alert_file_label;
    QLabel *label_2;
    QLabel *twisted_back_alert_file_label;
    QLabel *label_3;
    QLabel *hand_on_face_alert_file_label;
    QPushButton *turtle_neck_file_btn;
    QPushButton *twisted_back_file_btn;
    QPushButton *hand_on_face_file_btn;
    QGroupBox *forward_head_posture_groupbox;
    QLabel *forward_head_title;
    QLabel *rgb_label;
    QProgressBar *turtle_neck_progress_bar;
    QLabel *forward_head_posture_progressbar_text;
    QFrame *line;
    QGroupBox *slant_posture_groupbox;
    QLabel *slant_posture_title;
    QLabel *ir_label;
    QProgressBar *twisted_back_progress_bar;
    QLabel *slant_posture_progressbar_text;
    QFrame *line_2;
    QGroupBox *groupBox_2;
    QLabel *hand_on_face_title;
    QLabel *depth_label;
    QLabel *hand_on_face_count;
    QFrame *line_3;
    QGroupBox *groupBox_4;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *chart_layout;

    void setupUi(QMainWindow *graduation)
    {
        if (graduation->objectName().isEmpty())
            graduation->setObjectName(QStringLiteral("graduation"));
        graduation->resize(1159, 840);
        QFont font;
        font.setFamily(QStringLiteral("Noto Sans"));
        graduation->setFont(font);
        graduation->setStyleSheet(QStringLiteral(""));
        graduation->setLocale(QLocale(QLocale::Korean, QLocale::SouthKorea));
        centralWidget = new QWidget(graduation);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 430, 361, 191));
        groupBox->setStyleSheet(QLatin1String("QGroupBox {\n"
"	Background-color: #FFF;\n"
"\n"
"	border-radius: 12.5px;\n"
"	border-style: solid;\n"
"	border-color: #bbbbbb;\n"
"	border-width: 1px;\n"
"}"));
        connect_btn = new QPushButton(groupBox);
        connect_btn->setObjectName(QStringLiteral("connect_btn"));
        connect_btn->setGeometry(QRect(10, 20, 61, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Noto Sans"));
        font1.setPointSize(8);
        connect_btn->setFont(font1);
        connect_btn->setAutoFillBackground(false);
        connect_btn->setStyleSheet(QLatin1String("QPushButton {\n"
"	border-style: none;\n"
"	image: url(image/btn_connect.png);\n"
"}\n"
"\n"
""));
        record_save_btn = new QPushButton(groupBox);
        record_save_btn->setObjectName(QStringLiteral("record_save_btn"));
        record_save_btn->setGeometry(QRect(150, 20, 61, 31));
        record_save_btn->setFont(font1);
        record_save_btn->setStyleSheet(QLatin1String("QPushButton {\n"
"	border-style: none;\n"
"	image: url(image/btn_record_gray.png);\n"
"}\n"
"\n"
""));
        play_stop_btn = new QPushButton(groupBox);
        play_stop_btn->setObjectName(QStringLiteral("play_stop_btn"));
        play_stop_btn->setGeometry(QRect(80, 20, 61, 31));
        play_stop_btn->setFont(font1);
        play_stop_btn->setStyleSheet(QLatin1String("QPushButton {\n"
"	border-style: none;\n"
"	image: url(image/btn_play_gray.png);\n"
"}\n"
"\n"
""));
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 60, 341, 121));
        groupBox_3->setStyleSheet(QLatin1String("QGroupBox {\n"
"	border-radius: 0px;\n"
"	border-style: solid;\n"
"	border-color: #d3d3d3;\n"
"	border-width: 2.5px;\n"
"}"));
        turtleNeck_CheckBox = new QCheckBox(groupBox_3);
        turtleNeck_CheckBox->setObjectName(QStringLiteral("turtleNeck_CheckBox"));
        turtleNeck_CheckBox->setGeometry(QRect(10, 10, 291, 22));
        turtleNeck_CheckBox->setFont(font1);
        turtleNeck_CheckBox->setStyleSheet(QLatin1String("QCheckBox {\n"
"	border-style: none;\n"
"	color: #5c5d5d;\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked {\n"
"/*	background-color: #bbbbbb; */\n"
"	image: url(image/unchecked.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"/*	background-color: #1b95d4; */\n"
"	image: url(image/checked(blue mark).png);\n"
"}\n"
""));
        twistedBack_CheckBox = new QCheckBox(groupBox_3);
        twistedBack_CheckBox->setObjectName(QStringLiteral("twistedBack_CheckBox"));
        twistedBack_CheckBox->setGeometry(QRect(10, 50, 261, 22));
        twistedBack_CheckBox->setFont(font1);
        twistedBack_CheckBox->setStyleSheet(QLatin1String("QCheckBox {\n"
"	border-style: none;\n"
"	color: #5c5d5d;\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked {\n"
"/*	background-color: #bbbbbb; */\n"
"	image: url(image/unchecked.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"/*	background-color: #1b95d4; */\n"
"	image: url(image/checked(blue mark).png);\n"
"}\n"
""));
        handOnFace_CheckBox = new QCheckBox(groupBox_3);
        handOnFace_CheckBox->setObjectName(QStringLiteral("handOnFace_CheckBox"));
        handOnFace_CheckBox->setGeometry(QRect(10, 90, 291, 22));
        handOnFace_CheckBox->setFont(font1);
        handOnFace_CheckBox->setStyleSheet(QLatin1String("QCheckBox {\n"
"	border-style: none;\n"
"	color: #5c5d5d;\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked {\n"
"/*	background-color: #bbbbbb; */\n"
"	image: url(image/unchecked.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"/*	background-color: #1b95d4; */\n"
"	image: url(image/checked(blue mark).png);\n"
"}\n"
""));
        alert_file_setting_groupbox = new QGroupBox(centralWidget);
        alert_file_setting_groupbox->setObjectName(QStringLiteral("alert_file_setting_groupbox"));
        alert_file_setting_groupbox->setGeometry(QRect(20, 640, 361, 171));
        QFont font2;
        font2.setFamily(QStringLiteral("High Tower Text"));
        alert_file_setting_groupbox->setFont(font2);
        alert_file_setting_groupbox->setStyleSheet(QLatin1String("\n"
"QGroupBox {\n"
"	Background-color: #FFF;\n"
"	border-radius: 12.5px;\n"
"	border-style: solid;\n"
"	border-color: #bbbbbb;\n"
"	border-width: 1px;\n"
"}\n"
""));
        label_4 = new QLabel(alert_file_setting_groupbox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 10, 91, 18));
        QFont font3;
        font3.setFamily(QStringLiteral("Noto Sans"));
        font3.setBold(true);
        font3.setItalic(false);
        font3.setWeight(75);
        label_4->setFont(font3);
        label_4->setStyleSheet(QLatin1String("QLabel {\n"
"	color:#1b95d4;\n"
"	background-color:#ffffff;\n"
"	border-style:none;\n"
"}"));
        label = new QLabel(alert_file_setting_groupbox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 50, 172, 24));
        label->setFont(font1);
        label->setStyleSheet(QLatin1String("QLabel {\n"
"	color:#5c5d5d;\n"
"	border-style:none;\n"
"	background-color: #ffffff\n"
"}"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        turtle_neck_alert_file_label = new QLabel(alert_file_setting_groupbox);
        turtle_neck_alert_file_label->setObjectName(QStringLiteral("turtle_neck_alert_file_label"));
        turtle_neck_alert_file_label->setGeometry(QRect(190, 50, 101, 24));
        turtle_neck_alert_file_label->setMaximumSize(QSize(16777215, 28));
        QFont font4;
        font4.setFamily(QStringLiteral("Noto Sans"));
        font4.setPointSize(7);
        turtle_neck_alert_file_label->setFont(font4);
        turtle_neck_alert_file_label->setStyleSheet(QLatin1String("Background-color: #FFF;\n"
"\n"
"border-radius: 0px;\n"
"border-style: solid;\n"
"border-color: #bbbbbb;\n"
"border-width: 1px;\n"
"\n"
"color:#5c5d5d;"));
        turtle_neck_alert_file_label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(alert_file_setting_groupbox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 90, 105, 24));
        label_2->setFont(font1);
        label_2->setStyleSheet(QLatin1String("QLabel {\n"
"	color:#5c5d5d;\n"
"	border-style:none;\n"
"	background-color: #ffffff\n"
"}"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        twisted_back_alert_file_label = new QLabel(alert_file_setting_groupbox);
        twisted_back_alert_file_label->setObjectName(QStringLiteral("twisted_back_alert_file_label"));
        twisted_back_alert_file_label->setGeometry(QRect(190, 90, 101, 24));
        twisted_back_alert_file_label->setMaximumSize(QSize(16777215, 28));
        twisted_back_alert_file_label->setFont(font4);
        twisted_back_alert_file_label->setStyleSheet(QLatin1String("Background-color: #FFF;\n"
"\n"
"border-radius: 0px;\n"
"border-style: solid;\n"
"border-color: #bbbbbb;\n"
"border-width: 1px;\n"
"\n"
"color:#5c5d5d;"));
        twisted_back_alert_file_label->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(alert_file_setting_groupbox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 130, 111, 24));
        label_3->setFont(font1);
        label_3->setStyleSheet(QLatin1String("QLabel {\n"
"	color:#5c5d5d;\n"
"	border-style:none;\n"
"	background-color: #ffffff\n"
"}"));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        hand_on_face_alert_file_label = new QLabel(alert_file_setting_groupbox);
        hand_on_face_alert_file_label->setObjectName(QStringLiteral("hand_on_face_alert_file_label"));
        hand_on_face_alert_file_label->setGeometry(QRect(190, 130, 101, 24));
        hand_on_face_alert_file_label->setMaximumSize(QSize(16777215, 28));
        hand_on_face_alert_file_label->setFont(font4);
        hand_on_face_alert_file_label->setStyleSheet(QLatin1String("Background-color: #FFF;\n"
"\n"
"border-radius: 0px;\n"
"border-style: solid;\n"
"border-color: #bbbbbb;\n"
"border-width: 1px;\n"
"\n"
"color:#5c5d5d;"));
        hand_on_face_alert_file_label->setAlignment(Qt::AlignCenter);
        turtle_neck_file_btn = new QPushButton(alert_file_setting_groupbox);
        turtle_neck_file_btn->setObjectName(QStringLiteral("turtle_neck_file_btn"));
        turtle_neck_file_btn->setGeometry(QRect(300, 50, 51, 24));
        turtle_neck_file_btn->setMaximumSize(QSize(16777215, 16777215));
        QFont font5;
        font5.setFamily(QStringLiteral("Noto Sans"));
        font5.setPointSize(9);
        font5.setKerning(true);
        turtle_neck_file_btn->setFont(font5);
        turtle_neck_file_btn->setLayoutDirection(Qt::LeftToRight);
        turtle_neck_file_btn->setStyleSheet(QLatin1String("QPushButton {\n"
"	border-style: none;\n"
"	image: url(image/set.png);\n"
"}"));
        turtle_neck_file_btn->setIconSize(QSize(10, 24));
        twisted_back_file_btn = new QPushButton(alert_file_setting_groupbox);
        twisted_back_file_btn->setObjectName(QStringLiteral("twisted_back_file_btn"));
        twisted_back_file_btn->setGeometry(QRect(300, 90, 51, 24));
        twisted_back_file_btn->setMaximumSize(QSize(60, 16777215));
        QFont font6;
        font6.setFamily(QStringLiteral("Noto Sans"));
        font6.setPointSize(9);
        twisted_back_file_btn->setFont(font6);
        twisted_back_file_btn->setStyleSheet(QLatin1String("\n"
"         QPushButton {\n"
"         border-style: none;\n"
"         image: url(image/set.png);\n"
"         }\n"
"       "));
        twisted_back_file_btn->setIconSize(QSize(10, 24));
        hand_on_face_file_btn = new QPushButton(alert_file_setting_groupbox);
        hand_on_face_file_btn->setObjectName(QStringLiteral("hand_on_face_file_btn"));
        hand_on_face_file_btn->setGeometry(QRect(300, 130, 51, 24));
        hand_on_face_file_btn->setMaximumSize(QSize(60, 16777215));
        hand_on_face_file_btn->setFont(font6);
        hand_on_face_file_btn->setStyleSheet(QLatin1String("\n"
"         QPushButton {\n"
"        	border-style: none;\n"
"         	image: url(image/set.png);\n"
"         }\n"
"       "));
        hand_on_face_file_btn->setIconSize(QSize(10, 24));
        forward_head_posture_groupbox = new QGroupBox(centralWidget);
        forward_head_posture_groupbox->setObjectName(QStringLiteral("forward_head_posture_groupbox"));
        forward_head_posture_groupbox->setGeometry(QRect(10, 10, 371, 401));
        forward_head_posture_groupbox->setStyleSheet(QLatin1String("Background-color: #FFF;\n"
"\n"
"border-radius: 12.5px;\n"
"border-style: solid;\n"
"border-color: #bbbbbb;\n"
"border-width: 1px;"));
        forward_head_title = new QLabel(forward_head_posture_groupbox);
        forward_head_title->setObjectName(QStringLiteral("forward_head_title"));
        forward_head_title->setGeometry(QRect(10, 10, 351, 20));
        QFont font7;
        font7.setFamily(QStringLiteral("Noto Sans"));
        font7.setPointSize(11);
        font7.setBold(true);
        font7.setWeight(75);
        font7.setStyleStrategy(QFont::PreferDefault);
        forward_head_title->setFont(font7);
        forward_head_title->setStyleSheet(QLatin1String("color:#1b95d4;\n"
"border-style:none;"));
        forward_head_title->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        rgb_label = new QLabel(forward_head_posture_groupbox);
        rgb_label->setObjectName(QStringLiteral("rgb_label"));
        rgb_label->setGeometry(QRect(10, 50, 351, 281));
        rgb_label->setStyleSheet(QLatin1String("Background-color: #000;\n"
"border-radius: 0px;"));
        turtle_neck_progress_bar = new QProgressBar(forward_head_posture_groupbox);
        turtle_neck_progress_bar->setObjectName(QStringLiteral("turtle_neck_progress_bar"));
        turtle_neck_progress_bar->setGeometry(QRect(10, 350, 349, 31));
        turtle_neck_progress_bar->setStyleSheet(QLatin1String("QProgressBar { \n"
"	Background-color: #e6e6e5;\n"
"	border-radius: 0px;\n"
"}\n"
"\n"
"QProgressBar::chunk { \n"
"	background: #1b95d4; \n"
"}"));
        turtle_neck_progress_bar->setMinimum(0);
        turtle_neck_progress_bar->setMaximum(5);
        turtle_neck_progress_bar->setValue(0);
        turtle_neck_progress_bar->setTextVisible(false);
        forward_head_posture_progressbar_text = new QLabel(forward_head_posture_groupbox);
        forward_head_posture_progressbar_text->setObjectName(QStringLiteral("forward_head_posture_progressbar_text"));
        forward_head_posture_progressbar_text->setGeometry(QRect(20, 349, 77, 31));
        QFont font8;
        font8.setFamily(QStringLiteral("Noto Sans"));
        font8.setBold(true);
        font8.setWeight(75);
        forward_head_posture_progressbar_text->setFont(font8);
        forward_head_posture_progressbar_text->setStyleSheet(QLatin1String("QLabel {\n"
"	Background: none;\n"
"	border-style:none;\n"
"	color: #fff;\n"
"}\n"
""));
        line = new QFrame(forward_head_posture_groupbox);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 40, 371, 2));
        line->setStyleSheet(QLatin1String("background-color: #eff2f4;\n"
"border-style: none;"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        slant_posture_groupbox = new QGroupBox(centralWidget);
        slant_posture_groupbox->setObjectName(QStringLiteral("slant_posture_groupbox"));
        slant_posture_groupbox->setGeometry(QRect(390, 10, 371, 401));
        slant_posture_groupbox->setStyleSheet(QLatin1String("Background-color: #FFF;\n"
"\n"
"border-radius: 12.5px;\n"
"border-style: solid;\n"
"border-color: #bbbbbb;\n"
"border-width: 1px;"));
        slant_posture_title = new QLabel(slant_posture_groupbox);
        slant_posture_title->setObjectName(QStringLiteral("slant_posture_title"));
        slant_posture_title->setGeometry(QRect(10, 10, 351, 20));
        slant_posture_title->setFont(font7);
        slant_posture_title->setStyleSheet(QLatin1String("color:#1b95d4;\n"
"border-style:none;"));
        slant_posture_title->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ir_label = new QLabel(slant_posture_groupbox);
        ir_label->setObjectName(QStringLiteral("ir_label"));
        ir_label->setGeometry(QRect(10, 50, 351, 281));
        ir_label->setStyleSheet(QLatin1String("Background-color: #000;\n"
"border-radius: 0px;"));
        twisted_back_progress_bar = new QProgressBar(slant_posture_groupbox);
        twisted_back_progress_bar->setObjectName(QStringLiteral("twisted_back_progress_bar"));
        twisted_back_progress_bar->setGeometry(QRect(10, 350, 349, 31));
        twisted_back_progress_bar->setStyleSheet(QLatin1String("QProgressBar { \n"
"	Background-color: #e6e6e5;\n"
"	border-radius: 0px;\n"
"}\n"
"\n"
"QProgressBar::chunk { \n"
"	background: #1b95d4; \n"
"}"));
        twisted_back_progress_bar->setMaximum(10);
        twisted_back_progress_bar->setValue(0);
        twisted_back_progress_bar->setTextVisible(false);
        slant_posture_progressbar_text = new QLabel(slant_posture_groupbox);
        slant_posture_progressbar_text->setObjectName(QStringLiteral("slant_posture_progressbar_text"));
        slant_posture_progressbar_text->setGeometry(QRect(20, 349, 77, 31));
        slant_posture_progressbar_text->setFont(font8);
        slant_posture_progressbar_text->setStyleSheet(QLatin1String("QLabel {\n"
"	Background: none;\n"
"	border-style:none;\n"
"	color: #fff;\n"
"}\n"
""));
        line_2 = new QFrame(slant_posture_groupbox);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(0, 40, 371, 2));
        line_2->setStyleSheet(QLatin1String("background-color: #eff2f4;\n"
"border-style: none;"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(770, 10, 371, 401));
        groupBox_2->setStyleSheet(QLatin1String("Background-color: #FFF;\n"
"\n"
"border-radius: 12.5px;\n"
"border-style: solid;\n"
"border-color: #bbbbbb;\n"
"border-width: 1px;"));
        hand_on_face_title = new QLabel(groupBox_2);
        hand_on_face_title->setObjectName(QStringLiteral("hand_on_face_title"));
        hand_on_face_title->setGeometry(QRect(10, 10, 351, 20));
        hand_on_face_title->setFont(font7);
        hand_on_face_title->setStyleSheet(QLatin1String("color:#1b95d4;\n"
"border-style:none;"));
        hand_on_face_title->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        depth_label = new QLabel(groupBox_2);
        depth_label->setObjectName(QStringLiteral("depth_label"));
        depth_label->setGeometry(QRect(10, 50, 351, 281));
        depth_label->setStyleSheet(QLatin1String("Background-color: #000;\n"
"border-radius: 0px;"));
        hand_on_face_count = new QLabel(groupBox_2);
        hand_on_face_count->setObjectName(QStringLiteral("hand_on_face_count"));
        hand_on_face_count->setGeometry(QRect(10, 340, 349, 51));
        QFont font9;
        font9.setFamily(QStringLiteral("Noto Sans"));
        font9.setPointSize(10);
        hand_on_face_count->setFont(font9);
        hand_on_face_count->setStyleSheet(QLatin1String("border-style: none;\n"
"color: #5c5d5d;"));
        hand_on_face_count->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        hand_on_face_count->setMargin(12);
        line_3 = new QFrame(groupBox_2);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(0, 40, 371, 2));
        line_3->setStyleSheet(QLatin1String("background-color: #eff2f4;\n"
"border-style: none;"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(390, 430, 751, 381));
        groupBox_4->setStyleSheet(QLatin1String("\n"
"QGroupBox {\n"
"	Background-color: #ffffFF;\n"
"	border-radius: 12.5px;\n"
"	border-style: solid;\n"
"	border-color: #bbbbbb;\n"
"	border-width: 1px;\n"
"}\n"
""));
        verticalLayoutWidget_5 = new QWidget(groupBox_4);
        verticalLayoutWidget_5->setObjectName(QStringLiteral("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(10, 10, 731, 361));
        chart_layout = new QVBoxLayout(verticalLayoutWidget_5);
        chart_layout->setSpacing(0);
        chart_layout->setContentsMargins(11, 11, 11, 11);
        chart_layout->setObjectName(QStringLiteral("chart_layout"));
        chart_layout->setContentsMargins(0, 0, 0, 0);
        graduation->setCentralWidget(centralWidget);

        retranslateUi(graduation);

        QMetaObject::connectSlotsByName(graduation);
    } // setupUi

    void retranslateUi(QMainWindow *graduation)
    {
        graduation->setWindowTitle(QApplication::translate("graduation", "\354\236\220\354\204\270\352\265\220\354\240\225\354\234\240\353\217\204\355\224\204\353\241\234\352\267\270\353\236\250", 0));
        groupBox->setTitle(QString());
        connect_btn->setText(QString());
        record_save_btn->setText(QString());
        play_stop_btn->setText(QString());
        groupBox_3->setTitle(QString());
        turtleNeck_CheckBox->setText(QApplication::translate("graduation", "Forward Head Posture Detection", 0));
        twistedBack_CheckBox->setText(QApplication::translate("graduation", "Slant Posture Detection", 0));
        handOnFace_CheckBox->setText(QApplication::translate("graduation", "Hand On Face Detection", 0));
        alert_file_setting_groupbox->setTitle(QString());
        label_4->setText(QApplication::translate("graduation", "Alert files", 0));
        label->setText(QApplication::translate("graduation", "Forward Head Posture", 0));
        turtle_neck_alert_file_label->setText(QString());
        label_2->setText(QApplication::translate("graduation", "Slant Posture", 0));
        twisted_back_alert_file_label->setText(QString());
        label_3->setText(QApplication::translate("graduation", "Hand On Face", 0));
        hand_on_face_alert_file_label->setText(QString());
        turtle_neck_file_btn->setText(QString());
        twisted_back_file_btn->setText(QString());
        hand_on_face_file_btn->setText(QString());
        forward_head_posture_groupbox->setTitle(QString());
        forward_head_title->setText(QApplication::translate("graduation", "Forward Head Posture", 0));
        rgb_label->setText(QString());
#ifndef QT_NO_TOOLTIP
        turtle_neck_progress_bar->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        turtle_neck_progress_bar->setFormat(QApplication::translate("graduation", "%p%", 0));
        forward_head_posture_progressbar_text->setText(QApplication::translate("graduation", "0 grade", 0));
        slant_posture_groupbox->setTitle(QString());
        slant_posture_title->setText(QApplication::translate("graduation", "Slant Posture", 0));
        ir_label->setText(QString());
        slant_posture_progressbar_text->setText(QApplication::translate("graduation", "0.0 / 10.0", 0));
        groupBox_2->setTitle(QString());
        hand_on_face_title->setText(QApplication::translate("graduation", "Hand On Face", 0));
        depth_label->setText(QString());
        hand_on_face_count->setText(QApplication::translate("graduation", "Count : 0", 0));
        groupBox_4->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class graduation: public Ui_graduation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRADUATION_H
