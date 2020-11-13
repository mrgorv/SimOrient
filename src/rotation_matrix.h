#ifndef ROTATION_MATRIX_H_
#define ROTATION_MATRIX_H_

#include <vector>
using std::vector;

class RotationMatrix{
public:
	RotationMatrix();
	RotationMatrix(vector<vector<float>> m);
private:
	vector<vector<float>> matrix;
};



#endif /* ROTATION_MATRIX_H_ */
