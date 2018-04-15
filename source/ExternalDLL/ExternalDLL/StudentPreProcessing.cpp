#include "StudentPreProcessing.h"
#include "GrayscaleAlgorithm.h"
#include <iostream>
#include <math.h>
#include "ImageFactory.h"
#include "HereBeDragons.h"
#include <time.h>
#include <vector>

#include "IntensityImageStudent.h"

void apply_LOG(IntensityImage &newImage, int x, int y, IntensityImage &copyOfImage) {
	const int N = 7;
	const int marge = N/2+1; //marge is get the center pixel which is [marge] pixels from filter[0][0]

	int LoG[N][N] = {	{ 0, 0, -1, -2, -1, 0, 0, },
						{ 0, -2, -3, -4, -3, -2, 0, },
						{ -1, -3, 1, 9, 1, -3, -1, },
						{ -2. - 4, 9, 24, 9, -4, -1 },
						{ -1, -3, 1, 9, 1, -3, -1, },
						{ 0, -2, -3, -4, -3, -2, 0, },
						{ 0, 0, -1, -2, -1, 0, 0, } };

	double sum = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			auto temp = int(copyOfImage.getPixel(x + i, y + j));
			temp *= LoG[i][j];
			sum += temp;
		}
	}

	sum = sum / 50 + 127;

	if (sum > 256) {
		newImage.setPixel(x + marge, y + marge, 255);
	}
	else if (sum < 0) {
		newImage.setPixel(x + marge, y + marge, 0);
	}
	else  {
		newImage.setPixel(x + marge, y + marge, sum);
	}
}

void apply_gaussian(IntensityImage &newImage, int x, int y, IntensityImage &copyOfImage) {
	const int N = 5;
	const int marge = floor((float)N / 2);

	int gaussian[N][N] = { {	1, 2, 3, 2, 1	},
							{	2, 7, 11,7, 2	},
							{	3, 11,17,11,3	},
							{	2, 7, 11,7, 2	},
							{	1, 2, 3, 2, 1	} };
	
	double scaling = 1.0 / 121.0;
	double sum = 0;

	for (int i = 0; i <= N-1; i++) {
		for (int j = 0; j <= N-1; j++) {
			auto temp = int(copyOfImage.getPixel(x + i, y + 1));
			temp *= gaussian[i][j];
			sum += temp;
		}
	}

	int pixel = sum * scaling;
	newImage.setPixel(x + marge, y + marge, int(pixel));

}

void apply_laplacian(IntensityImage &newImage, int x, int y, IntensityImage &copyOfImage) {
	const int N = 9;
	const int marge = floor((float)N / 2);

	int laplacian[N][N] = { { 0, 0, 0, -1, -1, -1, 0, 0, 0 },
							{ 0, 0, 0, -1, -1, -1, 0, 0, 0 },
							{ 0, 0, 0, -1, -1, -1, 0, 0, 0 },
							{ -1,-1,-1, 4, 4, 4, -1, -1, -1 },
							{ -1,-1,-1, 4, 4, 4, -1, -1, -1 },
							{ -1,-1,-1, 4, 4, 4, -1, -1, -1 },
							{ 0, 0, 0, -1, -1, -1, 0, 0, 0 },
							{ 0, 0, 0, -1, -1, -1, 0, 0, 0 },
							{ 0, 0, 0, -1, -1, -1, 0, 0, 0 } };
	
	double sum = 0;

	for (int i = 0; i <= N-1; i++) {
		for (int j = 0; j <= N-1; j++) {
			auto temp = int(copyOfImage.getPixel(x + i, y + j));
			temp *= laplacian[i][j];
			sum += temp;
		}
	}

	sum = int(sum)/8;
	if (sum < -20) {
		if (sum < -255){
			newImage.setPixel(x + marge, y + marge, 0);
		}
		else {
			newImage.setPixel(x + marge, y + marge, sum);
		}
	} 
	else if (sum > 20) {
		if (sum > 255) {
			newImage.setPixel(x + marge, y + marge, 255);
		}
		else {
			newImage.setPixel(x + marge, y + marge, sum);
		}
	}
	else{
		newImage.setPixel(x + marge, y + marge, 127);
	}

}

void filter(IntensityImage &newImage, IntensityImage &copyOfImage) {
	int width = newImage.getWidth();
	int height = newImage.getHeight();
	
	/*
	for (int i = 0; i < width - 2; i++) {
		for (int j = 0; j < height - 2; j++) {
			//for every pixel -2x rand
			apply_gaussian(newImage, i, j, copyOfImage);
		}
	}

	for (int i = 0; i < width - 2; i++) {
		for (int j = 0; j < height - 2; j++) {
			//for every pixel -2x rand
			apply_laplacian(newImage, i, j, copyOfImage);
		}
	}*/

	
	//LoG filter
	for (int i = 0; i < width - 4; i++) {
		for (int j = 0; j < height - 4; j++) {
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

	auto width = image.getWidth(); 
	auto height = image.getHeight();

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

	filter(*newImage, *copyOfImage); 
	

	time = clock() - time;
	std::cout << "\nTime spent EdgeDetection: " << time << " milliseconds \n";
	return newImage;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	std::cout << "\n-------------------------------------------\nStarting Thresholding\n\n";
	clock_t time = clock(); //start clock
	int threshold;

	auto width = image.getWidth();
	auto height = image.getHeight();

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
	int mid = (min + max) / 2;
	avg = avg / 100;
	if (min < 50 || mid > 170) {
		threshold = avg - (max - min) / 5 - (min / 3.5) - 5;
	}
	else {
		threshold = 125 + min / 100;
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
	std::cout << max << std::endl;
	std::cout << min << std::endl;
	std::cout << threshold << std::endl;
	std::cout << avg << std::endl; 
	time = clock() - time;
	std::cout << "Time spent Thresholding: " << time << " milliseconds \n";
	return copyOfImage;
}
