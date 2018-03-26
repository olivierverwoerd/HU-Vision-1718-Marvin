#include "IntensityImageStudent.h"
#include <iostream>
#include <algorithm>
#include <vector>

IntensityImageStudent::IntensityImageStudent() : IntensityImage() {
	//int throwError = 0, e = 1 / throwError; //Throws error without the need to include a header
	//TODO: Nothing

	std::cout << "IntensityImageStudent() called" << std::endl;
}

IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) : IntensityImage(other.getWidth(), other.getHeight()), temp(new Intensity[getWidth()*getHeight()]){
	//TODO: Create a copy from the other object
	std::cout << "IntensityImageStudent(other) called" << std::endl;
	for (int i = 0; i < getWidth()*getHeight(); i++) {
		temp[i] = other.temp[i];
	}
}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) : IntensityImage(width, height),  temp(new Intensity[width*height]){
	//TODO: Initialize pixel storage
	//std::cout << "IntensityImageStudent(width, height) called" << std::endl;

	for (int i = 0; i <= width*height; i++) {
		temp[i] = 0;
	}
}

IntensityImageStudent::~IntensityImageStudent() {
	//TODO: delete allocated objects
	
	//copied from private
	delete[] temp;
}

void IntensityImageStudent::set(const int width, const int height) {
	IntensityImage::set(width, height);
	//std::cout << "Set(width, height) called" << std::endl;
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)
	
	//copied from Private
	delete[] temp;
	this->temp = new Intensity[width*height];
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
	//std::cout << "Set(const IntensityImageStudent called" << std::endl;
	IntensityImage::set(other.getWidth(), other.getHeight());
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)
	
	delete[] temp;
	this->temp = new Intensity[getWidth()*getHeight()];
	for (int i = 0; i < getWidth()*getHeight(); i++) {
		temp[i] = other.temp[i];
	}
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	//std::cout << "SetPixel(int, int, Intensity) called" << std::endl;
	temp[y*getWidth() + x] = pixel;
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	//std::cout << "SetPixel(int, Intensity) called" << std::endl;
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
	//Get Intensity at position X x Y
	//std::cout << "GetPixel(int, int) called" << std::endl;

	return temp[y*getWidth() + x];
	//return 2;
}

Intensity IntensityImageStudent::getPixel(int i) const {
	//TODO: see setPixel(int i, RGB pixel)
	//std::cout << "GetPixel(int) called" << std::endl;

	return 1;
}