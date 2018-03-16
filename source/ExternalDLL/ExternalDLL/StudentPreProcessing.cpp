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

	//auto width = image.getWidth();
	//auto height = image.getHeight();
	std::cout << (int)image.getPixel(50, 50) << std::endl; // dit mag
	std::cout << (int)image.getPixel(10, 50) << std::endl;
	std::cout << (int)image.getPixel(32, 50) << std::endl;
	std::cout << (int)image.getPixel(50, 5) << std::endl;
	std::cout << "w="<< image.getWidth() << "  h=" << image.getHeight() << std::endl; // dit mag

	//trying to set (1,1) 1 waarde hoger
	//Intensity test = image.getPixel(1, 1) + 1;
	//std::cout << "test =" << (int)test << std::endl;
	//&image.setPixel(1, 1, (Intensity)test);

	auto width = 5;
	auto height = 5;

	IntensityImage * copyOfImage = ImageFactory::newIntensityImage(width, height);
	auto beep = copyOfImage->getPixel(1, 1);
	std::cout << "beep:" << (int)beep << std::endl;
	copyOfImage->setPixel(1, 1, 2);
	auto beep2 = copyOfImage->getPixel(1, 1);
	std::cout << "beep2:" << (int)copyOfImage->getPixel(1, 1) << std::endl;

	/*
	//creating a new empty image, trying to set on pixel on a random 4
	auto beep = IntensityImage(width, heigth);
	Intensity x = 4;
	beep.setPixel(1, 1, x);
	*/

	
	//Dit stuk checkt de volledige afbeelding met GetPixel en zet het in een array
	std::vector <int> v;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			v.push_back((int)copyOfImage->getPixel(i, j));
		}
	}

	for (auto i = v.begin(); i != v.end(); ++i)
		std::cout << *i << ' ';
	
	std::cout << "\n" << width << std::endl;
	std::cout << "width=" << width << std::endl;
	std::cout << "height=" << height << std::endl;

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
	int threshold = 80;
	//wederom een nieuwe afbeeling maken in student
	auto width = 5;
	auto height = 5;

	std::cout << (int)image.getPixel(32, 50) << std::endl;
	IntensityImage * copyOfImage = ImageFactory::newIntensityImage(width, height);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if ((int)copyOfImage->getPixel(i, j) < threshold) {
				copyOfImage->setPixel(i, j, 0); //zou niet de copy moeten pakken maar image maar de getpixel werkt daar nog niet...
			}
			else {
				copyOfImage->setPixel(i, j, 255);
			}
		}
	}


	time = clock() - time;
	std::cout << "Time spent Thresholding: " << time << " milliseconds \n";
	return copyOfImage;
}