#include "interpolant.h"
#include "dataframe.h"
#include <iostream>
#include <string>
#include <math.h>
using namespace std;


int main(){
	vector<string> col_names = {"seconds", "latitude", "longitude", "altitude"};

	string filename = "data.csv";
	
	// create our csv
	Dataframe data_table(filename);

	vector<pair<string, vector<long double>>> my_df = data_table.getData();

	// we want to interpolate velocity vs time, so we collect those columns
	vector<long double> velocities = data_table.getVelocities();
	vector<long double> time = data_table.getTime();	
	
	/*
	vector<long double> lat = my_df[1].second;
	vector<long double> lon = my_df[2].second;
	vector<long double> alt = my_df[3].second;
	*/


	vector<pair<long double, long double>> points;

	for (int i = 0; i < velocities.size(); i++){
		points.push_back(pair<long double, long double>(time[i], velocities[i]));
	}

	interpolant myInterpolant(points); //we got our interpolant created



	long double first_val = myInterpolant.findValue(1532334000);
	long double second_val = myInterpolant.findValue(1532335268);

	cout << "here is the velocity at t = 1532334000: v = ";
	cout <<first_val <<endl;
	
	cout << "here is the velocity at t = 1532335268: v = ";
	cout << second_val << endl;
	

	return 0;
}


