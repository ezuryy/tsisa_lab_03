#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>

using std::cout;
using std::string;

double T_MAX = 10000.;
const double T_MIN = 0.01;
const double LOWER_EDGE = 1.;
const double UPPER_EDGE = 4.;
enum IsUnimodal : bool {
    True = true,
    False = false
};

double MyFunction(const double &x) {
    return -sqrt(x) * sin(x) + 2;
}

void PrintTopLine() {
    cout << std::setw(3) << "  N  "
         << std::setw(9) << "T  "
         << std::setw(9) << "x  "
         << std::setw(9) << "f(x)\n";
}

void PrintLine(const int &number, const double &temperature, const double &x,
               const double &y) {
    cout << std::fixed << std::setprecision(3)
         << std::setw(3) << number << "  "
         << std::setw(9) << temperature << "  "
         << std::setw(6) << x << "  "
         << std::setw(6) << y << '\n';
}

void SearchMinimumOfFunction(const IsUnimodal &isUnimodal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(LOWER_EDGE, UPPER_EDGE);
    double x = dist(gen);
    double y = (isUnimodal ? MyFunction(x) : sin(5 * x) * MyFunction(x));
    int number = 1;
    double tCurrent = T_MAX;
    PrintTopLine();
    while (tCurrent > T_MIN) {
        double xNext = dist(gen);
        double yNext = (isUnimodal ? MyFunction(xNext) : sin(5 * xNext) *
                                                         MyFunction(xNext));
        PrintLine(number, tCurrent, x, y);
        double deltaF = yNext - y;
        if (deltaF <= 0) {
            x = xNext;
            y = yNext;
        } else {
            double p = exp(-deltaF / tCurrent);
            std::discrete_distribution<> distrib({1 - p, p});
            if (distrib(gen)) {
                x = xNext;
                y = yNext;
            }
        }
        tCurrent *= 0.95;
        number++;
    }
    cout << "\nResult for function\t";
    cout << (isUnimodal ? "-sqrt(x) sin(x) + 2" : "(-sqrt(x) sin(x) + 2) * sin(5x)");
    cout << " :\n\tXmin = " << x
         << "  Fmin = " << y;
    cout << "\n\n";
}

int main() {
    cout << "Variant 7: \t -sqrt(x) * sin(x) + 2 \t [" << LOWER_EDGE << "; "
         << UPPER_EDGE << "]\n";
    cout << "Part 1. Search for the extremum of a unimodal function f(x) :\n";
    SearchMinimumOfFunction(IsUnimodal::True);
    cout << "Part 2. Search for the extremum of a multimodal function "
            "f(x) * sin(5x) :\n";
    SearchMinimumOfFunction(IsUnimodal::False);
}
