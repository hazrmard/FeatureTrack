#pragma once
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "utils.hpp"

#ifndef VISION
#define VISION

using namespace std;
using namespace cv;

#ifdef _WIN32
#define EXESAMPLES "opencv_createsamples.exe"
#define EXEANNOTATE "opencv_annotation.exe"
#define EXETRAIN "opencv_traincascade.exe"
#else
#define EXESAMPLES "opencv_createsamples"
#define EXEANNOTATE "opencv_annotation"
#define EXETRAIN "opencv_traincascade"
#endif

// gets number of frames from a video
long numFrames(const string path);

// Converts image files into grayscale files and moves them to a particular directory.
// Returns either file paths, or directory path.
//vector<string> convertImageToGray(vector<string>& paths, string directory, string prefix, bool retFilePaths);

// Converts sampled frames from a vector of video paths into gray scale image directories.
// Either returns vector of individual image paths, or a vector of image directories.
vector<string> sampleFramesFromVideo(vector<string>& paths, int sampleRatio, string directory, string prefix, bool retFilePaths);

// Runs image/frame through some correctional transformations. Does NOT change image dimension.
void rectify(Mat& frame, Mat& rFrame);

// Calls the opencv_annotation[.exe] tool with sensible parameters. It helps mark
// regions in positive sample video where the object is present.
void callAnnotator(Args& args);

// Calls the opencv_createsamples[.exe] utility with sensible parameters.
void createSamples(Args& args);

// Calls the opencv_traincascade[.exe] utility with sensible parameters. Final step in
// training a classifier for the provided object.
void callTrainer(Args& args);

// Begin feature tracking based on learned/provided classifier
void trackFeatures(Args& args);

#endif