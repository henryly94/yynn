#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <cstdio>
#include "nn.h"

using namespace std;

neuralnetwork::matrix::matrix(int m, int n){
	time_t timer;
  	struct tm y2k = {0};
	_mat.resize(m);
    normal_distribution<double> u(0, 1);
	for (int i=0; i<m; i++){
		_mat[i].resize(n);
		for (int j=0; j<n; j++){
			time(&timer);
			int seconds = (int)difftime(timer,mktime(&y2k));	
			default_random_engine e((seconds % 20171030) + i*n+j);
			_mat[i][j] = u(e);
		}
	}
	_m = m;
	_n = n;
}

void neuralnetwork::matrix::print(){
	cout << "Hello World!" << endl;
	for (int i=0; i<_m; i++){
		for (int j=0; j<_n; j++){
			cout << _mat[i][j] << ' ';
		}
		cout << endl;
	}
}

void neuralnetwork::assign(int i, int j, int value){
	if (i < 0 || i >= _m || j < 0 || j >= _n){
		throw "Wrong Index";
	}
	_mat[i][j] = value;
}

neuralnetwork::matrix &operator=(const neuralnetwork::matrix &a){
		
}

neuralnetwork::matrix neuralnetwork::dot(neuralnetwork::matrix& a){
	if (_n != a._m){
		char *s = new char[1024];
		sprintf(s, "Invalid dot operation between (%d, %d) and (%d, %d)", _m, _n, a._m, a._n);
		throw s;
	}
	neuralnetwork::matrix ret_mat(_m, a._n);
	for (int i=0; i< _m; i++){
		for (int j=0; j<a._n; j++){
			double tmp = 0;
			for(int k=0; k<_n; k++){
				tmp += _mat[i][k] * a._mat[k][j];	
			}
			ret_mat.assign(i, j, tmp);
		}
	}
	return ret_mat;
}


int main(){
	neuralnetwork::matrix mat(3, 3);
	mat.print();
	return 0;
}
