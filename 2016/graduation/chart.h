#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>	// abline
#include <QtCharts/QCategoryAxis>
#include <QtCharts/qscatterseries.h>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtCore/QDebug>


QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

const qint16 LINE_THICKNESS = 2;
const QColor FORWARD_HEAD_LINE_COLOR = "#d13355";
const QColor TWISTED_BACK_LINE_COLOR = "#f39800"; //"#ffcd12";//"#f48a3b"; // by designer
const QColor HAND_ON_FACE_LINE_COLOR = "#313b82";

const QString FORWARD_HEAD_LINE_NAME = "Forward Head";
const QString TWISTED_BACK_LINE_NAME = "Slant Posture";
const QString HAND_ON_FACE_LINE_NAME = "Hand On Face";

const qreal HAND_DETECTED = 1.5;
const qreal HAND_NOT_DETECTED = 0.5;


class Chart : public QChart
{
	Q_OBJECT

public:
	Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
	virtual ~Chart();

	void update_forward_head_chart(const qreal time, const qint16 grade);
	void update_slant_posture_chart(const qreal time, const qreal value);
	void update_hand_on_face_chart(const qreal time, const bool is_detected);

	void update_chart_scroll(const qreal time);

public slots:
	void handleTimeout();

private:
	QTimer m_timer;

//	QTime m_time;

	QValueAxis *time_axis;
	QValueAxis *forward_head_axis;
	QValueAxis *twisted_back_axis;
//	QValueAxis *hand_on_face_axis;
	QCategoryAxis *hand_on_face_axis;

	// each spline series
	QLineSeries *forward_head_series;
	QSplineSeries *twisted_back_series;
	QLineSeries *hand_on_face_series;
	//	QScatterSeries *hand_on_face_series;

	QStringList m_titles; // what's this?

	uint cumulative_time = 0;
};

#endif /* CHART_H */