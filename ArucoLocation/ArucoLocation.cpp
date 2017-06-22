
#include "ArucoLocation.h"


ArucoLocation::ArucoLocation(string cameraParams, Size inputImageSize)
{
	MarkerSize = 1000; //wielkosc markera px
	MarkerSizeM = 0.2645833333; //wielkosc markera w m
	//CamParam.readFromXMLFile(cameraParams); // read camera parameters
	InputImageSize = inputImageSize;

	dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_ARUCO_ORIGINAL);

	string sIP;
	unsigned short port = 53000;

	for (int i = 0; i < ROBOTS_COUNT; i++)
	{
		RobotLocation[i].set_robotid(i);

		sIP = "192.168.2.20" + to_string(i); //"192.168.2.201"; //

		RobotClient[i] = new UdpClient(sIP.c_str(), port);
	}

	working = true;

	thr = thread(&ArucoLocation::run, this);

	Xp = 0;
	Yp = inputImageSize.height;
}

ArucoLocation::~ArucoLocation()
{

}

void ArucoLocation::run()
{
	Aruco::ArucoLocation currentLocation;
	UdpClient* curentRobotClient;

	string output;
	cv::namedWindow("in", 1);
	//	cv::namedWindow("thes", 1);

	while (working)
	{
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck);

		if (working)
		{
			//CamParam.resize(InImage.size());  // resizes the parameters to fit the size of the input image
			cv::aruco::detectMarkers(InImage, dictionary, markerCorners, markerIds); //MDetector.detect(InImage, Markers, CamParam, MarkerSize);  // Ok, let's detect

			for (unsigned int i = 0; i < markerCorners.size(); i++) // for each marker, draw info and its boundaries in the image
			{
				if (markerIds[i] > ROBOTS_COUNT)
					continue;

				currentLocation = RobotLocation[markerIds[i]];
				curentRobotClient = RobotClient[markerIds[i]];

				set_location2(markerCorners[i], markerIds[i], &currentLocation);

				currentLocation.SerializePartialToString(&output);
				curentRobotClient->Send(output);

				directionVector(markerCorners[i], InImage, currentLocation.alfa());
			}

			cv::aruco::drawDetectedMarkers(InImage, markerCorners, markerIds);

			draw2dAxis(InImage, Xp, Yp); //narysuj osie Ox Oy

			cv::imshow("in", InImage); // show input with augmented information       
			//cv::imshow("thes", MDetector.getThresholdedImage());  // show also the internal image resulting from the threshold operation	  
			cv::waitKey(1); // wait for key to be pressed
		}
	}
}

void ArucoLocation::Update(Mat frame)
{
	std::unique_lock<std::mutex> lck(mtx, std::defer_lock);

	if (lck.try_lock())
	{
		frame.copyTo(InImage);
		cv.notify_one();
	}
}

void ArucoLocation::Stop()
{
	working = false;
	std::unique_lock<std::mutex> lck(mtx, std::defer_lock);
	cv.notify_one();
	thr.join();
}

void ArucoLocation::set_location2(vector< Point2f > marker, int id, Aruco::ArucoLocation* location)
{
	double x0 = marker[2].x;
	double y0 = marker[2].y;

	double x1 = marker[1].x;
	double y1 = marker[1].y;

	double dist = distance(x0, y0, x1, y1);

	double Xl = InputImageSize.height - ((marker[0].y + marker[2].y) / 2) - (InputImageSize.height - Yp); //InputImageSize.height - marker.getCenter().y - (InputImageSize.height -Yp);
	double Yl = ((marker[0].x + marker[2].x) / 2) - Xp; // marker.getCenter().x - Xp;

	double Xlm = (MarkerSizeM * Xl) / dist;
	double Ylm = (MarkerSizeM * Yl) / dist;

	double Vxl = x1 - x0;
	double Vyl = y1 - y0;

	double Vl = sqrt(pow(Vxl, 2) + pow(Vyl, 2));

	//double alfa = Vxl / Vl;

	double alfa = atan2(Vyl, Vxl);

	location->set_robotid(id); //robotID
	location->set_x(Xlm); //pozyajca w metrach
	location->set_y(Ylm); //pozyajca w metrach
	location->set_alfa(alfa); //kat w radianach
	location->set_timestamp(999); //timestamp

	cout << "ID: " << id << " X: " << Xlm << " Y: " << Ylm << " alfa: " << alfa << endl;

}

double ArucoLocation::distance(double x0, double y0, double x1, double y1)
{
	return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
}

void ArucoLocation::AddXp(double in)
{
	if ((Xp + in) >= 0)
		Xp += in;
}

void ArucoLocation::AddYp(double in)
{
	if ((Yp + in) >= 0)
		Yp += in;
}

void ArucoLocation::GetXpYp()
{
	cout << "Xp: " << Xp << " Yp: " << Yp << endl;
}

void ArucoLocation::draw2dAxis(Mat &Image, int  Xp, int  Yp)
{
	int lineWidth = 2;
	Point2f axis(Xp, Yp); //pocztek ukladu
	Point2f axisX(Xp, Yp - 50); //os X;
	Point2f axisY(Xp + 50, Yp); //os Y;

								//narysowanie osi OX
	cv::line(Image, axis, axisX, Scalar(0, 255, 0, 255), lineWidth, CV_AA);

	//narysowanie osi OY
	cv::line(Image, axis, axisY, Scalar(0, 0, 255, 255), lineWidth, CV_AA);

}
void ArucoLocation::directionVector(vector< Point2f > marker, Mat &in, double alfa)
{
	int lineWidth = 2;
	float arrowLength = 10.0;
	Point2f arrowEnd;
	Point2f center(((marker[0].x + marker[2].x) / 2), ((marker[0].y + marker[2].y) / 2));

	arrowEnd.x = center.x + (arrowLength * cos(alfa));
	arrowEnd.y = center.y + (arrowLength * sin(alfa));

	//narysuj vector kirunku
	cv::line(in, center, arrowEnd, Scalar(0, 255, 0, 255), lineWidth, CV_AA);
}


//void ArucoLocation::Run()
//{
//	working = true;
//	int index = 0;
//	string output;
//
//	while(working)
//	{	
//		for(int i = 0; i < ROBOTS_COUNT;i++)
//		{
//			RobotLocation[i].set_alfa(423423);
//
//			RobotLocation[i].SerializePartialToString(&output);
//			RobotClient[i]->Send(output);
//
//			Aruco::ArucoLocation temp;
//
//			temp.ParseFromString(output);
//
//			
//		}
//
//
//
//	if(index == 3)
//		working = false;
//
//	index++;
//
//
//	}
//}

//void ArucoLocation::set_location(Marker marker, Aruco::ArucoLocation* location)
//{
//	double x0 = marker[0].x;
//	double y0 = marker[0].y;
//
//	double x1 = marker[1].x;
//	double y1 = marker[1].y;
//
//	double dist = distance(x0, y0, x1, y1);
//
//	double Xl = marker.getCenter().x - Xp;
//	double Yl = marker.getCenter().y - Yp;
//
//	double Xlm = (MarkerSizeM * Xl) / dist;
//	double Ylm = (MarkerSizeM * Yl) / dist;
//
//	double Vxl = x1 - x0;
//	double Vyl = y1 - y0;
//
//	double Vl = sqrt(pow(Vxl,2) + pow(Vyl,2));
//
//	double alfa = Vxl / Vl;
//
//	location->set_robotid(marker.id); //robotID
//	location->set_x(Xlm); //pozyajca w metrach
//	location->set_y(Ylm); //pozyajca w metrach
//	location->set_alfa(alfa); //kat w radianach
//	location->set_timestamp(999); //timestamp
//
//	cout << "ID: " << marker.id << " X: "  << Xlm << " Y: " << Ylm << " alfa: " << alfa << endl;
//}