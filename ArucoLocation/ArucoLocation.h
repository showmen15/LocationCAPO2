#ifndef ARUCOLOCATION_H_
#define ARUCOLOCATION_H_

#include <iostream>
#include "ArucoLocation.pb.h" // protobuf //https://www.youtube.com/watch?v=x-u-hEFhDDo
#include "UdpClientLinux.h"  //http://www.binarytides.com/udp-socket-programming-in-winsock/
#include "VideoRecorder.h"


#include <math.h>

#include "opencv2/opencv.hpp"
#include <thread>         // std::thread
#include <mutex>		  //sekcja krtyczyna
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include "opencv2/opencv.hpp"
#include "opencv2/video.hpp"

#include <sstream>
#include <string>

#include <math.h>
#include <time.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <opencv2\aruco.hpp>
#include <opencv2\aruco\charuco.hpp>
#include <opencv2\aruco\dictionary.hpp>



#define ROBOTS_COUNT 10


using namespace std;
using namespace cv;
using namespace aruco;

class  ArucoLocation
{
private:
	Aruco::ArucoLocation RobotLocation[ROBOTS_COUNT];
	UdpClient *RobotClient[ROBOTS_COUNT];
	double PI;

	void run();
	bool working;

	thread thr;

	condition_variable cv;
	mutex mtx;           // mutex for critical section

	// CameraParameters CamParam;
	//MarkerDetector MDetector;
	vector< vector< Point2f >> markerCorners;
	vector< int > markerIds;

	cv::Ptr<cv::aruco::Dictionary> dictionary;

	float MarkerSize;
	float MarkerSizeM;

	Mat InImage; // read the input image

	//double get_x(Marker marker);
	//double get_y(Marker marker);
	//double get_alfa(Marker marker);

	//void set_location(Marker marker, Aruco::ArucoLocation* location);
	void set_location2(vector< Point2f > marker, int id, Aruco::ArucoLocation* location);
	double  distance(double x0,double y0,double x1,double y1);

	int Xp; //poczatek ukladu wspolzednych Xp
	int Yp; //poczatek ukladu wspolzednych Yp
	Size InputImageSize;

	void draw2dAxis(Mat &Image, int  Xp, int  Yp);
	void directionVector(vector< Point2f > marker, Mat &in, double alfa);

public:
	ArucoLocation(string cameraParams,Size inputImageSize);
	~ArucoLocation();
	void Run();
	void Stop();
	void Update(Mat frame);

	void AddXp(double in);
	void AddYp(double in);

	void GetXpYp();
};





#endif /* ARUCOLOCATION_H_ */