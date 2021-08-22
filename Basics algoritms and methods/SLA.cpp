#include <iostream>
#include <cmath>
using namespace std;

double func(const double& x)
{
	return (3 * x * x * x * x + 4 * x * x * x - 12 * x * x - 5);
}

double funcDerivative(const double& x)
{
	return (12 * x * x * x + 12 * x * x - 24 * x);
}

double funcU(const double& x)
{
	return (3 * x * x * x * x + 4 * x * x * x);
}

double funcW(const double& x)
{
	return (12 * x * x + 5);
}

void rootSeparation(double& left, double& right)
{
	left = -5;
	right = 5;
	for (int pos = func(left++); pos * func(left) >= 0; ++left);
	--left;
	for (int pos = func(right--); pos * func(right) >= 0; --right);
	++right;
	return;
}

double rootDihotomiy(const double& left, const double& right)
{
	double x, tmpR = right, tmpL = left;
	int pos;
	if (func(tmpL) >= 0) pos = 1;
	else pos = -1;
	while (tmpR - tmpL > 0.001 || tmpL - tmpR > 0.001)
	{
		x = (tmpR + tmpL) / 2;
		if (func(x) * pos <= 0) tmpR = x;
		else tmpL = x;
	}
	return tmpR;
}

double rootHord(const double& left, const double& right)
{
	double a = right, b = left;
	while (fabs(b - a) > 0.001)
	{
		a = b - (b - a) * func(b) / (func(b) - func(a));
		b = a - (a - b) * func(a) / (func(a) - func(b));
	}
	return b;
}

double rootNewton(double x)
{
	do {
		x -= func(x) / funcDerivative(x);
	} while (fabs(func(x)) > 0.001);
	return x;
}

double rootIteration(double x)
{
	const double tmp = 1 / funcDerivative(x);
	double tmpF;
	do {
		tmpF = tmp * func(x);
		x -= tmp * func(x);
	} while (tmpF > 0.001);
	return x;
}

void rootSeparationGraph(double& left, double& right)
{
	left = -5;
	right = 5;
	int i = fabs(funcU(left) - funcW(left));
	for (++left; left != 100; left += 0.25)
	{
		double tmp = fabs(funcU(left) - funcW(left));
		if (tmp > i)
		{
			left -= 0.5;
			break;
		}
		else i = tmp;
	}
	i = fabs(funcU(right) - funcW(right));
	for (--right; right != -100; right -= 0.25)
	{
		double tmp = fabs(funcU(right) - funcW(right));
		if (tmp > i)
		{
			right += 0.5;
			break;
		}
		else i = tmp;
	}
}

void dialogSLA()
{
	cout << "\t\t\t\t\t\t**Simple linear algebra**\n\n";
	double left, right, dihotomiy, hord, newton, iteration;
	rootSeparation(left, right);
	dihotomiy = rootDihotomiy(left, right);
	hord = rootHord(left, right);
	cout << "\nВычисление корней в отрезке функции с помощью табулирования: [" << left << ";" << right << "]\n\nДихотомия: " << dihotomiy << "\nХорд: " << hord;
	rootSeparationGraph(left, right);
	newton = rootNewton(left);
	iteration = rootIteration(left);
	cout << "\n\nВычисление корней в отрезке функции с помощью графической оценки: [" << left << ";" << right << "]\n\nНьютон: " << newton << "\nИтерация: " << iteration << endl;
	return;
}