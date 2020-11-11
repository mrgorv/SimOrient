#include <array>
#include <vector>
#include "sensor.h"
#include "rotation_matrix.h"


class CoarseSunSensor : public Sensor{
public:
	explicit CoarseSunSensor ();
	void Update(){

	}
private:
	std::vector<bool> fotodiods = {0, 0, 0, 0};
	std::vector<int> sun_direction = {0, 0, 0};
	RotationMatrix install_matrix();
};


