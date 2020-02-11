/*
 * float_matrix.cpp
 *
 *  Created on: 10 февр. 2020 г.
 *      Author: Александр
 */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const float rad_to_deg = 57.2958;
const float deg_to_rad = 1/57.2958;

class RotationMatrix{
public:
	RotationMatrix(){
		matrix={{1,0,0},{0,1,0},{0,0,1}};
	}

	RotationMatrix(vector<vector<float>> m): matrix(m){}

	vector<vector<float>> GetMatrix(){
		return matrix;
	}

	vector<float> Apply(const vector<float> v){
		vector<float> nv = v;
		nv[0]=matrix[0][0]*v[0]+matrix[0][1]*v[1]+matrix[0][2]*v[2];
		nv[1]=matrix[1][0]*v[0]+matrix[1][1]*v[1]+matrix[1][2]*v[2];
		nv[2]=matrix[2][0]*v[0]+matrix[2][1]*v[1]+matrix[2][2]*v[2];
		return nv;
	}

	vector<float>& operator[](const int i){return matrix[i];}

private:
	vector<vector<float>> matrix;
};

ostream& operator<<(ostream& out, RotationMatrix A){
	vector<vector<float>> temp = A.GetMatrix();
	for(vector<float> i:temp){
		for (float j:i){
			out.width(10);
			out << j << ' ';
		}
		out << "\n";
	}
	return out;
}

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

int main (){
	RotationMatrix M({{2,0,0},{0,1,0},{0,0,1}});
	vector<float> test=M.Apply({3, 4, 5});
	vector<float> ang_test = Rotate({3, 4, 5}, 'X', 1);
	for (auto j:test) cout << j << ' ';
	for (auto i:ang_test) cout << i << ' ';
//	cout << M;
//	cout << endl;
//	M[1][1]=2;
//	cout << M;
	return 0;
}
