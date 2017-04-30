#include <iostream>
#include <string>
#include "utils.hpp"
#include "vision.hpp"

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	Args args;
	initializeArgs(args);
	parseArgs(argc, argv, args);

	if (args.featurePath.length() == 0) {
		// if no feature file specified, learn classifier

		// NEGATIVE SAMPLES
		if (args.nInfoPath.length() == 0) {
			// if no negative info file specified, construct from negative image/video samples

			if (args.nVideoPaths.size() > 0) {
				// sample and save frames from negative video samples
				vector<string> paths = sampleFramesFromVideo(args.nVideoPaths, args.iSamplingRatio, args.workDir, "n", true);
				args.nImagePaths.insert(args.nImagePaths.end(), paths.begin(), paths.end());
			}
			if (args.nImagePaths.size() > 0) {
				// if negative image file paths present, construct info file manually
				ofstream f;
				args.nInfoPath = NINFOFILE;
				f.open(args.nInfoPath, ofstream::out);
				for (string path : args.nImagePaths) {
					f << path << endl;
				}
				f.close();
			}
			args.numNSamples = (int) args.nImagePaths.size();
		}
		else {
			args.numNSamples = numLines(args.nInfoPath);
		}


		// POSITIVE SAMPLES
		if (args.vecPath.empty()) {

			if (args.videoPaths.size() > 0 && args.infoPath.empty()) {
				// sample and save frames from positive video samples
				vector<string> paths = sampleFramesFromVideo(args.videoPaths, args.iSamplingRatio, args.workDir, "p", !args.annotate);
				args.imagePaths.insert(args.imagePaths.end(), paths.begin(), paths.end());
			}
			if (args.annotate && args.infoPath.empty()) {
				// call annotator on each sampled frame set
				callAnnotator(args);
				args.infoPath = ANNOFILE;
			}

			args.numPSamples = (args.numPSamples == 0 ? numLines(args.infoPath) : args.numPSamples);

			// create vec file from positive samples to be used by trainer
			createSamples(args);
		}


		// now that positive and negative images are available, begin training
		callTrainer(args);
		// the learned classifier is stored as cascade.xml
		args.featurePath = args.workDir + PATHSEP FEATUREFILE;

	}
	
	
	if (!args.featurePath.empty() && (args.isLive || !args.videoPath.empty())) {
		// if feature path is specified, load that and apply to target video stream
		trackFeatures(args);
	}

}