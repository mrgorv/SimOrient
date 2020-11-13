#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

class Integrable {
    virtual void Integrate(double step) = 0;
    virtual int IntegrateEuler(double step);
    virtual int IntegrateKutta(double step);
};

namespace Integrate{

    double Euler(double y, double dy, double dt){
        return y + dy*dt;
    }

    double Runge_Kutta(double y, double dy, double dt);
}

#endif