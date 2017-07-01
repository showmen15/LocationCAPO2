#include "ArucoLocation.h"

//formatowanie kodu
// CTRL+K CTRL+F 

//http://docs.opencv.org/3.0-beta/modules/videoio/doc/reading_and_writing_video.html


//string getTimeAndFormat()
//{
//	  // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
//
//	time_t     now = time(0);
//    struct tm  tstruct;
//    char       buf[80];
//    tstruct = *localtime(&now);
//  
//    strftime(buf, sizeof(buf), "Robot_%Y_%m_%d_%X", &tstruct);
//
//    return buf;
//}

int main22()
{
	//string ss = getTimeAndFormat();
	//ss += "aaa";

	// current date/time based on current system
	//time_t now = time(0);
	//
	//// convert now to string form
	//char* dt = ctime(&now);

	//cout << "The local date and time is: " << dt << endl;

	//// convert now to tm struct for UTC
	//tm *gmtm = gmtime(&now);
	//dt = asctime(gmtm);
	//cout << "The UTC date and time is:"<< dt << endl;


	// current date/time based on current system
	//time_t now = time(0);

	//cout << "Number of sec since January 1,1970:" << now << endl;

	//tm *ltm = localtime(&now);

	//// print various components of tm structure.
	//cout << "Year" << 1900 + ltm->tm_year<<endl;
	//cout << "Month: "<< 1 + ltm->tm_mon<< endl;
	//cout << "Day: "<<  ltm->tm_mday << endl;
	//cout << "Time: "<< 1 + ltm->tm_hour << ":";
	//cout << 1 + ltm->tm_min << ":";
	//cout << 1 + ltm->tm_sec << endl;


	//while(true)
	//{
	//	int key = waitKey(5);

	//	if(key > -1)
	//	{
	//		key += 1;
	//	}

	//}
	return 0;
}

bool temp;

void run()
{
	while(temp)
	{

		Sleep(1000);
	}
}


int main22(int argc, char **argv)
{
	temp = true;
	thread thr = thread(run);
	temp = false;

	thr.join();
	return 0;
}


bool isParam(string line)
{
    char* p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}



//wykrywanie obiektu po kolorze
 int main44( int argc, char** argv )
 {
    VideoCapture cap(0); //capture the video from web cam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }

    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

 int iLowH = 0;
 int iHighH = 179;

 int iLowS = 0; 
 int iHighS = 255;

 int iLowV = 0;
 int iHighV = 255;

 //Create trackbars in "Control" window
 cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
 cvCreateTrackbar("HighH", "Control", &iHighH, 179);

 cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
 cvCreateTrackbar("HighS", "Control", &iHighS, 255);

 cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
 cvCreateTrackbar("HighV", "Control", &iHighV, 255);

    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

  Mat imgHSV;

  cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
 
  Mat imgThresholded;

  inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
      
  //morphological opening (remove small objects from the foreground)
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

  //morphological closing (fill small holes in the foreground)
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

  imshow("Thresholded Image", imgThresholded); //show the thresholded image
  imshow("Original", imgOriginal); //show the original image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }
    }

   return 0;

}
//#include <string>
//#include <windows.h>
//#include <iostream>

 /*std::string getexepath()
 {
	 char result[MAX_PATH];
	 return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
 }*/

 //int main(int argc, char **argv)
 //{
	// char* path;
	// _get_pgmptr(&path);
	// string programStartUp = path;


	// printf("Hallo");
	// cout << programStartUp << endl; // Example output: C:/Projects/Hello/World.exe
	// printf("End");
 //}

int main(int argc, char **argv)
{
	try
	{
		char* path;
		_get_pgmptr(&path);
		string programStartUp = path;
		string source = argv[1];

		cout << programStartUp << endl;
		cout << source << endl;
 
		VideoCapture inputVideo;

		if(isParam(source))
			inputVideo = VideoCapture(stoi(source.c_str())); // open the default camera
		else
			inputVideo = VideoCapture(source); // open file

		if(!inputVideo.isOpened())  // check if we succeeded    
			return -1;

		//settings
		inputVideo.set(CV_CAP_PROP_FRAME_WIDTH,1920);
		inputVideo.set(CV_CAP_PROP_FRAME_HEIGHT,1080);

		bool working = true;
		int key;
		string sCameraParams =  ".\\out_camera_params.yml";

		int CodecType = CV_FOURCC('M', 'J', 'P', 'G'); //CV_FOURCC('H', '2', '6', '3'); // Get Codec Type- Int form
		double Fps = 15; //25.0
		Size InputSize = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT)); // Acquire input size

		ArucoLocation location(sCameraParams,InputSize); //okiekt lokalizacji
		VideoRecorder rec(CodecType,Fps,InputSize,programStartUp);

		Mat frame;
		namedWindow("frame",cv::WINDOW_NORMAL);
		//cv::namedWindow("Output", cv::WINDOW_AUTOSIZE);
		namedWindow("rot", cv::WINDOW_NORMAL);


		int zaczytane = 20;

		
		bool init = false;

		for(;working;)
		{
			inputVideo >> frame; // get a new frame from camera

			rec.Record(frame);
			location.Update(frame);	
			/*

			double angle = -90;

			// get rotation matrix for rotating the image around its center
			cv::Point2f center(frame.cols / 2.0, frame.rows / 2.0);
			cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
			// determine bounding rectangle
			cv::Rect bbox = cv::RotatedRect(center, frame.size(), angle).boundingRect();
			// adjust transformation matrix
			rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
			rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

			cv::Mat dst;
			cv::warpAffine(frame, dst, rot, bbox.size());
			imshow("rot", dst);
			*/
			imshow("frame", frame);


			key = waitKey(42);
			if(key >= 0)
			{
			switch (key)
				{
					//S|s -> start recording
				case 83:
				case 115:
					{
						rec.StartRecord();
						break;
					}

					//E|e -> end recording
				case 69:
				case 101:
					{
						rec.StopRecord();
						break;
					}


					//Esc -> end progroam
				case 27:
					{
						working = false;
						rec.StopRecord();
						location.Stop();
						exit(1);
						break;
					}

					// P|p  -> print Xp, Yp
				case 80:
				case 112:
					{
						location.GetXpYp();
						break;
					}

				//strzalka up | num 8;
				case 56:
				case 2490368:
					{
						location.AddYp(-1);
						break;
					}

				//strzalka down | num 2
				case 50:
				case 2621440:
					{
						location.AddYp(1);
						break;
					}

				//strzalka left | num 4
				case 52:
				case 2424832:
					{
						location.AddXp(-1);
						break;
					}

				//strzalka right | num 6
				case 54: 
				case 2555904:
					{
						location.AddXp(1);
						break;
					}

					//F2 | q
				case 113: 
				case 7405568: 
					{

					cout << inputVideo.get(CV_CAP_PROP_FRAME_WIDTH) << endl;
					cout << inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
					cout << inputVideo.get(CV_CAP_PROP_FPS) << endl;
					cout << inputVideo.get(CV_CAP_PROP_FORMAT) << endl;

					cout << inputVideo.get(CV_CAP_PROP_SETTINGS) << endl;

					inputVideo.set(CV_CAP_PROP_SETTINGS, 1);
					break;
					}
				default:
					break;
				}
			}
		}
	}
	catch(Exception ex)
	{
		cout << ex.what();
	}


	return 0;
}




/*
//Grayscale matrix
cv::Mat grayscaleMat (frame.size(), CV_8U);

//Convert BGR to Gray
cv::cvtColor( frame, grayscaleMat, CV_BGR2GRAY );

//Binary image
cv::Mat binaryMat(grayscaleMat.size(), grayscaleMat.type());

//Apply thresholding
cv::threshold(grayscaleMat, binaryMat, 100, 255, cv::THRESH_BINARY);

//Show the results

cv::imshow("Output", binaryMat);
*/