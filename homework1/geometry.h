#pragma once
# define M_PI 3.14159265358979323846

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
//fixed cpp
class Point {

private:

    double x;
    double y;

public:

    Point();


    Point(double __x, double __y);


    Point(const Point& another);

    virtual ~Point();

    double getX() const;

    double getY() const;

    Point& operator = (const Point& another);

};

class PolygonalChain : public Point {

private:
    vector<Point> a_point;
    int counter_of_points;

public:

    PolygonalChain();

    PolygonalChain(int n, Point point[]);

    PolygonalChain(const PolygonalChain& another);

    Point getPoint(const int num) const;

    int getN() const;

    double range(const Point& point1, const Point& point2) const;

    virtual double perimeter() const;

    PolygonalChain& operator = (const PolygonalChain& another);

};

class ClosedPolygonalChain : public PolygonalChain {

public:

    ClosedPolygonalChain();

    ClosedPolygonalChain(int n, Point* point);

    ClosedPolygonalChain(const ClosedPolygonalChain& another);

    double perimeter() const;

    ClosedPolygonalChain& operator = (const ClosedPolygonalChain& another);
};

class Polygon : public ClosedPolygonalChain {

public:

    Polygon();

    Polygon(int n, Point* point);

    Polygon(const Polygon& another);

    double area() const;

    Polygon& operator = (const Polygon& another);
};

class Triangle : public Polygon {

public:

    Triangle();

    Triangle(int n, Point* point);

    Triangle(const Triangle& another);

    bool hasRightAngle() const;

    Triangle& operator = (const Triangle& another);
};

class Trapezoid : public Polygon {

public:

    Trapezoid();

    Trapezoid(int n, Point* point);

    Trapezoid(const Trapezoid& another);

    double height() const;

    Trapezoid& operator = (const Trapezoid& another);
};

class RegularPolygon : public Polygon {

public:

    RegularPolygon();

    RegularPolygon(int n, Point* point);

    RegularPolygon(const RegularPolygon& another);

    double perimeter() const;

    double area() const;

    RegularPolygon& operator = (const RegularPolygon& another);

};

