#ifndef RANDOM_FOREST_COMMON_H
#define RANDOM_FOREST_COMMON_H

#include <vector>
#include <string>
#include <sstream>

#include <Eigen/Core>

#include <DataProvider/Types.h>

namespace RandomForest {

typedef Eigen::RowVectorXf RowVector;

typedef long long NodeIdType;

int CountCommas(const std::string& s);

template<typename T>
std::vector<T> StringToStdVector(const std::string& line, int n_elements = 0) {
  // if number of elements was not specified, count the commas
  if (n_elements == 0) { n_elements = CountCommas(line) + 1; }
  // fill in the vector
  std::vector<T> vec(n_elements);
  std::stringstream ss(line);
	std::string value;
	for (int el = 0; el < n_elements; ++el) {
		getline(ss, value, ',');
		istringstream(value) >> vec[el];
	}
	return vec;
};

template<typename T>
std::string StdVectorToString(const std::vector<T>& vec) {
  std::ostringstream oss;
  std::vector<T>::const_iterator cit = vec.begin();
  oss << *cit;
  for (; cit != vec.end(); ++cit) {
    oss << "," << *cit;
  }
  return oss.str();
};

// convert between std::vector<float> and std::string and vice versa
RowVector ReadFloatVector(const std::string& line, int size);
EigenMat ReadFloatMatrix(const std::string& line, int height, int width);

// writes Matrix to the specified location as a CSV file
void SerializeMatrix(const EigenMat& data, const std::string& fileName);
} // namespace RandomForest

#endif // RANDOM_FOREST_COMMON_H