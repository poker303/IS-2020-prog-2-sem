#include <windows.h>
#include <iostream>
#include <fstream>
#include "RouteAnalysis.hpp"
#include <cstdlib>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include "pugixml.hpp"

using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	pugi::xml_document doc;
	doc.load_file("data_1.xml");

	std::vector<Stop> stops;

	for (auto& station : doc.child("dataset").children("transport_station"))
	{
		Stop prev;
		prev.set_index(atoi(station.child_value("number")));
		prev.set_type(station.child_value("type_of_vehicle"));
		prev.set_sts(station.child_value("location"));
		prev.set_routes(station.child_value("routes"));
		prev.set_coords(station.child_value("coordinates"));

		stops.push_back(prev);
	}

	std::unordered_set<std::string> types;

	std::unordered_map<std::string, unsigned> stops_at_st;

	for (const Stop& temp_stop : stops)
	{
		types.insert(temp_stop.get_type());

		for (const std::string& st : temp_stop.get_sts())
		{
			if (stops_at_st.find(st) != stops_at_st.end()) stops_at_st[st] += 1;

			else stops_at_st[st] = 1;
		}
	}

//1
	std::unordered_map<std::string, std::pair<std::string, unsigned>> max_type_s_stops;
	for (const auto& temp_type : types)
	{
		max_type_s_stops[temp_type].first = "";
		max_type_s_stops[temp_type].second = 0;

		std::unordered_map<std::string, unsigned> stops_at_route;

		for (const auto& temp_stop : stops)
		{
			if (temp_stop.get_type() != temp_type)
				continue;

			for (const auto& route : temp_stop.get_routes())
			{
				if (stops_at_route.find(route) != stops_at_route.end())
					stops_at_route[route] += 1;

				else stops_at_route[route] = 1;
			}
		}

		for (auto [route, num_of_stops] : stops_at_route)
		{
			if (num_of_stops > max_type_s_stops[temp_type].second)
			{
				max_type_s_stops[temp_type].second = num_of_stops;
				max_type_s_stops[temp_type].first = route;
			}
		}
	}

//2
	std::unordered_map<std::string, std::pair<std::string, double>> max_type_s_route;

	for (const auto& temp_type : types)
	{
		//todo first second
		max_type_s_route[temp_type].first = "";
		max_type_s_route[temp_type].second = 0.0;

		std::unordered_map<std::string, std::vector<std::pair<double, double>>> stops_cors_at_route;

		for (const auto& temp_stop : stops)
		{
			if (temp_stop.get_type() != temp_type) continue;

			for (const auto& route : temp_stop.get_routes())
			{
				if (stops_cors_at_route.find(route) != stops_cors_at_route.end())
					stops_cors_at_route[route].push_back(temp_stop.get_coords());

				else stops_cors_at_route[route] = std::vector<std::pair<double, double>>({ temp_stop.get_coords() });
			}
		}

		for (auto [route, stops_coors] : stops_cors_at_route)
		{
			double length = Stop::get_route_length(stops_coors);
			if (length > max_type_s_route[temp_type].second)
			{
				max_type_s_route[temp_type].second = length;
				max_type_s_route[temp_type].first = route;
			}
		}
	}

//3
	std::string st_with_max_routes = "";
	unsigned max_stops_num = 0;

	for (auto [st, stops_num] : stops_at_st)
	{
		if (stops_num > max_stops_num)
		{
			max_stops_num = stops_num;
			st_with_max_routes = st;
		}
	}

	std::cout << "1. The route with the most stops\n";
	for (const auto& temp_type : types)
	{
		std::cout << temp_type << " : " << max_type_s_stops[temp_type].first
			<< " ; " << max_type_s_stops[temp_type].second << " stops\n";
	}
	std::cout << std::endl;
	std::cout << "2. Longest routes\n";
	for (const auto& temp_type : types)
	{
		std::cout << temp_type << " : " << max_type_s_route[temp_type].first
			<< " ; " << round(max_type_s_route[temp_type].second) << " km\n";
	}
	std::cout << std::endl;
	std::cout << "3. The street with the most stops\n";
	std::cout << st_with_max_routes << " ; " << max_stops_num << " stops\n";

}