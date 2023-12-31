// Question 1 - functions
// 
//	you are given the following missing implementation:
//	float applyF(float a, float b, ??????)
//	{
//		return f(a, b);
//	}
//	
//	1) list at least 3 different ways to replace the qustion marks (??????)
//		1. float applyF(float a, float b, float(*f)(float, float)) -> using pointer to a Function
//		2. float applyF(float a, float b, function<float(float, float)> f) -> using std::function<>
//		3.float applyF(float a, float b, float(*f)(float, float)) -> I didn't sure if you mean to implementation with Lambdas or something like this
//	
//	2) replace the qustion marks in the following implementations with the solutions you listed
//
//	3) using one of those options create an add operation and a multiply operation and implement the following computation:
//		(2 * 3) + (4 * 5) + 6
//
//	you may not change the functions' implementation, only complete the signature


#include <iostream>
#include <functional>
using namespace std;


float add(float a, float b) {
	return a + b;
}

float mult(float a, float b) {
	return a * b;
}

float applyF1(float a, float b, float(*f)(float, float))
{
	return f(a, b);
}

float applyF2(float a, float b, function<float(float, float)> f)
{
	return f(a, b);
}

float applyF3(float a, float b, function<double(double, double)> f)
{
	return f(a, b);
}


int main(int argc, char *argv[])
{
	float fNum = 0;
	// calculate fNum = (2 * 3) + (4 * 5) + 6
	float x = applyF1(2, 3, &mult); // (2 * 3)
	float y = applyF1(4, 5, &mult); //  (4 * 5)
	fNum = applyF1(x, y, &add);
	fNum = applyF1(fNum, 6, &add);
	
	std::cout << "(2 * 3) + (4 * 5) + 6 = " << fNum << std::endl;
	getchar();
    return 0;
}

