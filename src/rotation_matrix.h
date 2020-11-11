#ifndef ROTATION_MATRIX_H_
#define ROTATION_MATRIX_H_

#include <vector>

class RotationMatrix{
public:
	RotationMatrix(){
		matrix={{1,0,0},{0,1,0},{0,0,1}};
	}
private:
	std::vector<std::vector<float>> matrix;
};



#endif /* ROTATION_MATRIX_H_ */
