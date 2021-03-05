#include "geometry.h"

using namespace std;

Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(double __x, double __y)

{
    x = __x;
    y = __y;
}

Point::Point(const Point& another)

{
    x = another.x;
    y = another.y;
}

Point::~Point() = default;

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

Point& Point::operator = (const Point & another) = default;



PolygonalChain::PolygonalChain()

{
    counter_of_points = 0;
    //fixed wtf is this clear, stop doing it
}

PolygonalChain::PolygonalChain(int n, Point point[])

{
    counter_of_points = n;
    for (int i = 0; i < n; i++) {
        a_point.push_back(point[i]);
    }
}

PolygonalChain::PolygonalChain(const PolygonalChain & another) : Point(another)

{
    counter_of_points = another.counter_of_points;
    a_point = another.a_point;
}

Point PolygonalChain::getPoint(const int num) const {
    return a_point[num];
}

int PolygonalChain::getN() const {
    return counter_of_points;
}

double PolygonalChain::range(const Point & point1, const Point & point2) const {
    return sqrt(pow(point1.getX() - point2.getX(), 2) + pow(point1.getY() - point2.getY(), 2));
}

double PolygonalChain::perimeter() const {
    double perimeter_result = 0;

    for (int i = 0; i < getN() - 1; i++) {
        perimeter_result = perimeter_result + range(getPoint(i), getPoint(i + 1));
    }
    return perimeter_result;
}

PolygonalChain& PolygonalChain::operator = (const PolygonalChain & another) = default;




ClosedPolygonalChain::ClosedPolygonalChain() : PolygonalChain() {}

ClosedPolygonalChain::ClosedPolygonalChain(int n, Point * point) : PolygonalChain(n, point) {}

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain & another) : PolygonalChain(another) {}

double ClosedPolygonalChain::perimeter() const {
    //fixed perimeter copy-paste
    return PolygonalChain::perimeter() + range(getPoint(0), getPoint(getN() - 1));
}

ClosedPolygonalChain& ClosedPolygonalChain::operator = (const ClosedPolygonalChain & another) = default;



Polygon::Polygon() : ClosedPolygonalChain() {}

Polygon::Polygon(int n, Point * point) : ClosedPolygonalChain(n, point) {}

Polygon::Polygon(const Polygon & another) : ClosedPolygonalChain(another) {}

double Polygon::area() const {

    double area_result = 0;

    for (int i = 0; i < getN() - 1; i++) {
        area_result = area_result + (getPoint(i).getX() + getPoint(i + 1).getX()) *
            (getPoint(i).getY() - getPoint(i + 1).getY());
    }

    return abs(area_result) / 2;
}

Polygon& Polygon::operator = (const Polygon & another) = default;



Triangle::Triangle() : Polygon() {}

Triangle::Triangle(int n, Point * point) : Polygon(n, point) {}

Triangle::Triangle(const Triangle & another) : Polygon(another) {}
//fixed without sqrt
bool Triangle::hasRightAngle() const {

    double side[3];
    side[0] = pow(getPoint(0).getX() - getPoint(1).getX(), 2) + pow(getPoint(0).getY() - getPoint(1).getY(), 2);
    side[1] = pow(getPoint(1).getX() - getPoint(2).getX(), 2) + pow(getPoint(1).getY() - getPoint(2).getY(), 2);
    side[2] = pow(getPoint(2).getX() - getPoint(0).getX(), 2) + pow(getPoint(2).getY() - getPoint(0).getY(), 2);

    double max_side = side[0];

    for (int i = 1; i < 3; i++) {
        if (side[i] > max_side) {
            side[0] = side[i];
            side[i] = max_side;
            max_side = side[0];
        }
    }
    //fixed return expression
    return side[0] == (side[1] + side[2]);

}

Triangle& Triangle::operator = (const Triangle & another) = default;


Trapezoid::Trapezoid() : Polygon() {}

Trapezoid::Trapezoid(int n, Point * point) : Polygon(n, point) {}

Trapezoid::Trapezoid(const Trapezoid & another) : Polygon(another) {}

double Trapezoid::height() const {

    double part_1, part_2, part_3, part_4, numerator, denominator, fraction;

    part_1 = range(getPoint(0), getPoint(1));
    part_2 = range(getPoint(1), getPoint(2));
    part_3 = range(getPoint(2), getPoint(3));
    part_4 = range(getPoint(3), getPoint(0));

    numerator = pow(part_4 - part_2, 2) + pow(part_1, 2) - pow(part_3, 2);
    denominator = 2 * (part_4 - part_2);
    fraction = pow(numerator / denominator, 2);

    return sqrt(pow(part_1, 2) - fraction);

}

Trapezoid& Trapezoid::operator = (const Trapezoid & another) = default;

//fixed regular polygon perimeter

RegularPolygon::RegularPolygon() : Polygon() {}

RegularPolygon::RegularPolygon(int n, Point * point) : Polygon(n, point) {}

RegularPolygon::RegularPolygon(const RegularPolygon & another) : Polygon(another) {}

double RegularPolygon::perimeter() const {

    double perimeter_res = 0;

    perimeter_res = getN() * range(getPoint(0), getPoint(1));

    return perimeter_res;
}

double RegularPolygon::area() const {

    double angle = tan(M_PI / getN());

    double final_area = (pow(range(getPoint(1), getPoint(2)), 2) * getN()) / (4 * angle);

    return final_area;

}

RegularPolygon& RegularPolygon::operator = (const RegularPolygon & another) = default;
