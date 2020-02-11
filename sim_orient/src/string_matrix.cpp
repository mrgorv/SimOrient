//============================================================================
// Name        : plus_things.cpp
// Author      : Gorv
// Version     :
// Copyright   : C++ Tutorial
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

struct OrientDescMatrix{
public:
	OrientDescMatrix(size_t n, size_t m, string x): sts(n),cls(m){
		vector<string> X(m,x);
		for (size_t i=0; i<n; i++){
			matrix.push_back(X);
		}
	}
	vector<vector<string>> matrix;
	size_t sts;
	size_t cls;
};

ostream& operator<<(ostream& out, OrientDescMatrix A){
	for(vector<string> i:A.matrix){
		for (string j:i){
			out.width(40);
			out << j << ' ';
		}
		out << "\n";
	}
	return out;
}

OrientDescMatrix operator*(OrientDescMatrix& A, OrientDescMatrix& B){
	string s="";
	OrientDescMatrix R(3,3,"");
	for(size_t i=0; i<A.sts; i++){
		for (size_t j=0; j<B.cls; j++){
			s="";
			for(size_t k=0; k<A.cls; k++){
				string a=A.matrix[i][k];
				string b=B.matrix[k][j];
				if (!s.empty() && a!="0" && b!="0")	s+='+';

				if (a=="0" || b=="0"); // @suppress("Suspicious semicolon")
				else if (a=="1"){
					s+=b;
				}
				else if (b=="1"){
					s+=a;
				}
				else{
					s+=a+'*'+b;
				}

			}
			if (s.empty()) s="0";
			R.matrix[i][j]=s;
		}
	}
	return R;
}

OrientDescMatrix RotateDescPointer (char axis, OrientDescMatrix vec){
	OrientDescMatrix nv=vec;
	switch (axis){
	case 'X':
		nv.matrix[1][0]+=vec.matrix[1][0]+"cos(p)"+"-"+vec.matrix[2][0]+"sin(p)";
		nv.matrix[2][0]+=vec.matrix[2][0]+"cos(p)"+"+"+vec.matrix[1][0]+"sin(p)";
		break;
	case 'Y':
		nv.matrix[0][0]+="-"+vec.matrix[0][0]+"cos(k)"+"+"+vec.matrix[2][0]+"sin(k)";
		nv.matrix[2][0]+="-"+vec.matrix[0][0]+"sin(k)"+"+"+vec.matrix[2][0]+"cos(k)";
		break;
	case 'Z':
		nv.matrix[0][0]+=vec.matrix[0][0]+"cos(t)"+"-"+vec.matrix[1][0]+"sin(t)";
		nv.matrix[1][0]+=vec.matrix[1][0]+"cos(t)"+"+"+vec.matrix[0][0]+"sin(t)";
		break;
	}
	return nv;
}


int main_desc() {
	OrientDescMatrix X (3,3,"X");
	OrientDescMatrix Y (3,3,"Y");
	OrientDescMatrix Z (3,3,"Z");
	OrientDescMatrix V (3,1,"V");
	V.matrix={{"1"},{"1"},{"0"}};
	X.matrix={{"1","0","0"},{"0","cos(p)","sin(p)"},{"0","-sin(p)","cos(p)"}};
	Y.matrix={{"cos(k)","0","-sin(k)"},{"0","1","0"},{"sin(k)","0","cos(k)"}};
	Z.matrix={{"cos(t)","sin(t)","0"},{"-sin(t)","cos(t)","0"},{"0","0","1"}};
	OrientDescMatrix F=X*Y;
	F=Z*F;
	F=F*V;
	cout << F; // prints Accept the struggle!
	cout << endl;
	V = RotateDescPointer('X',V);
	V = RotateDescPointer('Y',V);
	V = RotateDescPointer('Z',V);
	cout << V;
	return 0;
}
