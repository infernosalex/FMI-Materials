#include <iostream>
#include <cmath>
using namespace std;

double dist(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool isTriangle(double x1, double y1, double x2, double y2, double x3, double y3) {
    double a = dist(x1, y1, x2, y2);
    double b = dist(x2, y2, x3, y3);
    double c = dist(x3, y3, x1, y1);
    return (a + b > c) && (b + c > a) && (c + a > b);
}

string tip_triunghi(double x1, double y1, double x2, double y2, double x3, double y3) {
    double a = dist(x1, y1, x2, y2);
    double b = dist(x2, y2, x3, y3);
    double c = dist(x3, y3, x1, y1);
    
    if (abs(a - b) < 1e-6 && abs(b - c) < 1e-6) {
        return "echilateral";
    } else if (abs(a - b) < 1e-6 || abs(b - c) < 1e-6 || abs(c - a) < 1e-6) {
        return "isoscel";
    } else if (abs(a*a + b*b - c*c) < 1e-6 || abs(b*b + c*c - a*a) < 1e-6 || abs(c*c + a*a - b*b) < 1e-6) {
        return "dreptunghic";
    } else {
        return "oarecare";
    }
}

double arie(double x1, double y1, double x2, double y2, double x3, double y3) {
    return 0.5 * abs(x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2));
}

int main() {
    double x1, y1, x2, y2, x3, y3;
    
    cin >> x1 >> y1;
    cin >> x2 >> y2;
    cin >> x3 >> y3;

    if (isTriangle(x1, y1, x2, y2, x3, y3)) {
        cout << "Tipul triunghiului: " << tip_triunghi(x1, y1, x2, y2, x3, y3) << endl;
        cout << "Aria triunghiului: " << arie(x1, y1, x2, y2, x3, y3) << endl;
    } else {
        cout << "Punctele nu formează un triunghi." << endl;
    }

    return 0;
}
