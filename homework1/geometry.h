#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED
# define M_PI 3.14159265358979323846

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
//todo cpp
class Point {

private:

    double x;
    double y;

public:

    Point()

    {
        x = 0;
        y = 0;
    }

    Point(double __x, double __y)

    {
        x = __x;
        y = __y;
    }

    Point(const Point& another)

    {
        x = another.x;
        y = another.y;
    }

    void setX(double __x) {
        x = __x;
    }

    void setY(double __y) {
        x = __y;
    }

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    Point& operator=(const Point& another) = default;

};

class PolygonalChain : public Point {

private:
    vector<Point> a_point;
    int counter_of_points;

public:

    PolygonalChain()

    {
        counter_of_points = 0;
        //todo wtf is this clear, stop doing it
        a_point.clear();
    }

    PolygonalChain(int n, Point point[])

    {
        counter_of_points = n;
        for (int i = 0; i < n; i++) {
            a_point.push_back(point[i]);
        }
    }

    PolygonalChain(const PolygonalChain& another) : Point(another)

    {
        counter_of_points = another.counter_of_points;
        a_point = another.a_point;
    }

    Point getPoint(int num) const {
        return a_point[num];
    }

    int getN() const {
        return counter_of_points;
    }

    double range(const Point& point1, const Point& point2) const {
        return sqrt(pow(point1.getX() - point2.getX(), 2) + pow(point1.getY() - point2.getY(), 2));
    }

    virtual double perimeter() const {
        double perimeter_result = 0;

        for (int i = 0; i < getN() - 1; i++) {
            perimeter_result = perimeter_result + range(getPoint(i), getPoint(i + 1));
        }
        return perimeter_result;
    }

    PolygonalChain& operator=(const PolygonalChain& another) = default;

};

class ClosedPolygonalChain : public PolygonalChain {

public:

    ClosedPolygonalChain() : PolygonalChain() {};

    ClosedPolygonalChain(int n, Point* point) : PolygonalChain(n, point) {};

    ClosedPolygonalChain(const ClosedPolygonalChain& another) : PolygonalChain(another) {};

    double perimeter() const {
        //todo perimeter copy-paste
        double perimeter_result = 0;

        for (int i = 0; i < getN(); i++) {
            if (i == getN() - 1)
                perimeter_result = perimeter_result + range(getPoint(i), getPoint(0));
            else
                perimeter_result = perimeter_result + range(getPoint(i), getPoint(i + 1));
        }

        return perimeter_result;
    }

    ClosedPolygonalChain& operator=(const ClosedPolygonalChain& another) = default;
};

class Polygon : public ClosedPolygonalChain {

public:

    Polygon() : ClosedPolygonalChain() {};

    Polygon(int n, Point* point) : ClosedPolygonalChain(n, point) {};

    Polygon(const Polygon& another) : ClosedPolygonalChain(another) {};

    double area() const {

        double area_result = 0;

            for (int i = 0; i < getN()-1; i++) {
                area_result = area_result + (getPoint(i).getX() + getPoint(i+1).getX()) *              
                   (getPoint(i).getY() - getPoint(i+1).getY());
            }

        return abs(area_result) / 2;
    }

    Polygon& operator=(const Polygon& another) = default;
};

class Triangle : public Polygon {

public:

    Triangle() : Polygon() {};

    Triangle(int n, Point* point) : Polygon(n, point) {};

    Triangle(const Triangle& another) : Polygon(another) {};
    //todo without sqrt
    bool hasRightAngle() const {

        double side[3];
        side[0] = range(getPoint(0), getPoint(1));
        side[1] = range(getPoint(1), getPoint(2));
        side[2] = range(getPoint(2), getPoint(0));

        double max_side = side[0];

        for (int i = 1; i < 3; i++) {
            if (side[i] > max_side) {
                side[0] = side[i];
                side[i] = max_side;
                max_side = side[0];
            }
        }
        //todo return expression
        if (pow(side[0], 2) == (pow(side[1], 2) + pow(side[2], 2)))
            return true;
        else
            return false;

    }

    Triangle& operator=(const Triangle& another) = default;
};

class Trapezoid : public Polygon {

public:

    Trapezoid() : Polygon() {};

    Trapezoid(int n, Point* point) : Polygon(n, point) {};

    Trapezoid(const Trapezoid& another) : Polygon(another) {};

    double height() const {

        double part_1, part_2, part_3, part_4, numerator, denominator, fraction, expression;

        part_1 = range(getPoint(0), getPoint(1));
        part_2 = range(getPoint(1), getPoint(2));
        part_3 = range(getPoint(2), getPoint(3));
        part_4 = range(getPoint(3), getPoint(0));

        numerator = pow(part_4 - part_2, 2) + pow(part_1, 2) - pow(part_3, 2);
        denominator = 2 * (part_4 - part_2);
        fraction = pow(numerator / denominator, 2);

        return sqrt(pow(part_1, 2) - fraction);

    }

    Trapezoid& operator=(const Trapezoid& another) = default;
};

//todo regular polygon perimeter
class RegularPolygon : public Polygon {

public:

    RegularPolygon() : Polygon() {};

    RegularPolygon(int n, Point* point) : Polygon(n, point) {};

    RegularPolygon(const RegularPolygon& another) : Polygon(another) {};

    double area() const {

        double angle = tan(M_PI / getN());

        double final_area = (pow(range(getPoint(1), getPoint(2)), 2) * getN()) / (4 * angle);

        return final_area;

    }

    RegularPolygon& operator=(const RegularPolygon& another) = default;

};


#endif // GEOMETRY_H_INCLUDED

