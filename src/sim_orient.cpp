/*
Модель (тестовая) углового движения твердого тела с упругими элементами в обезвешенном пространстве
Автор: Савельев Е.В.
Организация: <>
Дата: 16.11.20
*/

#include <iostream>
#include <vector>
#include <array>
#include <cmath>
using namespace std;

/*
Объявления классов
*/

using vector3D = std::array<double, 3>;

namespace Integrate
{
	double Euler(double y, double dy, const double dt) {return y + dy * dt;}

	template <typename Container>
	Container Euler(Container y, Container dy, const double dt)
	{
		Container y_next = y;
		for (size_t i = 0; i < y.size(); ++i)
			y_next[i] = y[i] + dy[i] * dt;
		return y_next;
	}
}

class Integrable
{
public:
	virtual ~Integrable() = default;
	virtual void Integrate() = 0;
	void SetStep(double step);

protected:
	double integ_step = 0.1;
};

class MomentSource : public Integrable
{
public:
	virtual void Integrate() = 0;
	virtual void SetTarget(Integrable* t);
	virtual vector3D GetMoment() = 0;
protected:
	Integrable* target;
};

class Solid : public Integrable
{
public:
	Solid() = default;
	void Integrate() override;
	void SetAcceleration(vector3D accel);
	Solid& AddMomentSource(MomentSource* msc);
	vector3D GetVelocity();
	vector3D GetAcceleration();

private:
	vector3D ang_velocity = {0, 0, 0};
	vector3D ang_accel = {0, 0, 0};
	vector3D ext_moment = {0, 0, 0};
	std::vector<MomentSource*> moment_sources;
};

class Oscillator final : public MomentSource
{
public:
	explicit Oscillator(double f);
	void Integrate() override;
	vector3D GetMoment() override;

private:
	const double frequency = 0;
	const double dissip = 0.4;
	double coordinate = 1;
	double velocity = 0;
	double accel = 0;
	vector3D coeffs = {1, 1, 1};
	vector3D moment = {0, 0, 0};
};

/*
Реализации методов
*/
void Integrable::SetStep(double step) {integ_step = step;}
void MomentSource::SetTarget(Integrable* t) {target = t;}

void Solid::Integrate()
{
	ext_moment = {0, 0, 0};
	for (MomentSource* ptr : moment_sources) {
		ext_moment[0] += ptr->GetMoment()[0];
		ext_moment[1] += ptr->GetMoment()[1];
		ext_moment[2] += ptr->GetMoment()[2];
	}
	ang_accel = ext_moment;
	ang_velocity = Integrate::Euler(ang_velocity, ang_accel, integ_step);
}

Solid& Solid::AddMomentSource(MomentSource *msc)
{
	moment_sources.push_back(msc);
	msc->SetTarget(this);
	return *this;
}

void Solid::SetAcceleration(vector3D accel) {ang_accel = accel;}
vector3D Solid::GetAcceleration() {return ang_accel;}
vector3D Solid::GetVelocity() {return ang_velocity;}

Oscillator::Oscillator(double f) : frequency(f) {}

void Oscillator::Integrate()
{
	 vector3D backlash;
	 if (static_cast<Solid*>(target)) backlash = static_cast<Solid*>(target)->GetAcceleration();
	 accel = -dissip*velocity - frequency*frequency*coordinate + (backlash[0]*coeffs[0] + backlash[1]*coeffs[1] + backlash[2]*coeffs[2]);
	 coordinate = Integrate::Euler(coordinate, velocity, integ_step);
	 velocity = Integrate::Euler(velocity, accel, integ_step);
	 for (size_t i = 0; i < 3; ++i) moment[i] = -accel*coeffs[i];
}

vector3D Oscillator::GetMoment() {return moment;}

int main()
{
	vector<Integrable*> objects;
	Solid body;
	Oscillator osc1(1.0);
	Oscillator osc2(2.0);
	body.AddMomentSource(&osc1).AddMomentSource(&osc2);

	objects.push_back(&osc1);
	objects.push_back(&osc2);
	objects.push_back(&body);
	for (Integrable* ptr : objects) ptr->SetStep(0.1);
	float time = 0;
	body.SetAcceleration({1, 0, 0.5});

	do
	{
		for (Integrable* ptr : objects) ptr->Integrate();
		time += 0.1;
		cout.precision(4);
		cout << body.GetVelocity()[0] << ' ' << body.GetVelocity()[1] << ' ' << body.GetVelocity()[2] << "\n";
	} while (time < 5);
}