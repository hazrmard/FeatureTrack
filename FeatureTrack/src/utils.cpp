#include <iostream>
#include <string>
#include "utils.hpp"


using namespace std;

void initializeArgs(Args & args) {
	args.annotate = true;
	args.interactive = false;
	args.imagePaths = vector<string>();
	args.videoPaths = vector<string>();
	args.nImagePaths = vector<string>();
	args.nVideoPaths = vector<string>();
	args.videoPath = "";
	args.featurePath = "";
	args.vecPath = "";
	args.infoPath = "";
	args.nInfoPath = "";
	args.workDir = "." PATHSEP;
	args.isLive = false;
	args.iSamplingRatio = 10;
	args.numPSamples = 0;
	args.sampleHeight = 32;
	args.sampleWidth = 32;
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
			else if (arg == ARGVECPATH && i + 1 < argc) {
				i++;
				args.vecPath = string(argv[i]);
				i++;
			}
			else if (arg == ARGINFO && i + 1 < argc) {
				i++;
				args.infoPath = string(argv[i]);
				i++;
			}
			else if (arg == ARGNINFO && i + 1 < argc) {
				i++;
				args.nInfoPath = string(argv[i]);
				i++;
			}
			else if (arg == ARGWORKDIR && i + 1 < argc) {
				i++;
				args.workDir = string(argv[i]);
				i++;
			}
			else if (arg == ARGSRATIO && i + 1 < argc) {
				i++;
				args.iSamplingRatio = stoi(argv[i]);
				i++;
			}
			else if (arg == ARGNSAMPLES && i + 1 < argc) {
				i++;
				args.numPSamples = stoi(argv[i]);
				i++;
			}
			else if (arg == ARGSWIDTH && i + 1 < argc) {
				i++;
				args.sampleWidth = stoi(argv[i]);
				i++;
			}
			else if (arg == ARGSHEIGHT && i + 1 < argc) {
				i++;
				args.sampleHeight = stoi(argv[i]);
				i++;
			}
			/*else if (arg == ARGIMAGE) {
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
			}*/
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
			/*else if (arg == ARGNIMAGE) {
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
			}*/
			/*else if (arg == ARGANNOTATE) {
				args.annotate = true;
				i++;
			}*/
			else if (arg == ARGLIVE) {
				args.isLive = true;
				i++;
			}
			else if (arg == ARGINTERACT) {
				args.interactive = true;
				i++;
			}
			else {
				printError("Invalid argument: " + arg);
			}
		}
	}
}


void printHelp() {
	cout << "FeatureTrack" << endl;
	cout << "FeatureTrack learns to detect objects from sample videos" << endl;
	cout << "and runs detection on video streams." << endl << endl;
	cout << "The process happens in 4 stages:" << endl;
	cout << "\t1a. Frames from positive videos are sampled to generate annotated description files," << endl;
	cout << "\t1b. Frames from negative videos are sampled to generate background desscription files." << endl;
	cout << "\t2.  The annotation and background files are used to create a binary file (.vec)" << endl;
	cout << "\t3.  The (.vec) file along with background description file train the classifner (.xml)" << endl;
	cout << "\t4.  The classifier is used with the provided video stream to detect objects." << endl;
	cout << "This application can pick up the process from any of the above stages." << endl << endl;

	cout << "Usage:" << endl;
	cout << "\tFeatureTrack.exe " ARGPATH " <PATH> " ARGVIDEO " <OBJECT VIDEOS...> " ARGNVIDEO " <BACKGROUND VIDEOS...> " ARGWORKDIR " <WORKDIR>" << endl;
	cout << "\t" ARGSHEIGHT " <HEIGHT> " ARGSWIDTH " <WIDTH> " ARGSRATIO " <SAMPLINGRATIO> [" ARGLIVE " " ARGINTERACT "]" << endl << endl;

	cout << "\tFeatureTrack.exe " ARGPATH " <PATH> " ARGINFO " <ANNOTATIONFILE> " ARGNINFO " <BACKGROUNDDESC> " ARGWORKDIR " <WORKDIR>" << endl;
	cout << "\t" ARGSHEIGHT " <HEIGHT> " ARGSWIDTH " <WIDTH> " ARGSRATIO " <SAMPLINGRATIO> [" ARGLIVE " " ARGINTERACT "]" << endl << endl;

	cout << "\tFeatureTrack.exe " ARGPATH " <PATH> " ARGVECPATH " <VECFILE> " ARGNSAMPLES " <NUMSAMPLES> " ARGNINFO " <BACKGROUNDDESC>" << endl;
	cout << "\t" ARGWORKDIR " <WORKDIR> "  ARGSHEIGHT " <HEIGHT> " ARGSWIDTH " <WIDTH> " ARGSRATIO " <SAMPLINGRATIO> [" ARGLIVE " " ARGINTERACT "]" << endl << endl;

	cout << "\tFeatureTrack.exe " ARGPATH " <PATH> " ARGFEATURES " <FEATUREFILE> " ARGSRATIO " <SAMPLINGRATIO> [" ARGLIVE " " ARGINTERACT "]" << endl << endl;

	cout << ARGPATH << "\t" << "Path to video file. If Live, then camera device number (default 0)" << endl;
	cout << ARGLIVE << "\t" << "If provided, runs feature tracking on live camera input" << endl;
	cout << endl;
	//cout << ARGIMAGE << "\t" << "Paths to target image files to find in video" << endl;
	cout << ARGVIDEO << "\t" << "Paths to target video of object to find in video" << endl;
	cout << ARGINFO << "\t" << "Path to info/annotation file for positive sample images" << endl;
	cout << ARGVECPATH << "\t" << "Path to .vec file containing processed positive samples" << endl;
	cout << ARGNSAMPLES << "\t" << "Number of positive samples in vec file (if provided)." << endl;
	cout << endl;
	//cout << ARGNIMAGE << "\t" << "Paths to background images to use as control in learning classifier" << endl;
	cout << ARGNVIDEO << "\t" << "Paths to background video to use as control in learning classifier" << endl;
	cout << ARGNINFO << "\t" << "Path to info/description file for negative sample images" << endl;
	cout << endl;
	//cout << ARGANNOTATE << "\t" << "Run the annotation tool to select target object on sample images" << endl;
	cout << ARGWORKDIR << "\t" << "The directory in which to create intermediate files etc. Default (." PATHSEP ")" << endl;
	cout << ARGSHEIGHT << "\t" << "Height of generated positive samples. Default 32. Required if learning." << endl;
	cout << ARGSWIDTH << "\t" << "Width of generated positive samples. Default 32. Required if learning." << endl;
	cout << ARGSRATIO << "\t" << "Frames to skip video streams for learning/detection. Default (10)" << endl;
	cout << ARGFEATURES << "\t" << "Path to existing classifier (.xml) to use instead of learning from samples" << endl;
	cout << ARGINTERACT << "\t" << "If provided detection process is interactive (default=false)" << endl;
}


void printArgs(Args& args) {
	cout << "Video:\t\t" << (args.isLive ? "Live" : args.videoPath) << endl;
	//cout << "Annotate:\t" << (args.annotate ? "Yes" : "No") << endl;
	cout << "Working Dir:\t" << args.workDir << endl;
	cout << "Feature file:\t" << args.featurePath << endl;
	cout << "+ive info:\t" << args.infoPath << endl;
	cout << "-ive info:\t" << args.nInfoPath << endl;
	cout << "Sample rate:\t" << args.iSamplingRatio << endl;
	cout << "Num. samples:\t" << args.numPSamples << endl;
	cout << "Sample res:\t" << args.sampleHeight << "x" << args.sampleWidth << endl;

	/*if (args.imagePaths.size() > 0) {
		cout << "Target images:" << endl;
		for (string s : args.imagePaths) {
			cout << "\t\t" << s << endl;
		}
	}*/
	if (args.videoPaths.size() > 0) {
		cout << "Target videos:" << endl;
		for (string s : args.videoPaths) {
			cout << "\t\t" << s << endl;
		}
	}
	/*if (args.nImagePaths.size() > 0) {
		cout << "Background images:" << endl;
		for (string s : args.nImagePaths) {
			cout << "\t\t" << s << endl;
		}
	}*/
	if (args.nVideoPaths.size() > 0) {
		cout << "Background videos:" << endl;
		for (string s : args.nVideoPaths) {
			cout << "\t\t" << s << endl;
		}
	}
}

void printError(const string error) {
	cerr << error;
	exit(-1);
}

void makeDir(string dirPath) {
	string command = "mkdir " + dirPath;
	int error = system(command.c_str());
	if (error != 0) {
		printError("Could not create directory: " + dirPath);
	}
}


int numLines(string fname) {
	ifstream f;
	f.open(fname, ifstream::in);
	int lines = 0;
	string temp;
	do {
		lines++;
	} while (getline(f, temp));
	return lines;
}
