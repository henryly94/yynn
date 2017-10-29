#ifndef YYNN_NN_H_
#define YYNN_NN_H_
#include <iostream>
#include <vector>

using namespace std;

namespace neuralnetwork{
	
	class matrix{
	public:
		matrix &operator=(const matrix &a);
		matrix(int m, int n);
		void print();
		int _m, _n;
		vector<vector<double> > _mat;	
		matrix dot(matrix& a);	
		void assign(int i, int j, int value);
	};

};


#endif //YYNN_NN_H_
