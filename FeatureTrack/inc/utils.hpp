#pragma once
#include <vector>

#ifndef UTILS
#define UTILS

using namespace std;

#define ARGPATH		"-p"
#define ARGIMAGE	"-i"
#define ARGVIDEO	"-v"
#define ARGNIMAGE	"-ni"
#define ARGNVIDEO	"-nv"
#define ARGANNOTATE	"-a"
#define ARGLIVE		"-l"
#define ARGFEATURES	"-f"
#define ARGSRATIO	"-r"
#define ARGWORKDIR	"-w"

struct Args
{
	bool isLive;
	bool annotate;
	int iSamplingRatio;
	string videoPath;
	string featurePath;
	string workDir;
	vector<string> imagePaths;
	vector<string> videoPaths;
	vector<string> nImagePaths;
	vector<string> nVideoPaths;
};

void initializeArgs(Args& args);
void parseArgs(int argc, char** argv, Args& args);
void printHelp();
void printArgs(Args& args);
void printError(const string error);

#endif // !UTILS
