#include "vision.hpp"
#include <iostream>


using namespace std;
using namespace cv;


long numFrames(const string path) {
	VideoCapture cap(path);
	return (long) cap.get(CAP_PROP_FRAME_COUNT);
}


//vector<string> convertImageToGray(vector<string>& paths, string directory, string prefix, bool retFilePaths) {
//	int i = 0;
//	vector<string> retPaths;
//	string dirPath = directory + PATHSEP + prefix + "img";
//	makeDir(dirPath);
//	if (!retFilePaths) {
//		retPaths.push_back(dirPath);
//	}
//	for (string path : paths) {
//		Mat img = imread(path, IMREAD_GRAYSCALE);
//		if (img.data) {
//			Mat gray;
//			cvtColor(img, gray, COLOR_BGR2GRAY);
//			imwrite(dirPath + PATHSEP + to_string(i) + ".jpg", gray);
//			if (retFilePaths) {
//				retPaths.push_back(dirPath + PATHSEP + to_string(i) + ".jpg");
//			}
//		}
//		else {
//			printError("Could not open image: " + path);
//		}
//		i++;
//	}
//	return retPaths;
//}


vector<string> sampleFramesFromVideo(vector<string>& paths, int sampleRatio, string directory, string prefix, bool retFilePaths) {
	int i = 0;
	int frameNum = 0;
	string dirPath;
	string imPath;
	vector<string> retPaths;
	Mat frame;		// original frame
	Mat gray;		// rectified frame
	for (string path : paths) {
		VideoCapture video(path);
		if (!video.isOpened()) {
			printError("Could not open video file: " + path);
		}
		else {
			dirPath = directory + PATHSEP + prefix + "v_" + to_string(i);
			makeDir(dirPath);
			if (!retFilePaths) {
				retPaths.push_back(dirPath);
			}
			while (video.read(frame)) {
				if (frameNum % sampleRatio == 0) {
					rectify(frame, gray);
					imPath = dirPath + PATHSEP "i_" + to_string(frameNum) + ".jpg";
					imwrite(imPath, gray);
					if (retFilePaths) {
						retPaths.push_back(imPath);
					}
				}
				frameNum++;
			}
			i++;
		}

	}
	return retPaths;
}


void rectify(Mat & frame, Mat & rFrame) {
	Mat intermediate;
	cvtColor(frame, intermediate, COLOR_BGR2GRAY);
	equalizeHist(intermediate, rFrame);
}


void createSamples(Args & args) {
	string command = EXESAMPLES
		" -vec " + args.workDir + PATHSEP VECFILE +
		(args.infoPath.empty() ? " -img " + args.imagePaths[0] : " -info " + args.infoPath) +
		" -bg " + args.nInfoPath +
		(args.infoPath.empty() ? " -num " + to_string(args.numPSamples) : "") +
		" -h " + to_string(args.sampleHeight) +
		" -w " + to_string(args.sampleWidth) +
		" -bgthresh 0";
	system(command.c_str());
}


void callTrainer(Args & args) {
	string command = EXETRAIN
		" -data " + args.workDir +
		" -vec " + (args.vecPath.empty() ? args.workDir + PATHSEP VECFILE : args.vecPath) +
		" -bg " + args.nInfoPath +
		" -numPos " + to_string(args.numPSamples) +
		" -numNeg " + to_string(args.numNSamples) +
		" -w " + to_string(args.sampleWidth) +
		" -h " + to_string(args.sampleHeight);
	cout << endl << command << endl;
	system(command.c_str());
}


void callAnnotator(Args& args) {
	ofstream annoFile(ANNOFILE, ofstream::out);
	string line;

	for (string imgDir : args.imagePaths) {
		string command = EXEANNOTATE
			" --annotations=" + args.workDir + PATHSEP "temp" ANNOFILE +
			" --images=" + imgDir +
			" --maxWindowHeight=" ANNOMAXWINHEIGHT +
			" --resizeFactor=" ANNORESIZEFACTOR;
		system(command.c_str());

		ifstream tempAnnoFile(args.workDir + PATHSEP "temp" ANNOFILE, ifstream::in);
		while (getline(tempAnnoFile, line)) {
			annoFile << line << endl;
		}
		tempAnnoFile.close();
	}

	annoFile.close();	
}


void trackFeatures(Args& args) {
	CascadeClassifier detector(args.featurePath);
	if (detector.empty()) {
		printError("Could not load classifier: " + args.featurePath);
	}
	
	VideoCapture cap;
	if (args.isLive) {
		cap.open((args.videoPath.empty()) ? 0 : stoi(args.videoPath));
	}
	else {
		cap.open(args.videoPath);
	}
	if (!cap.isOpened()) {
		printError("Could not open video stream.");
	}

	Mat oFrame, frame;
	vector<Rect> detections;
	long int frameNum = 0;
	double timestamp;
	while (cap.read(oFrame)) {
		timestamp = cap.get(CV_CAP_PROP_POS_MSEC);
		if (frameNum % args.iSamplingRatio == 0) {
			rectify(oFrame, frame);
			detector.detectMultiScale(frame, detections);
			for (Rect r : detections) {
				cout << timestamp << "\t" << r.x << "\t" << r.y << "\t" << r.width << "\t" << r.height << endl;
			}
			if (args.interactive) {
				namedWindow("FeatureTrack");
				for (int i = 0; i < detections.size(); i++) {
					rectangle(oFrame, detections[i], Scalar(0, 255, 0), 3);
				}
				imshow("FeatureTrack", oFrame);
				if (waitKey(30) == 27) {
					break;
				}
			}
		}
		frameNum++; 
	}
}