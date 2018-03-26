#include "StudentPreProcessing.h"
#include "GrayscaleAlgorithm.h"
#include <iostream>
#include "ImageFactory.h"
#include "HereBeDragons.h"
#include <time.h>
#include <vector>

#include "IntensityImageStudent.h"

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	std::cout << "Starting EdgeDetection\n\n";
	clock_t time = clock(); //start clock

	std::cout << (int)image.getPixel(1, 1) << std::endl; // dit mag
	std::cout << "w="<< image.getWidth() << "  h=" << image.getHeight() << std::endl; // dit mag

	auto width = image.getWidth(); //select for accurate width
	auto height = image.getHeight();
	
	//auto width = 5; //for debug
	//auto height = 5;

	IntensityImage * copyOfImage = ImageFactory::newIntensityImage(image);
	auto beep = copyOfImage->getPixel(1, 1);
	std::cout << "beep:" << (int)beep << std::endl;
	//copyOfImage->setPixel(1, 1, 1);

	//Copy inhoud van &image naar CopyOfImage
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			auto TMP = image.getPixel(i, j);
			copyOfImage->setPixel(i, j, TMP);
		}
	}
	
	//Dit stuk checkt de volledige afbeelding met GetPixel en zet het in een array
	std::vector <int> v;

	for (int i = 0; i < width; i++) { //set to width
		for (int j = 0; j < height; j++) { //set to height
			v.push_back((int)copyOfImage->getPixel(i, j));
		}
	}

	//print width, mostly debug purpose
	for (auto i = v.begin(); i != v.end(); ++i)
		std::cout << *i << ' ';
	
	time = clock() - time;
	std::cout << "\nTime spent EdgeDetection: " << time << " milliseconds \n";
	return 0;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	std::cout << "Starting Thresholding\n\n";
	clock_t time = clock(); //start clock
	int threshold = 80;
	//wederom een nieuwe afbeeling maken in student
	auto width = image.getWidth();
	auto height = image.getHeight();

	IntensityImage * copyOfImage = ImageFactory::newIntensityImage(width, height);
	std::cout << (int)image.getWidth() << std::endl; // sample of the eye
	std::cout << (int)image.getHeight() << std::endl;

	std::cout << (int)image.getPixel(35, 65) << std::endl; // sample of the eye
	std::cout << (int)image.getPixel(50, 75) << std::endl;
	std::cout << (int)image.getPixel(40, 65) << std::endl; // sample of the eye
	std::cout << (int)image.getPixel(40, 75) << std::endl;


	time = clock() - time;
	std::cout << "Time spent Thresholding: " << time << " milliseconds \n";
	return copyOfImage;
}