#include <iostream>

struct v // vector
{
	double x, y, z;
};


std::ostream &operator<< (std::ostream &output, const v &vec)
{
	output << vec.x << " " << vec.y << " " << vec.z;
	return output;
}


v add (v &v1, v &v2) // addition
{
	v result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}


v subtr (v &v1, v &v2) // subtraction
{
	v result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;	
}


v mult (double n, v &vec) // multiplication by a constant
{
	v result;
	result.x = n * vec.x;
	result.y = n * vec.y;
	result.z = n * vec.z;
	return result;
}


double dot (v &v1, v &v2) // dot product
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


v cross (v &v1, v&v2) // cross product
{
	v result;
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}
