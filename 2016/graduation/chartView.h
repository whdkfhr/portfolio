#pragma once

#include "chart.h"
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE


class ChartView :
	public QChartView
{
public:
	ChartView();
	~ChartView();

	void update_forward_head_chart(const qreal time, const qint16 grade);
	void update_slant_posture_chart(const qreal time, const qreal value);
	void update_hand_on_face_chart(const qreal time, const bool is_detected);
	void update_chart_scroll(const qreal time);

protected:
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void resizeEvent(QResizeEvent *event);

private:
	Chart *m_chart;
};

