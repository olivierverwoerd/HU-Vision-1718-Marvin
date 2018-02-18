#include "StudentPreProcessing.h"
#include <iostream>


IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	//hier moeten wij onze dingen aanmaken
	//beginnen met een blanko image via imagefactory in de zefde size als image. Dan daaroverheen de filters gooien
	// We moeten en egde en thresholding doen omdat het veel met elkaar te maken heeft
	//hier gaat de les van volgende week over
	//IntensityImage::Image new = IntensityImage::Image(400, 400);
	std::cout << "EdgeDetection\n";
	return 0;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	std::cout << "Thresholding\n";
	return 0;
}