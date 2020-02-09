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

class StringMatrix{
public:
	StringMatrix(size_t n, size_t m, string x): sts(n),cls(m){
		vector<string> X(m,x);
		for (size_t i=0; i<n; i++){
			matrix.push_back(X);
		}
	}
	vector<vector<string>> matrix;
	size_t sts;
	size_t cls;
};

ostream& operator<<(ostream& out, StringMatrix A){
	for(vector<string> i:A.matrix){
		for (string j:i){
			out.width(40);
			out << j << ' ';
		}
		out << "\n";
	}
	return out;
}

StringMatrix operator*(StringMatrix& A, StringMatrix& B){
	string s="";
	StringMatrix R(3,3,"");
	for(size_t i=0; i<A.sts; i++){
		for (size_t j=0; j<A.cls; j++){
			s="";
			for(size_t k=0; k<A.cls; k++){
				string a=A.matrix[i][k];
				string b=B.matrix[k][j];
				if (k!=0 && a!="0" && b!="0"){
					s+='+';
				}
				if (a=="0" || b=="0"){}
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
		R.matrix[i][j]=s;
		}
	}
	return R;
}

int main() {
	StringMatrix X (3,3,"X");
	StringMatrix Y (3,3,"Y");
	StringMatrix Z (3,3,"Z");
	X.matrix={{"1","0","0"},{"0","cos(p)","sin(p)"},{"0","-sin(p)","cos(p)"}};
	Y.matrix={{"cos(k)","0","-sin(k)"},{"0","1","0"},{"sin(k)","0","cos(k)"}};
	Z.matrix={{"cos(t)","sin(t)","0"},{"-sin(t)","cos(t)","0"},{"0","0","1"}};
	StringMatrix F=X*Y;
	F=F*Z;
	cout << F; // prints Accept the struggle!
	return 0;
}
