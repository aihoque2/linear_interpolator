/*dataframe.h*/

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Dataframe{
	public:
		Dataframe(string filename); //constructor that transforms our dataframe
		void read_file(string filename);
		vector<pair<string, vector<long double>>> getData(); //get the private member variable _data
		vector<long double> getVelocities(); //this function returns our velocity column
		vector<long double> getTime(); //this function returns the our time column



	private:
		vector<pair<string, vector<long double>>> _data;	
};
