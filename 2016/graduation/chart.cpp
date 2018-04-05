#include "chart.h"

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
		QChart(QChart::ChartTypeCartesian, parent, wFlags),
		time_axis(new QValueAxis),
		forward_head_axis(new QValueAxis),
		twisted_back_axis(new QValueAxis),
		hand_on_face_axis(new QCategoryAxis),
		forward_head_series(new QLineSeries(this)),
		twisted_back_series(new QSplineSeries(this)),
hand_on_face_series(new QLineSeries(this))
{
	// timer
	//qsrand((uint)QTime::currentTime().msec());
	//connect(&m_timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
	//m_timer.setInterval(1000);

	//forward_head_series = new QSplineSeries(this);
	//QPen twisted_back_pen(Qt::forward_head_pen);
	//twisted_back_pen.setWidth(3);
	//forward_head_series->setPen(twisted_back_pen);
	//forward_head_series->append(m_x, m_y);

	//addSeries(forward_head_series);
	//createDefaultAxes();
	//setAxisX(m_axis, forward_head_series);
	//m_axis->setTickCount(5);
	//axisX()->setRange(0, 10);
	//axisY()->setRange(-5, 10);


	// axis
	time_axis->setTickCount(16);
	time_axis->setRange(0, 30);
//	time_axis->setTitleText("time");
//	time_axis->setLabelsAngle(20);
	time_axis->setLabelsFont(QFont("noto sans"));
	time_axis->setLabelFormat("%.0f");
	addAxis(time_axis, Qt::AlignBottom);

	forward_head_axis->setTickCount(7);
	forward_head_axis->setRange(0, 6);
	forward_head_axis->setLabelsFont(QFont("noto sans"));
	forward_head_axis->setLabelFormat("%.0f");
	forward_head_axis->setLabelsColor(FORWARD_HEAD_LINE_COLOR);
	addAxis(forward_head_axis, Qt::AlignLeft);

	twisted_back_axis->setTickCount(6);
	twisted_back_axis->setRange(0, 10);
	twisted_back_axis->setLabelsFont(QFont("noto sans"));
	twisted_back_axis->setLabelFormat("%.1f");
	twisted_back_axis->setLabelsColor(TWISTED_BACK_LINE_COLOR);
	addAxis(twisted_back_axis, Qt::AlignRight);

//	hand_on_face_axis->setTickCount(3);
	hand_on_face_axis->setLabelsFont(QFont("noto sans"));
	hand_on_face_axis->append("down", 0);
	hand_on_face_axis->append("up", 2);
	hand_on_face_axis->setRange(0, 2);
	hand_on_face_axis->setLabelsColor(HAND_ON_FACE_LINE_COLOR);
	hand_on_face_axis->setVisible(false);
	addAxis(hand_on_face_axis, Qt::AlignRight);

	// spline series
	QPen forward_head_pen(FORWARD_HEAD_LINE_COLOR);
	forward_head_pen.setWidth(LINE_THICKNESS);
	forward_head_series->setPen(forward_head_pen);
	forward_head_series->setName(FORWARD_HEAD_LINE_NAME);
//	forward_head_series->setColor(TWISTED_BACK_LINE_COLOR);
	forward_head_series->append(0, 0);

	addSeries(forward_head_series);
	forward_head_series->attachAxis(time_axis);
	forward_head_series->attachAxis(forward_head_axis);
	

	QPen twisted_back_pen(TWISTED_BACK_LINE_COLOR);
	twisted_back_pen.setWidth(LINE_THICKNESS);
	twisted_back_series->setPen(twisted_back_pen);
//	twisted_back_series->setPointLabelsFont(QFont("noto sans"));
	twisted_back_series->setName(TWISTED_BACK_LINE_NAME);
	twisted_back_series->pointLabelsColorChanged(TWISTED_BACK_LINE_COLOR);
	twisted_back_series->append(0, 0);

	addSeries(twisted_back_series);
	twisted_back_series->attachAxis(time_axis);
	twisted_back_series->attachAxis(twisted_back_axis);


	QPen hand_on_face_pen(HAND_ON_FACE_LINE_COLOR);
	hand_on_face_pen.setWidth(LINE_THICKNESS);
	hand_on_face_series->setPen(hand_on_face_pen);
	hand_on_face_series->setName(HAND_ON_FACE_LINE_NAME);
	hand_on_face_series->append(0, 0.5);

	//QPen hand_on_face_pen(HAND_ON_FACE_LINE_COLOR);
	//hand_on_face_pen.setWidth(LINE_THICKNESS);
	//hand_on_face_series->setPen(hand_on_face_pen);
	//hand_on_face_series->setName(HAND_ON_FACE_LINE_NAME);
	//hand_on_face_series->setColor(HAND_ON_FACE_LINE_COLOR);
	//hand_on_face_series->setMarkerSize(5);

	addSeries(hand_on_face_series);
	hand_on_face_series->attachAxis(time_axis);
	hand_on_face_series->attachAxis(hand_on_face_axis);

//	m_timer.start();

//	m_time.start();

	//QBarSet *barSet = new QBarSet(QString("set ") + QString::number(m_series->count()));
	//qreal delta = m_series->count() * 0.1;
	//*barSet << 1 + delta << 2 + delta << 3 + delta << 4 + delta;
}

Chart::~Chart()
{
	delete time_axis;
	delete forward_head_axis;
	delete twisted_back_axis;
	delete hand_on_face_axis;

	delete forward_head_series;
	delete twisted_back_series;
	delete hand_on_face_series;
}

void Chart::update_forward_head_chart(const qreal time, const qint16 grade)
{
//	qreal current_time = m_time.elapsed() / 1000.0;
	forward_head_series->append(time, grade);
}

void Chart::update_slant_posture_chart(const qreal time, const qreal value)
{
	twisted_back_series->append(time, value);
}

void Chart::update_hand_on_face_chart(const qreal time, const bool is_detected)
{
	qreal value;
	if (is_detected) {
		value = HAND_DETECTED;
		//	hand_on_face_series->append(time, value);
	}
	else {
		value = HAND_NOT_DETECTED;
	}

	hand_on_face_series->append(time, value);
}

void Chart::update_chart_scroll(const qreal time)
{
//	qreal dx = (time_axis->max() - time_axis->min()) / time_axis->tickCount();

	qreal dx = plotArea().width() / time_axis->tickCount() / 4.0;

	if (time >= 25) scroll(dx, 0);
}

void Chart::handleTimeout()
{
	if (cumulative_time == 0) {
		cumulative_time++;
		return;
	}
	qreal x = cumulative_time;

	qreal y = qrand() % 100;
	twisted_back_series->append(x, y);

	y = (qrand() + 7) % 10;
	hand_on_face_series->append(x, y);

	cumulative_time++;

//	if (cumulative_time >= 25) scroll(20, 0);

//	scroll(x, 0);
//	if (m_x == 100)
//		m_timer.stop();
}