# FeatureTrack
Learning object detection from video input

`FeatureTrack` combines various tools shipped with OpenCV to train and implement object detection classifiers. It takes video files as inputs for positive and background samples.

## Requirements
Tested to work with:

* Windows 10
* OpenCV 3.2
* Visual Studio 2015 (development)

The environment variable `OPENCV_DIR` shout be set up to point to OpenCV libraries in your system.

## Use
The application prints usage instructions when run without any arguments:

```
FeatureTrack
FeatureTrack learns to detect objects from sample videos
and runs detection on video streams.

The process happens in 4 stages:
        1a. Frames from positive videos are sampled to generate annotated description files,
        1b. Frames from negative videos are sampled to generate background desscription files.
        2.  The annotation and background files are used to create a binary file (.vec)
        3.  The (.vec) file along with background description file train the classifner (.xml)
        4.  The classifier is used with the provided video stream to detect objects.
This application can pick up the process from any of the above stages.

Usage:
        FeatureTrack.exe -p <PATH> -v <OBJECT VIDEOS...> -nv <BACKGROUND VIDEOS...> -d <WORKDIR>
        -h <HEIGHT> -w <WIDTH> -r <SAMPLINGRATIO> [-l -x]

        FeatureTrack.exe -p <PATH> -info <ANNOTATIONFILE> -ninfo <BACKGROUNDDESC> -d <WORKDIR>
        -h <HEIGHT> -w <WIDTH> -r <SAMPLINGRATIO> [-l -x]

        FeatureTrack.exe -p <PATH> -vec <VECFILE> -n <NUMSAMPLES> -ninfo <BACKGROUNDDESC>
        -d <WORKDIR> -h <HEIGHT> -w <WIDTH> -r <SAMPLINGRATIO> [-l -x]

        FeatureTrack.exe -p <PATH> -f <FEATUREFILE> -r <SAMPLINGRATIO> [-l -x]

-p      Path to video file. If Live, then camera device number (default 0)
-l      If provided, runs feature tracking on live camera input

-v      Paths to target video of object to find in video
-info   Path to info/annotation file for positive sample images
-vec    Path to .vec file containing processed positive samples
-n      Number of positive samples in vec file (if provided).

-nv     Paths to background video to use as control in learning classifier
-ninfo  Path to info/description file for negative sample images

-d      The directory in which to create intermediate files etc. Default (.\)
-h      Height of generated positive samples. Default 32. Required if learning.
-w      Width of generated positive samples. Default 32. Required if learning.
-r      Frames to skip video streams for learning/detection. Default (10)
-f      Path to existing classifier (.xml) to use instead of learning from samples
-x      If provided detection process is interactive (default=false)
```
