#include "pch.h"
#include <iostream>
#include <vector> 
#include <cmath>
#include <list>
#include <map>

using namespace std;

string dijkstra(string start, string end, string cities[], list<pair<string, int>> distances) {
	string visited = {}; 
	map<string, int> distance_from_start;
	int city_index = 0;

	//this searches through the paralell array and finds the index of the starting city
	for (int i = 0; i < 7; ++i) {
		if (start == cities[i]) {
			city_index = i;
		}
	}

	//this iterates through the cities and sets their total distances from the starting point to infinity (represented by -1)
	distance_from_start["STL"] = -1;
	distance_from_start["NY"] = -1;
	distance_from_start["MA"] = -1;
	distance_from_start["CR"] = -1;
	distance_from_start["KC"] = -1;
	distance_from_start["LA"] = -1;
	distance_from_start["MN"] = -1;

	//this iterates through the city distances and selects the one closest to the starting point, adds it to the visited list, and updates the distance_from_start for each city
	for (int i = 0; i < 7; ++i) {
		
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

	string starting_city, ending_city;
	cout << "What is your starting city? (STL, NY, MA, CR, KC, LA, MN) ==> ";
	cin >> starting_city;
	cout << "What is your ending city? (STL, NY, MA, CR, KC, LA, MN) ==> ";
	cin >> ending_city;

	string shortest_path = dijkstra(starting_city, ending_city, cities, city_distances);

	
	return 0;
}
