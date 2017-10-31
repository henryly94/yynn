#ifndef YYNN_MATRIX_H_
#define YYNN_MATRIX_H_
#include <iostream>
#include <vector>

using namespace std;

namespace neuralnetwork{
	
	class matrix{
	public:
		int _m, _n;
		vector<vector<double> > _mat;	
		
		matrix(int m, int n);
		matrix(const vector<double> v);
		matrix(const matrix& a);
		matrix(matrix&& a):_mat(move(a._mat)), _m(a._m), _n(a._n){};
		void operator=(const matrix &a);
		void print();
		matrix dot(const matrix& a);
		matrix T();
		matrix operator+(const matrix& a);	
		matrix operator-(const matrix& a);	
		matrix operator*(const matrix& a);
		matrix operator*(const double a);
		static matrix sigmoid(const matrix& a);
		static matrix identity(int m, int n);
		void assign(int i, int j, double value);
	};

};


#endif //YYNN_MATRIX_H_
