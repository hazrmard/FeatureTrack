//#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>
#include "utils.hpp"
#include "vision.hpp"

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	cout << system("mkdir TEST");
	exit(0);
	Args args;
	Data data;
	initializeArgs(args);
	parseArgs(argc, argv, args);

	cout << endl;
	printHelp();
	cout << endl;
	printArgs(args);

	if (args.annotate) {
		callAnnotator(args);
	}

	// readTargetImages(args.imagePaths, data.images);

	// callTrainer();
}