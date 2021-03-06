# ofxKu
Kuflex extension for openFrameworks.

It contains classes and functions for rendering, image analysis and working with files, which we are using in Kuflex projects.
* Modules are relatively independent. 
* Module ofxKuRasterOpenCV requires ofxOpenCv addon to work - if you don't need it, kust not include in your project.
* ofxKuFileTime::isNewerThan function implementation doesn't works in oF >= 0.9.0, te simplest workaround is change it to return always 'true'.

## Drawing
* ofxKuRectRender class for fast rendering rectangles
* ofxKuLineRender class for fast rendering lines
* ofxKuVertexRender class for fast rendering points
* ofxKuDrawTextureFit(ofTexture &tex, float x, float y, float w, float h) function in ofxKuDrawUtils for fitting texture in rectangle
* ofxKuDrawRaster draws raster array

## Image processing
* ofxKuRaster.h - include it for accessing all image processing functions
* ofxKuRasterArithmetics - add, subtract, multiply, divide, threshold, find mask for range values, 
count number of pixels in range, project on axes, histogram for raster arrays
* ofxKuRasterBlur_int, ofxKuRasterBlur_float - box blur for raster arrays
* ofxKuRasterInterpolate - interpolation of raster arrays, including ofPoint rasters
* ofxKuRasterMorphology - dilatation and erosion, contour detection
* ofxKuRasterResize_nearest - resize raster arrays
* ofxKuFloodFill function which do flood fill in array, removing small blobs
* ofxKuRasterOpenCV - gaussian smoothing, convex hull, implemented with OpenCV. Requires ofxOpenCv addon.

## Statistics
* ofxKuMathStat - compute median value of the vector

## Values
* ofxKuValueCheckChange - checks if value was changed
* ofxKuSlowBit - bit, controllable changing it state

## Presets
* ofxKuPreset - presets maintaining system

## Utilities for files
* ofxKuBufferRecorder class for recording/replaying data buffers, such as kinect data
* ofxKuFile - write and read text files as vector of strings
* ofxKuFileTime::isNewerThan(string fileName1, string fileName2) function which compares file creation times


