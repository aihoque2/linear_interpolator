/*interpolant.h*/
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <algorithm>
#include <stdexcept>

/*this file here contains the interpolant() class
 *this class creates the object to hold our interpolating 
 function
 *this will take time as a function and return velocity as an input.
 * */


using namespace std;


class interpolant{

	public:
	//this is for my interpolation function
	
		interpolant(const vector<pair<long double, long double>>& points);//constructor	
		
		long double findValue(long double x) const; //calculate our y given x


	private:
		vector<pair<long double, long double>> _points;



};


