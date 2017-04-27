#include <iostream>
#include <string>
#include "utils.hpp"


using namespace std;

void initializeArgs(Args & args) {
	args.annotate = false;
	args.imagePaths = vector<string>();
	args.videoPaths = vector<string>();
	args.nImagePaths = vector<string>();
	args.nVideoPaths = vector<string>();
	args.videoPath = "";
	args.featurePath = "";
	args.workDir = "./";
	args.isLive = false;
	args.iSamplingRatio = 5;
}

void parseArgs(int argc, char** argv, Args& args) {
	if (argc <= 1) {
		printHelp();
		exit(0);
	}
	else {
		int i = 1;
		while (i < argc) {
			string arg(argv[i]);
			if (arg == ARGPATH && i+1 < argc) {
				i++;
				args.videoPath = string(argv[i]);
				i++;
			}
			else if (arg == ARGFEATURES && i + 1 < argc) {
				i++;
				args.featurePath = string(argv[i]);
				i++;
			}

			else if (arg == ARGWORKDIR && i + 1 < argc) {
				i++;
				args.workDir = string(argv[i]);
				i++;
			}
			else if (arg == ARGIMAGE) {
				i++;
				while (i < argc) {
					if (argv[i][0] != '-') {
						args.imagePaths.push_back(string(argv[i]));
					}
					else {
						break;
					}
					i++;
				}
			}
			else if (arg == ARGVIDEO) {
				i++;
				while (i < argc) {
					if (argv[i][0] != '-') {
						args.videoPaths.push_back(string(argv[i]));
					}
					else {
						break;
					}
					i++;
				}
			}
			else if (arg == ARGNVIDEO) {
				i++;
				while (i < argc) {
					if (argv[i][0] != '-') {
						args.nVideoPaths.push_back(string(argv[i]));
					}
					else {
						break;
					}
					i++;
				}
			}
			else if (arg == ARGNIMAGE) {
				i++;
				while (i < argc) {
					if (argv[i][0] != '-') {
						args.nImagePaths.push_back(string(argv[i]));
					}
					else {
						break;
					}
					i++;
				}
			}
			else if (arg == ARGANNOTATE) {
				args.annotate = true;
				i++;
			}
			else if (arg == ARGLIVE) {
				args.isLive = true;
				i++;
			}
			else {
				printError("Invalid argument: " + arg);
			}
		}
	}
}


void printHelp() {
	cout << "FeatureTrack" << endl << "Usage:" << endl << endl;
	cout << "\tFeatureTrack.exe " << ARGPATH << " <PATH> " << ARGIMAGE << " <IMAGEPATHS ...> " << ARGVIDEO << " <VIDEOPATHS ...>" << endl << endl;
	cout << ARGPATH << "\t" << "Path to .avi video file" << endl;
	cout << ARGIMAGE << "\t" << "Paths to target image files to find in video" << endl;
	cout << ARGVIDEO << "\t" << "Paths to target video of object to find in video" << endl;
	cout << ARGNIMAGE << "\t" << "Paths to background images to use as control in learning classifier" << endl;
	cout << ARGNVIDEO << "\t" << "Paths to background video to use as control in learning classifier" << endl;
	cout << ARGANNOTATE << "\t" << "Run the annotation tool to select target object on sample images" << endl;
	cout << ARGLIVE << "\t" << "Run feature tracking on live camera input" << endl;
	cout << ARGFEATURES << "\t" << "The path to existing classifier to use instead of learning from samples" << endl;
	cout << ARGSRATIO << "\t" << "Frames to skip in input video for learning classifier" << endl;
	cout << ARGWORKDIR << "\t" << "The directory in which to create intermediate files etc" << endl;
}


void printArgs(Args& args) {
	cout << "Video:\t\t" << (args.isLive ? "Live" : args.videoPath) << endl;
	cout << "Annotate:\t" << (args.annotate ? "Yes" : "No") << endl;
	cout << "Working Dir:\t" << args.workDir << endl;

	cout << "Target images:" << endl;
	for (string s : args.imagePaths) {
		cout << "\t\t" << s << endl;
	}

	cout << "Target videos:" << endl;
	for (string s : args.videoPaths) {
		cout << "\t\t" << s << endl;
	}
	cout << "Background images:" << endl;
	for (string s : args.nImagePaths) {
		cout << "\t\t" << s << endl;
	}
	cout << "Background videos:" << endl;
	for (string s : args.nVideoPaths) {
		cout << "\t\t" << s << endl;
	}
}

void printError(const string error) {
	cerr << error;
	exit(-1);
}
