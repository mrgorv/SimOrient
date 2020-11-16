#include <iostream>
#include <vector>
#include <array>
#include <cmath>
using namespace std;

/*
Объявления классов
*/

using vector3D = array<double, 3>;

namespace Integrate
{
	double Euler(double y, double dy, double dt)
	{
		return y + dy * dt;
	}

	template <typename Container>
	Container Euler(Container y, double dy, double dt)
	{
		Container y_next = y;
		for (size_t i = 0, i < y.size(), ++i)
			y_next[i] = y[i] + dy * dt;
		return y_next;
	}
}

class Integrable
{
public:
	virtual void Integrate() = 0;
	Integrable& SetStep(double step);

protected:
	double integ_step;
};

class Solid : public Integrable
{
public:
	Solid();
	void Integrate() override;
	void AddOscillator(Integrable *osc);

private:
	vector3D ang_velocity;
	vector3D ang_accel;
	vector3D ext_moment;
	std::vector<Integrable*> connected_parts;
};

class Oscillator : public Integrable
{
public:
	Oscillator();
	void Integrate() override;
	array<double, 3> GetMoment();
private:
	vector3D coeffs = {0, 0, 0};
	vector3D moment = {0, 0, 0};
};

/*
Реализации методов
*/

Solid::Solid()
{
}

void Solid::Integrate()
{
	ang_accel = ext_moment;
	ang_velocity = Integrate::Euler(ang_velocity, ang_accel, integ_step);
}

double Solid::GetOmegaMag()
{
	return omega_x * omega_x + omega_y * omega_y + omega_z * omega_z;
}

void Solid::AddOscillator(Integrable *osc)
{
	connected_parts.push_back(osc);
}

int main()
{
	float time = 0;
	Solid body;
	body.SetStep(0.1);

	while (time < 5)
	{
		body.Integrate();
	}
}
