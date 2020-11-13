#include <vector>
#include "integrator.h"

using namespace std;

/*
Solid - твердое тело
Oscill - осциллятор
Оба наследники Integrable
Интегратор должен собрать все моменты с осцилляторов и запуститься.
*/

// TODO: Перенести объявление Solid в заголовок

class Solid : public Integrable{
public:

    Solid(){
        omega_x = omega_y = omega_z = 0;
        epsil_x = epsil_y = epsil_z = 0;
    }

    void Integrate(double step) override{
        omega_x = Integrate::Euler(omega_x, epsil_x, step);
        omega_y = Integrate::Euler(omega_y, epsil_y, step);
        omega_z = Integrate::Euler(omega_z, epsil_z, step);
    }

     double GetOmegaMag() {
        return omega_x*omega_x + omega_y*omega_y + omega_z*omega_z;
    }

private:
    double omega_x, omega_y, omega_z;
    double epsil_x, epsil_y, epsil_z;
    vector<Integrable*> connected_parts;
};