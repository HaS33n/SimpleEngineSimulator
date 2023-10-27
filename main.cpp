#include <SFML/Graphics.hpp>
#include "include/SimManager.h"
#include <iostream>
#define M_PI 3.14159265358979323846
#include <cmath>

double integral(long double(*f)(long double x), long double a, long double b, int n) {
    long double step = (b - a) / n;
    long double area = 0.0; 
    for (int i = 0; i < n; i++) {
        area += f(a + (i + 0.5) * step) * step;
    }
    return area;
}

long double f(long double t) {
    double n = 0.002;
    double V = 103.6;
    double d = 1.2;
    double R = 8.314;
    double K = 298.15;
    double p = 101300;
    double B = 0.0000672;
    double A = 0.0058088;
    return(B * sqrt(2 * (p - ((n*R*K) / (A * V * t))) / (d * (1 - (pow((B / A), 2))))));
    //return (B * sqrt(2 * (p - ((n * R * K) / (A * V * t))) / (d * (1 - (pow((B / A), 2))))));
}

int main()
{
	//sf::RenderWindow window(sf::VideoMode(800,600), "Simple Car Engine Simulator"); 
	//SimManager SM(window);
	//SM.runSimulation();

    std::cout.precision(30);
    //std::cout << integral(f, 0, 0.00083, 5); //przy 10 sie wypierdala
    std::cout << f(0.00083/4);
 

	return 0;
}