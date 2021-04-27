#define _USE_MATH_DEFINES
#include "RouteAnalysis.hpp"
#include <queue>
#include <cmath>
#include <cfloat>

//auxiliary functions
double get_dist(std::pair<double, double> stop_coord1, std::pair<double, double> stop_coord2)
{
    auto [x_1, y_1] = stop_coord1;
    auto& [xr_1, yr_1] = stop_coord1;

    auto [x_2, y_2] = stop_coord2;
    auto& [xr_2, yr_2] = stop_coord2;
    //fixed strange constants CAPS
    //todo mb const?
    auto LENGTH_OF_THE_MERIDIAN_ARC_IN_ONE_DEGREE = 111.0;
    auto LATITUDE = 58;

    double height = (xr_1 - xr_2) * LENGTH_OF_THE_MERIDIAN_ARC_IN_ONE_DEGREE;
    double width = (yr_1 - yr_2) * LATITUDE;
    return sqrt(pow(height, 2) + pow(width, 2));
}

double Prim(const std::vector<std::pair<double, double>>& stops) {

    double x = 0.0;
    size_t next = 0;
    std::vector<bool> used(stops.size(), false);

    while (next != stops.size())
    {
        size_t cur = next;
        used[cur] = true;
        double min_dist = FLT_MAX;
        next = stops.size();

        for (size_t i = 0; i < stops.size(); i++)
        {
            if (used[i]) continue;
            double temp_dist;
            if ((temp_dist = get_dist(stops[cur], stops[i])) < min_dist)
            {
                min_dist = temp_dist;
                next = i;
            }
        }
        if (next < stops.size())
        {
            for (size_t i = 0; i < stops.size(); i++)
            {
                if (!used[i]) continue;
                double temp_dist;
                if ((temp_dist = get_dist(stops[next], stops[i]) < min_dist))
                {
                    min_dist = temp_dist;
                }
            }
            x += min_dist;
        }
    }
    return x;
}

std::vector<std::string> Stop::string_splitting(const std::string& string, char ch) const
{
    std::vector<std::string> result;
    size_t prev = 0;
    for (size_t i = 0; i < string.length() - 1; i++)
    {
        if (string[i] == ch)
        {
            result.push_back(string.substr(prev, i - prev));
            prev = i + 1;
        }
    }
    result.push_back(string.substr(prev));
    return result;
}

std::string Stop::replace(const std::string& str, const std::string& str1, const std::string& str2) const
{
    std::string temp = str;
    size_t i;
    while ((i = temp.find(str1)) != std::string::npos)
    {
        temp.replace(i, str1.length(), str2);
    }
    return temp;
}

void Stop::set_index(unsigned index)
{
    this->index = index;
}

void Stop::set_type(const std::string& type)
{
    this->type = type;
}

void Stop::set_sts(const std::string& str)
{
    if (str.length() > 0)
    {
        std::string temp = str;
        sts = string_splitting(str, ',');
    }
}

void Stop::set_routes(const std::string& str)
{
    if (str.length() > 0)
        routes = string_splitting(replace(str, ".", ","), ',');
}

void Stop::set_coords(const std::string& str)
{
    std::vector<std::string> tokens = string_splitting(str, ',');
    //todo stof
    coords.first = atof(tokens[0].c_str());
    coords.second = atof(tokens[1].c_str());
}

unsigned Stop::get_index() const { return index; }

std::string Stop::get_type() const { return type; }

const std::vector<std::string>& Stop::get_sts() const { return sts; }

const std::vector<std::string>& Stop::get_routes() const { return routes; }

std::pair<double, double> Stop::get_coords() const { return coords; }

double Stop::get_route_length(const std::vector<std::pair<double, double>>& stops)
{
    return Prim(stops);
}