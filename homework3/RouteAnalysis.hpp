#pragma once
#include <string>
#include <list>
#include <vector>

class Stop
{
private:
    unsigned index;
    std::string type;
    std::vector<std::string> sts;
    std::vector<std::string> routes;
    std::pair<double, double> coords;

    std::vector<std::string> string_splitting(const std::string&, char) const;
    std::string replace(const std::string&, const std::string&, const std::string&) const;

public:
    Stop() {}

    void set_index(unsigned);
    void set_type(const std::string&);
    void set_sts(const std::string&);
    void set_routes(const std::string&);
    void set_coords(const std::string&);

    unsigned get_index() const;
    std::string get_type() const;
    const std::vector<std::string>& get_sts() const;
    const std::vector<std::string>& get_routes() const;
    std::pair<double, double> get_coords() const;

    static double get_route_length(const std::vector<std::pair<double, double>>&);
};