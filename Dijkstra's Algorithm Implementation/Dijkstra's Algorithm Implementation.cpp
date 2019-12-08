#include "pch.h"
#include <iostream>
#include <vector> 
#include <cmath>
#include <list>
#include <map>
#include <string>

using namespace std;

bool is_visited(string city, vector<string> chosen) {
	for (int i = 0; i < chosen.size(); ++i) {
		if (chosen.at(i) == city) {
			return true;
		}
	}

	return false;
}

bool empty(string city) {
	if (city == "") {
		return true;
	}

	return false;
}

bool is_less(string current_city, string potential_city, map<string, pair<string, int>> distance_from_start) {
	if (distance_from_start[potential_city].second < distance_from_start[current_city].second) {
		return true;
	}

	return false;
}

string pick_smallest(map<string, pair<string, int>> distance_from_start, vector<string> chosen, string end) {
	map<string, pair<string, int>>::iterator it = distance_from_start.begin();
	string current_smallest_city = "";
	int current_smallest_distance = INT_MAX;

	for (it; it != distance_from_start.end(); ++it) {
		if ((is_visited(it->first, chosen) == false) && (it->first != end)) {
			if (it->second.second < current_smallest_distance) {
				current_smallest_city = it->first;
				current_smallest_distance = it->second.second;
			}
		}
	}

	return current_smallest_city;
}

string backtrack(map<string, pair<string, int>> distance_from_start, string start, string end) {
	vector<string> total_path = {}; 
	string output = "Your total path is: ";
	int total_distance = distance_from_start[end].second;
	total_path.push_back(end);
	string current_city = end;

	while (total_path.back() != start) {
		current_city = distance_from_start[current_city].first;
		total_path.push_back(current_city);
	}

	for (int i = total_path.size() - 1; i >= 1; --i) {
		output += total_path.at(i) + "->";
	}
	output += total_path.at(0) + "\n";
	output += "The total distance of this trip is: " + to_string(total_distance) + "\n";
	return output;
}

string dijkstra(string start, string end, map<string, list<pair<string, int>>> distances) {
	vector<string> chosen = {};
	map<string, pair<string, int>> distance_from_start;

	//this iterates through the cities and sets their total distances from the starting point to infinity (represented by -1)
	distance_from_start["STL"] = make_pair("", INT_MAX);
	distance_from_start["NY"] = make_pair("", INT_MAX);
	distance_from_start["MA"] = make_pair("", INT_MAX);
	distance_from_start["CR"] = make_pair("", INT_MAX);
	distance_from_start["KC"] = make_pair("", INT_MAX);
	distance_from_start["LA"] = make_pair("", INT_MAX);
	distance_from_start["MN"] = make_pair("", INT_MAX);

	//this sets the starting city to itself with a distance of 0
	distance_from_start[start] = make_pair(start, 0);
	chosen.push_back(start);
	string current_city = start;

	//this iterates through the city distances and selects the one closest to the starting point, adds it to the visited list, and updates the distance_from_start for each city

	//while the vector size is less than 6
	for (int i = 0; i < 6; ++i) {
		//the end of chosen
		current_city = chosen[chosen.size() - 1];
		int current_city_distance = distance_from_start[current_city].second;

		//the list related to the current city
		list<pair<string, int>> current_list = distances[current_city];

		//iterator for this list
		list<pair<string, int>>::iterator it = current_list.begin();

		//beginning of undo

		//iterate through the potential destination cities and update/add distances
		for (it; it != current_list.end(); ++it) {
			string next_city = it->first;
			int next_city_distance = it->second;

			//if the spot for the city in distance_from_start is not yet populated
			if (empty(distance_from_start[next_city].first)) {
				distance_from_start[next_city].first = current_city;
				distance_from_start[next_city].second = next_city_distance + current_city_distance;
			}

			//if it is populated, determine if the new value could be better
			else {
				if (distance_from_start[next_city].second > (current_city_distance + next_city_distance)) { 
					distance_from_start[next_city].first = current_city;
					distance_from_start[next_city].second = (current_city_distance + next_city_distance);
				}
			}
			
		}

		current_city = pick_smallest(distance_from_start, chosen, end);
		chosen.push_back(current_city);
	}

	string output = backtrack(distance_from_start, start, end);
	return output;
}

int main() {
	//initialise the starting cities in a paralell array
	string cities[7] = { "STL", "NY", "MA", "CR", "KC", "LA", "MN" };

	//create a list of all cities consisting of all cities they're attached to and the distances between them 
	list<pair<string, int>> STL = { make_pair("NY", 12), make_pair("MN", 9), make_pair("KC", 2), make_pair("CR", 10) };
	list<pair<string, int>> NY = { make_pair("STL", 12), make_pair("MN" ,3), make_pair("MA", 5) };
	list<pair<string, int>> MA = { make_pair("NY", 5), make_pair("LA", 7), make_pair("CR", 6) };
	list<pair<string, int>> CR = { make_pair("STL", 10), make_pair("MA", 6), make_pair("KC", 11) };
	list<pair<string, int>> KC = { make_pair("LA", 13), make_pair("CR", 11), make_pair("STL", 2) };
	list<pair<string, int>> LA = { make_pair("MN", 4), make_pair("MA", 7), make_pair("KC", 13) };
	list<pair<string, int>> MN = { make_pair("LA", 4), make_pair("STL", 9), make_pair("NY", 3) };

	//add each city into the parallel array city distances for easy lookup
	list<pair<string, int>> city_distances[7] = { STL, NY, MA, CR, KC, LA, MN };

	//add each city into map 
	map<string, list<pair<string, int>>> city_distances_map;
	for (int i = 0; i < 7; ++i) {
		city_distances_map[cities[i]] = city_distances[i];
	}

	string starting_city, ending_city;
	cout << "What is your starting city? (STL, NY, MA, CR, KC, LA, MN) ==> ";
	cin >> starting_city;
	cout << "What is your ending city? (STL, NY, MA, CR, KC, LA, MN) ==> ";
	cin >> ending_city;

	string shortest_path = dijkstra(starting_city, ending_city, city_distances_map);
	
	cout << shortest_path; 

	system("PAUSE");
	return 0;
}
