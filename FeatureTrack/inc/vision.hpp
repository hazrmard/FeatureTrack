#pragma once
#include <vector>
#include <cstdlib>

#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>

#include "utils.hpp"

#ifndef VISION
#define VISION

using namespace std;
using namespace cv;

#define ANNOFILE "anno.txt"
#define ANNOMAXWINHEIGHT "1024"
#define ANNORESIZEFACTOR "4"

struct Data
{
	vector<Mat> images;
};

long numFrames(const string path);
void readTargetImages(vector<string>& paths, vector<Mat>& images);
void readTargetFrames(vector<string>& paths, vector<Mat>& images);
void sampleFramesFromVideo(vector<string>& paths, int sampleRatio, string directory);
void createSamples(Args& args);
void callTrainer();
void callAnnotator(Args& args);

#endif