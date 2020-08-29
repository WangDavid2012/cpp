#ifndef _COMPLEX_H_
#define _COMPLEX_H_
#include<iostream>
#include<math.h>

namespace mySTL{
	const double pi(3.14159265);

    template<class T>
	class complex
	{
	private:
		T _real;
		T _image;
	public:
		complex():_real(0),_image(0){}
		complex(T real,T image){
			_real = real;
			_image = image;
		}

  		T real(){return _real;}	
		T image(){return _image;}
		T abs(){return sqrt(_real*_real + _image*_image);}	
		T norm(){return _real*_real + _image*_image;}

		complex conj(){
			complex com2;
			com2._real = _real;
  			com2._image = _image * -1;
			return com2;
		}
		complex operator+(const complex& com2){
			complex com3;
			com3._real = _real + com2._real;
  			com3._image = _image + com2._image;
			return com3;
		}
		complex operator-(const complex& com2){
			complex com3;
			com3._real = _real - com2._real;
  			com3._image = _image - com2._image;
			return com3;
		}
		complex operator*(const complex& com2){
			complex com3;
			com3._real = _real * com2._real - _image * com2._image;
  			com3._image = _real * com2._image - _image * com2._real;
			return com3;
		}

		//:(a+bi)/(c+di)=(ac+bd)/(c^2+d^2) +(bc-ad)/(c^2+d^2)i
		complex operator/(const complex& com2){
			complex com3;
			com3._real = (_real*com2._real+_image*com2._image)/(com2._real*com2._real+com2._image*com2._image);
  			com3._image = _image*com2._real-_real*com2._image;
			return com3;
		}
		void Display(){
			std::cout<<(_real)<<" + "<<(_image)<<"i"<<std::endl;
		}
		~complex(){

		}

	};

}
#endif
