#include "IntensityImageStudent.h"
#include <iostream>
#include <algorithm>
#include <vector>

IntensityImageStudent::IntensityImageStudent() : IntensityImage() {
	//int throwError = 0, e = 1 / throwError; //Throws error without the need to include a header
	//TODO: Nothing

	//AndHangAPearlInEveryCowslipsEar = intensity object
	//OverHillOverDale = x  // soms image &other
	// ThoroughBushThoroughBrier = y
}

IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) : IntensityImage(other.getWidth(), other.getHeight()), temp(new Intensity[other.getWidth()*other.getHeight()]){
	//int throwError = 0, e = 1 / throwError;
	//TODO: Create a copy from the other object

	for (int i = 0; i < getWidth()*getHeight(); i++) {
		temp[i] = other.temp[i];
	}
}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) : IntensityImage(width, height),  temp(new Intensity[width*height]){
	//int throwError = 0, e = 1 / throwError;
	//TODO: Initialize pixel storage
	for (int i = 0; i <= width*height; i++) {
		temp[i] = 0;
	}
}

IntensityImageStudent::~IntensityImageStudent() {
	//int throwError = 0, e = 1 / throwError;
	//TODO: delete allocated objects
	
	//copied from private
	//delete[] temp;
}

void IntensityImageStudent::set(const int width, const int height) {
	IntensityImage::set(width, height);
	//int throwError = 0, e = 1 / throwError;
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)
	
	//copied from Private
	delete[] temp;
	this->temp = new Intensity[width*height];
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
	IntensityImage::set(other.getWidth(), other.getHeight());
	//int throwError = 0, e = 1 / throwError;
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)
	
	//delete[] temp;
	//this->temp = new Intensity[getWidth()*getHeight()];
	for (int i = 0; i < getWidth()*getHeight(); i++) {
		temp[i] = other.temp[i];
	}
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
	temp[y*getWidth() + x] = pixel;
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	//int throwError = 0, e = 1 / throwError;
	/*
	* TODO: set pixel i in "Row-Major Order"
	*
	*
	* Original 2d image (values):
	* 9 1 2
	* 4 3 5
	* 8 7 8
	*
	* 1d representation (i, value):
	* i		value
	* 0		9
	* 1		1
	* 2		2
	* 3		4
	* 4		3
	* 5		5
	* 6		8
	* 7		7
	* 8		8
	*/
}

Intensity IntensityImageStudent::getPixel(int x, int y) const {
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)

	//std::cout << "\nSKITTLEGETPIXEL\n" << std::endl;
	return temp[y*getWidth() + x];
	//return 4;
}

Intensity IntensityImageStudent::getPixel(int i) const {
	//int throwError = 0, e = 1 / throwError;
	//TODO: see setPixel(int i, RGB pixel)
	return 0;
}