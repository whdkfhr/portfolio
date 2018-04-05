#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;

	//try {
	//	QFile qss("qss/test.qss");
	//	if (qss.open(QFile::ReadOnly)) {
	//		QString StyleSheet = QLatin1String(qss.readAll());
	//		a.setStyleSheet(StyleSheet);
	//		qss.close();
	//	}
	//}
	//catch( Exception e) {
	////	exit(1);
	//}
	
	

	//Chart *chart = new Chart;
	//chart->setTitle("Dynamic spline chart");
	//chart->legend()->hide();
	//chart->setAnimationOptions(QChart::AllAnimations);
	//QChartView chartView(chart);
	//w.setCentralWidget(&chartView);

	w.show();

	/*

	BOOL bLive = TRUE;
	KinectCamData *pCVMgr = new KinectCamData;
	KinectManager *pKinectMgr = new KinectManager;
	pKinectMgr->setKinectCamData(pCVMgr);

	while (bLive)
	{
		pKinectMgr->Update_Color();
		pKinectMgr->Update_IR();
		pKinectMgr->Update_Depth();
		pKinectMgr->FPS_Render();
		bLive = pCVMgr->Render();
	}

	delete pKinectMgr;
	delete pCVMgr;

	*/

	return a.exec();
}




/*

#include "stdio.h"
#include "define.h"
#include "KinectManager.h"

void main()
{
	BOOL bLive = TRUE;
	KinectCamData *pCVMgr = new KinectCamData;
	KinectManager *pKinectMgr = new KinectManager;
	pKinectMgr->setKinectCamData(pCVMgr);

	while(bLive)
	{
		pKinectMgr->Update_Color();
		pKinectMgr->Update_IR();
		pKinectMgr->Update_Depth();
		pKinectMgr->FPS_Render();
		bLive = pCVMgr->Render();
	}

	delete pKinectMgr;
	delete pCVMgr;

	return;
}



*/