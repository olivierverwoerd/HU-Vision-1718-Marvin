#include "StudentPreProcessing.h"
#include "GrayscaleAlgorithm.h"
#include <iostream>
#include "ImageFactory.h"
#include "HereBeDragons.h"
#include <time.h>
#include <vector>

#include "IntensityImageStudent.h"

void apply_gaussian(IntensityImage &copyOfImage, int x, int y) {
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
	copyOfImage.setPixel(x + 2, y + 2, int(pixel));

}

void apply_laplacian(IntensityImage &copyOfImage, int x, int y) {
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

	sum = int(sum);
	if (sum > -5 && sum < 5 ) {
		copyOfImage.setPixel(x + 4, y + 4, 127);
	} 


}

void filter(IntensityImage &copyOfImage) {
	int width = copyOfImage.getWidth();
	int height = copyOfImage.getHeight();

	for (int i = 0; i < width - 2; i++) {
		for (int j = 0; j < height - 2; j++) {
			//for every pixel -2x rand
			apply_gaussian(copyOfImage, i, j);
		}
	}

	//for (int i = 0; i < width - 4; i++) {
	//	for (int j = 0; j < height - 4; j++) {
	//		//for every pixel -2x rand
	//		apply_laplacian(copyOfImage, i, j);
	//	}
	//}
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

	IntensityImage * copyOfImage = ImageFactory::newIntensityImage(image);

	//Copy inhoud van &image naar CopyOfImage
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			auto TMP = image.getPixel(i, j);
			copyOfImage->setPixel(i, j, TMP);
		}
	}

	//here starts the action!
	//apply_laplacian(*copyOfImage);

	//------------------------------------------------------Filter is de manier om hem uit te zetten. sorry
	//filter(*copyOfImage); 
	
	//Dit stuk checkt de volledige NIEUWE afbeelding met GetPixel en zet het in een array
	/*std::vector <int> v;

	for (int i = 0; i < width; i++) { //set to width
		for (int j = 0; j < height; j++) { //set to height
			v.push_back((int)copyOfImage->getPixel(i, j));
		}
	}

	//print width, mostly debug purpose
	for (auto i = v.begin(); i != v.end(); ++i)
		std::cout << *i << ' ';
	*/

	time = clock() - time;
	std::cout << "\nTime spent EdgeDetection: " << time << " milliseconds \n";
	return copyOfImage;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	std::cout << "\n-------------------------------------------\nStarting Thresholding\n\n";
	clock_t time = clock(); //start clock
	int threshold = 120;
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
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			auto TMP = image.getPixel(i, j);
			if (TMP < min) {
				min = (int)TMP;
			}
			if (TMP > max) {
				max = (int)TMP;
			}
			avg += TMP;
			if ((int)TMP < threshold) {
				copyOfImage->setPixel(i, j, 0);
			}
			else {
				copyOfImage->setPixel(i, j, 255);
			}
		}
	}
	std::cout << max << std::endl; // dit mag
	std::cout << min << std::endl; // dit mag
	std::cout << avg/(height*width)<< std::endl; // dit mag
	time = clock() - time;
	std::cout << "Time spent Thresholding: " << time << " milliseconds \n";
	return copyOfImage;
}
