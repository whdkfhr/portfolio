#include "ChartView.h"




// public

ChartView::ChartView()
{
	m_chart = new Chart;


	//	chart->setTitle("Dynamic spline chart");
	m_chart->setContentsMargins(0, 0, 0, 0);
	m_chart->setMargins(QMargins(0, 0, 0, 0));

	// set legends
	//	chart->legend()->hide();
	//	chart->legend()->setWindowTitle("dfa");
	m_chart->legend()->setAlignment(Qt::AlignTop);
	m_chart->legend()->setFont(QFont("noto sans"));
	//	chart->legend()->resize(QSizeF(1, 1));
	//	chart->legend()->adjustSize();
	//	chart->legend()->setLabelColor(FORWARD_HEAD_LINE_COLOR);

	//	chart->legend()->markers().at(0);

	//	chart->legend()->setBackgroundVisible(true);
	//chart->legend()->setBrush(QBrush(QColor(128, 128, 128, 128)));
	//chart->legend()->setPen(QPen(QColor(192, 192, 192, 192)));


	//	chart->setBackgroundRoundness(0);
	m_chart->setAnimationOptions(QChart::AllAnimations);
	//	chart->setAnimationOptions(QChart::SeriesAnimations);
	//	chart->setBackgroundVisible(false);
	//	chart->setBackgroundPen(QPen(FORWARD_HEAD_LINE_COLOR));
	m_chart->setBackgroundBrush(QBrush("#ffffff"));
	//	chart->
	//	chart->
	//	 chart->setAutoFillBackground(true);

	//	chartView->layout()->setContentsMargins(0, 0, 0, 0);


	//	chartView->autoFillBackground();

	//	chartView->setStyleSheet("QChartView { Background-color: #ff00FF; border-radius: 12.5px; border-style: solid;	border-color: #bbbbbb; border - width: 1px;}");
	//	chartView->setForegroundRole(QPalette::ColorRole::Background);
	//	chartView->setStyleSheet("QChartView")

	setRubberBand(QChartView::HorizontalRubberBand);
	//	chartView->setForegroundBrush(QBrush("#00ffff"));
	setBackgroundBrush(QBrush("#ffffff"));


	//	echo(QString::number(chartView->foregroundRole()));


	setChart(m_chart);

	setContentsMargins(QMargins());

	//	chartView->setContentsMargins(100, 0, 100, 0);

	setEnabled(true);	// working

	//	chartView->margin

	
}


ChartView::~ChartView()
{
	delete m_chart;
}

void ChartView::update_forward_head_chart(const qreal time, const qint16 grade)
{
	m_chart->update_forward_head_chart(time, grade);
}

void ChartView::update_slant_posture_chart(const qreal time, const qreal value)
{
	m_chart->update_slant_posture_chart(time, value);
}

void ChartView::update_hand_on_face_chart(const qreal time, const bool is_detected)
{
	m_chart->update_hand_on_face_chart(time, is_detected);
}

void ChartView::update_chart_scroll(const qreal time)
{
	m_chart->update_chart_scroll(time);
}



// protected

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
	QChartView::mouseMoveEvent(event);
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
	QChartView::mousePressEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
	QChartView::mouseReleaseEvent(event);
//	ChartView* d_ptr = this;
//	rubbet
//	// customized mouseReleaseEvent
//#ifndef QT_NO_RUBBERBAND
//	if (d_ptr->rubberBand() && d_ptr->m_rubberBand->isVisible()) {
//		if (event->button() == Qt::LeftButton) {
//			d_ptr->m_rubberBand->hide();
//			QRectF rect = d_ptr->m_rubberBand->geometry();
//			// Since plotArea uses QRectF and rubberband uses QRect, we can't just blindly use
//			// rubberband's dimensions for vertical and horizontal rubberbands, where one
//			// dimension must match the corresponding plotArea dimension exactly.
//			if (d_ptr->m_rubberBandFlags == VerticalRubberBand) {
//				rect.setX(d_ptr->m_chart->plotArea().x());
//				rect.setWidth(d_ptr->m_chart->plotArea().width());
//			}
//			else if (d_ptr->m_rubberBandFlags == HorizontalRubberBand) {
//				rect.setY(d_ptr->m_chart->plotArea().y());
//				rect.setHeight(d_ptr->m_chart->plotArea().height());
//			}
//			d_ptr->m_chart->zoomIn(rect);
//			event->accept();
//		}
//
//	}
//	else if (d_ptr->m_rubberBand && event->button() == Qt::RightButton) {
//		// If vertical or horizontal rubberband mode, restrict zoom out to specified axis.
//		// Since there is no suitable API for that, use zoomIn with rect bigger than the
//		// plot area.
//		if (d_ptr->m_rubberBandFlags == VerticalRubberBand
//			|| d_ptr->m_rubberBandFlags == HorizontalRubberBand) {
//			QRectF rect = d_ptr->m_chart->plotArea();
//			if (d_ptr->m_rubberBandFlags == VerticalRubberBand) {
//				qreal adjustment = rect.height() / 2;
//				rect.adjust(0, -adjustment, 0, adjustment);
//			}
//			else if (d_ptr->m_rubberBandFlags == HorizontalRubberBand) {
//				qreal adjustment = rect.width() / 2;
//				rect.adjust(-adjustment, 0, adjustment, 0);
//			}
//			d_ptr->m_chart->zoomIn(rect);
//		}
//		else {
//			d_ptr->m_chart->zoomOut();
//		}
//		event->accept();
//	}
//	else {
//#endif
//		QGraphicsView::mouseReleaseEvent(event);
//#ifndef QT_NO_RUBBERBAND
//	}
//#endif
//
}

void ChartView::resizeEvent(QResizeEvent *event)
{
//	QChartView::resizeEvent(event);

	// Fit the chart into view if it has been rotated
	qreal sinA = qAbs(this->transform().m21());
	qreal cosA = qAbs(this->transform().m11());
	QSize chartSize = this->size();

	if (sinA == 1.0) {
		chartSize.setHeight(this->size().width());
		chartSize.setWidth(this->size().height());
	}
	else if (sinA != 0.0) {
		// Non-90 degree rotation, find largest square chart that can fit into the view.
		qreal minDimension = qMin(this->size().width(), this->size().height());
		qreal h = (minDimension - (minDimension / ((sinA / cosA) + 1.0))) / sinA;
		chartSize.setHeight(h);
		chartSize.setWidth(h);
	}

	m_chart->resize(chartSize);
	this->setMinimumSize(m_chart->minimumSize().toSize());
	this->setSceneRect(m_chart->geometry());
}