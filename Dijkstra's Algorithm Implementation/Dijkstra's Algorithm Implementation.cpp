#include "pch.h"
#include <iostream>
#include <vector> 
#include <cmath>
#include <list>
#include <map>

using namespace std;

bool is_visited(string city, vector<string> chosen) {
	for (int i = 0; i < chosen.size(); ++i) {
		if (chosen.at(i) == city) {
			return true;
		}
	}

	return false;
}

bool is_empty(string city) {
	if (city == NULL) {
		return true;
	}

	return false;
}

bool is_less(string current_city, string potential_city, map<string, pair<string, int>> distance_from_start) {
	if (distance_from_start[potenial_city]->second < distance_from_start[current_city]->second) {
		return true;
	}

	return false;
}

string dijkstra(string start, string end, string cities[], list<pair<string, int>> distances) {
	vector<string> chosen = {};
	map<string, pair<string, int>> distance_from_start;

	//this iterates through the cities and sets their total distances from the starting point to infinity (represented by -1)
	distance_from_start["STL"] = make_pair(NULL, INT_MAX);
	distance_from_start["NY"] = make_pair(NULL, INT_MAX);
	distance_from_start["MA"] = make_pair(NULL, INT_MAX);
	distance_from_start["CR"] = make_pair(NULL, INT_MAX);
	distance_from_start["KC"] = make_pair(NULL, INT_MAX);
	distance_from_start["LA"] = make_pair(NULL, INT_MAX);
	distance_from_start["MN"] = make_pair(NULL, INT_MAX);

	//this sets the starting city to itself with a distance of 0
	distance_from_start[start] = make_pair(start, 0);
	chosen.push_back(start);

	//this iterates through the city distances and selects the one closest to the starting point, adds it to the visited list, and updates the distance_from_start for each city

	//while the vector size is less than 6
	for (int i = 0; i < 6; ++i) {
		//the end of chosen
		string current_city = chosen[chosen.size() - 1];
		int current_city_distance = distance_from_start[current_city]->second;

		//the list related to the current city
		list<pair<string, int>> current_list = distances[chosen];

		//iterator for this list
		list<pair<string, int>>::iterator it = current_list.begin();

		//iterate through the potential destination cities and update/add distances
		for (it; it != current_list.end(); ++it) {
			string next_city = it->first;
			string next_city_distance = it->second;

			//if the spot for the city in distance_from_start is not yet populated
			if (isempty(distance_from_start[next_city]->first)) {
				distance_from_start[next_city]->first = current_city;
				distance_from_start[next_city]->second = next_city_distance;
			}

			//if it is populated, determine if the new value could be better
			else {
				if (distance_from_start[next_city]->second > (current_city_distance + next_city_distance)) {
					distance_from_start[next_city]->first = current_city;
					distance_from_start[next_city]->second = (current_city_distance + next_city_distance);
				}
			}

		}
	}


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
	map<string, pair<string, int>> city_distances_map;
	for (int i = 0; i < 7; ++i) {
		distance_from_start[cities[i]] = city_distances[i];
	}

	string starting_city, ending_city;
	cout << "What is your starting city? (STL, NY, MA, CR, KC, LA, MN) ==> ";
	cin >> starting_city;
	cout << "What is your ending city? (STL, NY, MA, CR, KC, LA, MN) ==> ";
	cin >> ending_city;

	string shortest_path = dijkstra(starting_city, ending_city, city_distances_map);

	
	return 0;
}
