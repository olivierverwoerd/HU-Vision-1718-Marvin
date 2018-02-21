#include "StudentPreProcessing.h"
#include "GrayscaleAlgorithm.h"
#include <iostream>
#include "ImageFactory.h"
#include "HereBeDragons.h"
#include <time.h>

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	std::cout << "Starting EdgeDetection\n\n";
	clock_t time = clock(); //start clock
	std::cout << (int)image.getPixel(12, 1) << '\n'; // dit mag
	std::cout << "w="<< image.getWidth() << "  h=" << image.getHeight() <<'\n'; // dit mag

	auto width = image.getWidth();
	auto heigth = image.getHeight();

	std::cout << "width=" << width << std::endl;
	std::cout << "height=" << heigth << std::endl;

	

	//IntensityImage new(image.getWidth(), image.getHeight());

	//image.setPixel(1,2, 'd');
	//std::cout << (int)image.getPixel(16, 16) << '\n'; // dit mag
	//IntensityImage &new = IntensityImage::Image(12, 12);
	//IntensityImage * newIntensityImage(const int 600, const int 600);
	//IntensityImage * ImageFactory::ImplementationStudent::newIntensityImage(const int width, const int height);
	//hier moeten wij onze dingen aanmaken
	//beginnen met een blanko image via imagefactory in de zefde size als image. Dan daaroverheen de filters gooien
	// We moeten en egde en thresholding doen omdat het veel met elkaar te maken heeft
	//hier gaat de les van volgende week over
	//IntensityImage::Image new = IntensityImage::Image(400, 400);
	

	time = clock() - time;
	std::cout << "\nTime spent EdgeDetection: " << time << " milliseconds \n";
	return 0;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	std::cout << "Starting Thresholding\n\n";
	clock_t time = clock(); //start clock




	time = clock() - time;
	std::cout << "Time spent Thresholding: " << time << " milliseconds \n";
	return 0;
}