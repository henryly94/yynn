#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cmath>

#include "matrix.h"

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

neuralnetwork::matrix::matrix(const neuralnetwork::matrix& a){
	//cout << "Copy Construct Function" << endl;
	_m = a._m;
	_n = a._n;
	_mat.resize(_m);
	for (int i=0; i<_m; i++){
		_mat[i].resize(_n);
		for (int j=0; j<_n; j++){
			_mat[i][j] = a._mat[i][j];
		}
	}
}

neuralnetwork::matrix::matrix(const vector<double> v){
	_m = 1;
	_n = v.size();
	_mat.resize(1);
	_mat[0].resize(_n);
	for(int i=0; i<_n; i++){
		_mat[0][i] = v[i];
	}
}

neuralnetwork::matrix neuralnetwork::matrix::identity(int m, int n){
	matrix ret_mat(m, n);
	for(int i=0; i<m; i++){
		for (int j=0; j<n; j++){
			ret_mat.assign(i, j, 1.0);
		}
	}
	return ret_mat;
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

void neuralnetwork::matrix::assign(int i, int j, double value){
	if (i < 0 || i >= _m || j < 0 || j >= _n){
		cout << "Wrong Index" << endl;
		throw "Wrong Index";
	}
	_mat[i][j] = value;
}

neuralnetwork::matrix neuralnetwork::matrix::sigmoid(const neuralnetwork::matrix& a){
	neuralnetwork::matrix ret_mat(a);
	for (int i=0; i<a._m ;i++){
		for (int j=0; j<a._n; j++){
			ret_mat.assign(i, j, 1/(1+exp(-a._mat[i][j])));
		}
	}
	return ret_mat;
}

void neuralnetwork::matrix::operator=(const neuralnetwork::matrix& a){
	if (_m != a._m || _n !=a._n){
		cout << _m << ", " << _n <<" : "<< a._m << ", " << a._n << endl;
		throw "Shape can't match";
	}
	for (int i=0; i<_m; i++){
		for (int j=0; j<_n; j++){
			_mat[i][j] = a._mat[i][j];
		}
	}
}

neuralnetwork::matrix neuralnetwork::matrix::dot(const neuralnetwork::matrix& a){
	if (_n != a._m){
		char *s = new char[1024];
		sprintf(s, "Invalid dot operation between (%d, %d) and (%d, %d)", _m, _n, a._m, a._n);
		cout << s << endl;
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

neuralnetwork::matrix neuralnetwork::matrix::T(){
	neuralnetwork::matrix ret_mat(_n, _m);
	for (int i=0; i<_m; i++){
		for (int j=0; j<_n; j++){
			ret_mat.assign(j, i, _mat[i][j]);
		}
	}
	return ret_mat;
}

neuralnetwork::matrix neuralnetwork::matrix::operator+(const neuralnetwork::matrix& a){
	if (!(_m == a._m && _n % a._n == 0) && !(_n == a._n && _m % a._m == 0)){
		char *s = new char[1024];
		sprintf(s, "Invalid '+' operation between (%d, %d) and (%d, %d)", _m, _n, a._m, a._n);
		cout << s << endl;
		throw s;
	}
	neuralnetwork::matrix ret_mat(*this);
	for(int i=0; i<_m; i++){
		for(int j=0; j<_n; j++){
			ret_mat.assign(i, j, _mat[i][j] + a._mat[i%a._m][j%a._n]);
		}
	}
	return ret_mat;
}

neuralnetwork::matrix neuralnetwork::matrix::operator-(const neuralnetwork::matrix& a){
	if (!(_m == a._m && _n % a._n == 0) && !(_n == a._n && _m % a._m == 0)){
		char *s = new char[1024];
		sprintf(s, "Invalid '-' operation between (%d, %d) and (%d, %d)", _m, _n, a._m, a._n);
		cout << s << endl;
		throw s;
	}
	neuralnetwork::matrix ret_mat(*this);
	for(int i=0; i<_m; i++){
		for(int j=0; j<_n; j++){
			ret_mat.assign(i, j, _mat[i][j] - a._mat[i%a._m][j%a._n]);
		}
	}
	return ret_mat;
}

neuralnetwork::matrix neuralnetwork::matrix::operator*(const neuralnetwork::matrix& a){
	if (!(_m == a._m && _n % a._n == 0) && !(_n == a._n && _m % a._m == 0)){
		char *s = new char[1024];
		sprintf(s, "Invalid '*' operation between (%d, %d) and (%d, %d)", _m, _n, a._m, a._n);
		cout << s << endl;
		throw s;
	}
	neuralnetwork::matrix ret_mat(*this);
	for(int i=0; i<_m; i++){
		for(int j=0; j<_n; j++){
			ret_mat.assign(i, j, _mat[i][j] * a._mat[i%a._m][j%a._n]);
		}
	}
	return ret_mat;

}
neuralnetwork::matrix neuralnetwork::matrix::operator*(const double a){	
	neuralnetwork::matrix ret_mat(*this);
	for(int i=0; i<_m; i++){
		for(int j=0; j<_n; j++){
			ret_mat.assign(i, j, a*_mat[i][j]);
		}
	}
	return ret_mat;

}
/*
int main(){
	neuralnetwork::matrix mat1(1, 3);
   	neuralnetwork::matrix mat2(3, 1);
	neuralnetwork::matrix mat3 = mat1.dot(mat2);
	neuralnetwork::matrix mat4 = mat2.dot(mat1);
	neuralnetwork::matrix mat5 = mat2.dot(mat2.T());
	mat1.print();
	mat2.print();
	mat3.print();
	mat4.print();
	mat5.print();
	neuralnetwork::matrix mat6(mat4 + mat5), mat7(mat4 - mat2), mat8(mat4 * mat1);
	mat6.print();
	mat7.print();
	mat8.print();
	return 0;
}
*/
