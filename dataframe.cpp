#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <sstream>
#include <stdexcept>
#include <math.h>
#include "dataframe.h"

#define PI 3.14159265


using namespace std;

Dataframe::Dataframe(string filename){

	read_file(filename);
		
}

void Dataframe::read_file(string filename){
	
	ifstream myFile(filename);
	
	if(!myFile.is_open()) throw std::runtime_error("Could not open file");

	string line;

	//initialize the header of each column in the dataframe
	vector<string> colNames = {"seconds", "latitude", "longitude", "altitude"};
	for (int i =0; i < colNames.size(); i++){
		_data.push_back({colNames[i], vector<long double>{}});
	}

	long double val;
	while(getline(myFile, line)){
		std::stringstream ss(line);

		int colIdx = 0;

		while(ss >> val){
			_data[colIdx].second.push_back(val);

			if (ss.peek() == ',') ss.ignore();

			colIdx++;
		}

	}
	//close file
	myFile.close();
}


vector<pair<string, vector<long double>>> Dataframe::getData(){
	return _data;
}


/*NOTE TO SELF
 * HERE IS A KEY FOR THE COLUMN NAMES:
 *colNames = {"seconds", "latitude", "longitude", "altitude"};
 *
 *getVelocities() returns a vector containing the velocity values for each point in time.
 *
 */


vector<long double> Dataframe::getVelocities(){
	vector<long double> ret = {0.00}; //initialize ret with its first value as zero. We define the velocity at the starting time as zero.
	//define our constants
	long double a = 6378137.0;
	long double f = 1.0/298.257223563;
	long double b = a*(1.0-f);
	long double e = sqrt((pow(a,2.0) - pow(b,2.0))/pow(b,2.0));

	//storing our values in the columns into vectors. more memory, but cleaner-looking code
	vector<long double> time = _data[0].second;
	vector<long double> lat = _data[1].second;
	vector<long double> lon = _data[2].second;
	vector<long double> h = _data[3].second; //this is the altitude

	vector<long double> X_vec, Y_vec, Z_vec;
	

	//first, we gotta convert each LLA coordinate to ECEF. from there, we compute the change in magnitude of displacement over time.
	for (int j = 0; j < time.size(); j++){
		long double N =  a/sqrt(1 - pow(e, 2.0) * pow((sin(lat[j] * PI/180.0)), 2.0));

		//our coordinates
		long double X = (N + h[j])*cos(lat[j]*PI/180.0)*cos(lon[j]*PI/180.0);
		long double Y = (N + h[j])*cos(lat[j]*PI/180.0)*sin(lon[j]*PI/180.0);
		long double Z = ((pow(b, 2)/ pow(a,2))*N + h[j])*sin(lat[j]*PI/180.0);
		
		X_vec.push_back(X);
		Y_vec.push_back(Y);
		Z_vec.push_back(Z);
		
		if (j >= 1){
			//calculate velocitiy by getting the parameters first
			long double deltaX = X_vec[j] - X_vec[j-1];
			long double deltaY = Y_vec[j] - Y_vec[j-1];
			long double deltaZ = Z_vec[j] - Z_vec[j-1];
			long double dt     = time[j] - time[j-1];//delta t
			
			long double displacement = sqrt(pow(deltaX, 2.0) + pow(deltaY, 2.0) + pow(deltaZ, 2.0));

			long double velocity = displacement/dt;
			ret.push_back(velocity);

		}

	}

	return ret;
}

vector<long double> Dataframe::getTime(){
	return _data[0].second;
}
