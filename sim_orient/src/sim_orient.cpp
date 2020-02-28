//============================================================================
// Name        : sim_orient.cpp
// Author      : Gorv
// Version     :
// Copyright   : C++ Tutorial
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const float rad_to_deg = 57.2958;
const float deg_to_rad = 1/57.2958;

vector<float> Rotate (vector<float> v, char axis, float ang){
	vector<float> nv=v;
	float angle = ang*deg_to_rad;
	switch (axis) {
	case 'X':
		nv[1]=v[1]*cos(angle)-v[2]*sin(angle);
		nv[2]=v[2]*cos(angle)+v[1]*sin(angle);
		break;
	case 'Y':
		nv[0]=v[2]*sin(angle)-v[0]*cos(angle);
		nv[2]=v[2]*cos(angle)-v[0]*sin(angle);
		break;
	case 'Z':
		nv[0]=v[0]*cos(angle)-v[1]*sin(angle);
		nv[1]=v[1]*cos(angle)+v[0]*sin(angle);
		break;
	}
	return nv;
}

int simort() {
	cout << "Accept the struggle!" << endl; // prints Accept the struggle!
	return 0;
}
