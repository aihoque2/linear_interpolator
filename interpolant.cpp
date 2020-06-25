#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "interpolant.h"
using namespace std;

interpolant::interpolant(const std::vector<std::pair<long double, long double>>& points)
  : _points(points) {
	sort(_points.begin(), _points.end());
	const long double epsilon(1.0E-8);
	
	for (int i=0; i < _points.size(); i++){
		long double deltaX = abs(_points[i].first - _points[i-1].first);
		if (deltaX < epsilon){
			cout <<"error" <<endl;
			throw range_error("error");
		}
	}
}


long double interpolant::findValue(long double x) const {

	auto lessThan = //creating a less than operator (lambda function)
		[](const pair<long double, long double>& point, long double x)
		{ return point.first < x;};

	//find  first table entry greater than/equal to the x
	auto iter = std::lower_bound(_points.cbegin(), _points.cend(), x, lessThan);
	
	if (iter == _points.cend()){ //case if caller value is greater than the greatest value in our data point
		return (_points.cend() - 1) -> second;
	}


	if (iter == _points.cbegin() && x <=_points.cbegin()->first){
		return _points.cbegin()->second;
	}

	//interpolation time
	long double upperX = iter->first;
	long double upperY = iter->second;
	long double lowerX = (iter-1)->first;
	long double lowerY = (iter-1)->second;

	long double deltaY = upperY - lowerY;
	long double deltaX = upperX - lowerX;


	return lowerY + ((x-lowerX)/deltaX) * deltaY;
	

}


