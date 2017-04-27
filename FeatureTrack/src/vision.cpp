#include "vision.hpp"


using namespace std;
using namespace cv;


long numFrames(const string path) {
	VideoCapture cap(path);
	return (long) cap.get(CAP_PROP_FRAME_COUNT);
}


void readTargetImages(vector<string>& paths, vector<Mat>& images) {
	for (string path : paths) {
		Mat img = imread(path, IMREAD_GRAYSCALE);
		if (img.data) {
			images.push_back(img);
		}
		else {
			printError("Could not open image: " + path);
		}
	}
}


void readTargetFrames(vector<string>& paths, vector<Mat>& images) {
	
}

void sampleFramesFromVideo(vector<string>& paths, int sampleRatio, string directory) {
}

void createSamples(Args & args) {

}


void callTrainer() {
	system("opencv_traincascade.exe");
}


void callAnnotator(Args& args) {
	for (string imgDir : args.imagePaths) {
		string command = "opencv_annotation.exe"
			" --annotations=" + args.workDir + "/" ANNOFILE +
			" --images=" + imgDir +
			" --maxWindowHeight=" ANNOMAXWINHEIGHT +
			" --resizeFactor=" ANNORESIZEFACTOR;
		system(command.c_str());
	}
	
}
