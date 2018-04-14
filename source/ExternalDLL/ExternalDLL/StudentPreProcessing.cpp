#include "StudentPreProcessing.h"
#include "GrayscaleAlgorithm.h"
#include <iostream>
#include "ImageFactory.h"
#include "HereBeDragons.h"
#include <time.h>
#include <vector>

#include "IntensityImageStudent.h"

void apply_LOG(IntensityImage &newImage, int x, int y, IntensityImage &copyOfImage) {
	/*
	int laplacian[9][9] = { { 0, 1, 1, 2, 2, 2, 1, 1, 0 },
							{ 1, 2, 4, 5, 5, 5, 4, 2, 1 },
							{ 1, 4, 5, 3, 0, 3, 5, 4, 1 },
							{ 2, 5, 3,-12,-24,-12, 3, 5, 2 },
							{ 2, 5, 0,-24,-40,-24, 0, 5, 2 },
							{ 2, 5, 3,-12,-24,-12, 3, 5, 2 },
							{ 1, 4, 5, 3, 0, 3, 5, 4, 1 },
							{ 1, 2, 4, 5, 5, 5, 4, 2, 1 },
							{ 0, 1, 1, 2, 2, 2, 1, 1, 0 } };
	*/
	int laplacian[7][7] = { { 0, 0, -1, -2, -1, 0, 0, },
							{ 0, -2, -3, -4, -3, -2, 0, },
							{ -1, -3, 1, 9, 1, -3, -1, },
							{ -2. -4, 9, 24, 9, -4, -1 },
							{ -1, -3, 1, 9, 1, -3, -1, },
							{ 0, -2, -3, -4, -3, -2, 0, },
							{ 0, 0, -1, -2, -1, 0, 0, } };
	double sum = 0;

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			auto temp = int(copyOfImage.getPixel(x + i, y + j));
			temp *= laplacian[i][j];
			sum += temp;
		}
	}

	//std::cout << "SUM:" << sum << std::endl;
	//newImage.setPixel(x + 4, y + 4, int(sum));
	//int min = -255;
	//int max = 255;
	//std::cout << sum << "\n";
	sum = sum / 50 + 127;

	if (sum > 256) {
		newImage.setPixel(x + 4, y + 4, 255);
	}
	else if (sum < 0) {
		newImage.setPixel(x + 4, y + 4, 0);
	}
	else  {
		newImage.setPixel(x + 4, y + 4, sum);
	}

	/*if (sum < -20) {
		if (sum < -255) {
			newImage.setPixel(x + 4, y + 4, 0);
		}
		else {
			newImage.setPixel(x + 4, y + 4, sum);
		}
	}
	else if (sum > 20) {
		if (sum > 255) {
			newImage.setPixel(x + 4, y + 4, 255);
		}
		else {
			newImage.setPixel(x + 4, y + 4, sum);
		}
	}
	else {
		newImage.setPixel(x + 4, y + 4, 127);
	}*/
}

void apply_gaussian(IntensityImage &newImage, int x, int y, IntensityImage &copyOfImage) {
	int gaussian[5][5] = { {	1, 2, 3, 2, 1	},
							{	2, 7, 11,7, 2	},
							{	3, 11,17,11,3	},
							{	2, 7, 11,7, 2	},
							{	1, 2, 3, 2, 1	} };
	
	double scaling = 1.0 / 121.0;
	double sum = 0;

	for (int i = 0; i <= 4; i++) {
		for (int j = 0; j <= 4; j++) {
			auto temp = int(copyOfImage.getPixel(x + i, y + 1));
			temp *= gaussian[i][j];
			sum += temp;
		}
	}

	int pixel = sum * scaling;
	newImage.setPixel(x + 2, y + 2, int(pixel));

}

void apply_laplacian(IntensityImage &newImage, int x, int y, IntensityImage &copyOfImage) {
	//std::cout << "Starting Apply_laplacian\n\n";
	
	int laplacian[9][9] = { { 0, 0, 0, -1, -1, -1, 0, 0, 0 },
							{ 0, 0, 0, -1, -1, -1, 0, 0, 0 },
							{ 0, 0, 0, -1, -1, -1, 0, 0, 0 },
							{ -1,-1,-1, 4, 4, 4, -1, -1, -1 },
							{ -1,-1,-1, 4, 4, 4, -1, -1, -1 },
							{ -1,-1,-1, 4, 4, 4, -1, -1, -1 },
							{ 0, 0, 0, -1, -1, -1, 0, 0, 0 },
							{ 0, 0, 0, -1, -1, -1, 0, 0, 0 },
							{ 0, 0, 0, -1, -1, -1, 0, 0, 0 } };
	
	double sum = 0;

	for (int i = 0; i <= 8; i++) {
		for (int j = 0; j <= 8; j++) {
			auto temp = int(copyOfImage.getPixel(x + i, y + 1));
			temp *= laplacian[i][j];
			sum += temp;
		}
	}

	sum = int(sum)/8;
	if (sum < -20) {
		if (sum < -255){
			newImage.setPixel(x + 4, y + 4, 0);
		}
		else {
			newImage.setPixel(x + 4, y + 4, sum);
		}
	} 
	else if (sum > 20) {
		if (sum > 255) {
			newImage.setPixel(x + 4, y + 4, 255);
		}
		else {
			newImage.setPixel(x + 4, y + 4, sum);
		}
	}
	else{
		newImage.setPixel(x + 4, y + 4, 127);
	}

}

void filter(IntensityImage &newImage, IntensityImage &copyOfImage) {
	int width = newImage.getWidth();
	int height = newImage.getHeight();
	
	for (int i = 0; i < width - 2; i++) {
		for (int j = 0; j < height - 2; j++) {
			//for every pixel -2x rand
			apply_gaussian(newImage, i, j, copyOfImage);
		}
	}
	/*
	for (int i = 0; i < width - 4; i++) {
		for (int j = 0; j < height - 4; j++) {
			//for every pixel -2x rand
			apply_laplacian(newImage, i, j, copyOfImage);
		}
	}*/

	//LoG filter
	for (int i = 0; i < width - 4; i++) {
		for (int j = 0; j < height - 4; j++) {
			//for every pixel -2x rand
			apply_LOG(newImage, i, j, copyOfImage);
		}
	}
}

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	std::cout << "-------------------------------------------\nStarting EdgeDetection\n\n";
	clock_t time = clock(); //start clock

	std::cout << (int)image.getPixel(1, 1) << std::endl; // dit mag
	std::cout << "w="<< image.getWidth() << "  h=" << image.getHeight() << std::endl; // dit mag

	auto width = image.getWidth(); //select for accurate width
	auto height = image.getHeight();
	
	//auto width = 5; //for debug
	//auto height = 5;

	IntensityImage * newImage = ImageFactory::newIntensityImage(image);
	IntensityImage * copyOfImage = ImageFactory::newIntensityImage(image);
	//Copy inhoud van &image naar CopyOfImage
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			auto TMP = image.getPixel(i, j);
			newImage->setPixel(i, j, TMP);
			copyOfImage->setPixel(i, j, TMP);
		}
	}

	//here starts the action!
	//apply_laplacian(*copyOfImage);

	//------------------------------------------------------Filter is de manier om hem uit te zetten. sorry
	filter(*newImage, *copyOfImage); 
	
	//Dit stuk checkt de volledige NIEUWE afbeelding met GetPixel en zet het in een array
	/*std::vector <int> v;

	for (int i = 0; i < width; i++) { //set to width
		for (int j = 0; j < height; j++) { //set to height
			v.push_back((int)newImage->getPixel(i, j));
		}
	}
	
	//print width, mostly debug purpose
	for (auto i = v.begin(); i != v.end(); ++i)
		std::cout << *i << ' ';
	*/

	time = clock() - time;
	std::cout << "\nTime spent EdgeDetection: " << time << " milliseconds \n";
	return newImage;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	std::cout << "\n-------------------------------------------\nStarting Thresholding\n\n";
	clock_t time = clock(); //start clock
	int threshold = 140;
	//wederom een nieuwe afbeeling maken in student

	std::cout << (int)image.getPixel(1, 1) << std::endl; // dit mag
	std::cout << "w=" << image.getWidth() << "  h=" << image.getHeight() << std::endl; // dit mag

	auto width = image.getWidth(); //select for accurate width
	auto height = image.getHeight();

	//auto width = 5; //for debug
	//auto height = 5;

	IntensityImage * copyOfImage = ImageFactory::newIntensityImage(image);

	auto min = 255;
	auto max = 0;
	auto avg = 0;
	//Copy inhoud van &image naar CopyOfImage
	for (int i = 0; i < width; i += width/10) {
		for (int j = 0; j < height; j += height/10) {
			auto TMP = image.getPixel(i, j);
			if (TMP < min) {
			min = (int)TMP;
			}
			if (TMP > max) {
			max = (int)TMP;
			}
			avg += TMP;
		}
	}

	if (threshold == 127) { // voorkomt error als berekende waarde exact de middelse grijswaarde is om edge detection problemen te voorkomen
		threshold = 126;
	}
	for (int i = 0; i < width; i++) { //berekent de zwart-witwaardes op basis van de threshold
		for (int j = 0; j < height; j++) {
			auto TMP = image.getPixel(i, j);
			if ((int)TMP == 127) {// bij exacte grijse pixel van edge detection word de pixel wit
			copyOfImage->setPixel(i, j, 255);
			}
			else if ((int)TMP >= threshold) {
				copyOfImage->setPixel(i, j, 255);
			}
			else {
				copyOfImage->setPixel(i, j, 0);
			}
		}
	}
	std::cout << max << std::endl; // dit mag
	std::cout << min << std::endl; // dit mag
	time = clock() - time;
	std::cout << "Time spent Thresholding: " << time << " milliseconds \n";
	return copyOfImage;
}
