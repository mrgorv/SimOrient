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

	explicit RotationMatrix(vector<float> ax, float ang){
		vector<float> x,y,z;
		float ca=cos(ang);
		float sa=sin(ang);
		x = {ca+(1-ca)*ax[0]*ax[0], (1-ca)*ax[0]*ax[1]-sa*ax[2], (1-ca)*ax[0]*ax[2]+sa*ax[1]};
		y = {(1-ca)*ax[1]*ax[0]+sa*ax[2], ca+(1-ca)*ax[1]*ax[1], (1-ca)*ax[1]*ax[2]-sa*ax[0]};
		z = {(1-ca)*ax[2]*ax[0]+sa*ax[1], (1-ca)*ax[2]*ax[1]+sa*ax[0], ca+(1-ca)*ax[2]*ax[2]};
		matrix = {x,y,z};
	}

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

RotationMatrix operator*(RotationMatrix& A, RotationMatrix& B){
	float x;
	RotationMatrix R;
	for(size_t i=0; i<2; i++){
		for (size_t j=0; j<2; j++){
			x=0;
			for(size_t k=0; k<2; k++){
				x+=A[i][k];
			}
			R[i][j]=x;
		}
	}
	return R;
}

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

ostream& operator<<(ostream& out, const vector<float>& v){
	for(float i:v)	out << i << ' ';
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

vector<float> RotateAround(const vector<float> v, vector<float> axis, float ang){
	RotationMatrix M = RotationMatrix(axis, ang);
	return M.Apply(v);
}

int main (){
	vector<float> test = {1,2,1};
	vector<float> ox = {1,0,0};
	vector<float> oy = {0,1,0};
	vector<float> oz = {0,0,1};

	//TEST1 - умножение матриц (из симулятора)
	float p = 0.6;
	float k = 0.2;
	float t = 0.8;
	RotationMatrix X({{1,0,0},{0,cos(p),sin(p)},{0,-sin(p),cos(p)}});
	RotationMatrix Y({{cos(k),0,-sin(k)},{0,1,0},{sin(k),0,cos(k)}});
	RotationMatrix Z({{cos(t),sin(t),0},{-sin(t),cos(t),0},{0,0,1}});
	RotationMatrix M=X*Y;
	M=Z*M;
	vector<float> test1 = M.Apply(test);

	//TEST2 - вращение вокруг осей ССК
	vector<float> test2 = RotateAround(test, oy, k);
	test2 = RotateAround(test2, ox, p);
	test2 = RotateAround(test2, oz, t);

	//TEST3 - вращение вокруг осей ПСК
	vector<float> nox = ox;
	vector<float> noy = oy;
	vector<float> noz = oz;
	vector<float> test3;

	test3 = RotateAround(test, oy, k);
	nox = RotateAround(nox, noy, k);
	noz = RotateAround(noz, noy, k);

	test3 = RotateAround(test3, nox, p);
	noy = RotateAround(noy, nox, k);
	noz = RotateAround(noz, nox, k);

	test3 = RotateAround(test3, noz, t);
	nox = RotateAround(nox, noz, k);
	noy = RotateAround(noy, noz, k);

	cout << test1 << endl;
	cout << test2 << endl;
	cout << test3 << endl;
	return 0;
}
