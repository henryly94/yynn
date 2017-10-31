#include <iostream>
#include <fstream>
#include "nn.h"

using namespace std;

typedef double (*func)(vector<double>, vector<double>);

double loss_1(vector<double> a, vector<double> b){
	if (a.size() != b.size()) {
		cout << "Wrong Size at Loss_1" << endl;
		return 10000.0;
	}
	return a[0] - b[0];
}

neuralnetwork::neuralnetwork::neuralnetwork(vector<int> K_l, double eta){
	int s = K_l.size();
	if (s <= 1) throw "Too few layers";
	if (eta <= 0) throw "Invalid learning rate!";
	_layer = s;
	layer_info = K_l;
	_input_size = K_l.front();
	_output_size = K_l.back();
	for(int i=0; i<s-1; i++){
		_w.push_back(matrix(K_l[i], K_l[i+1]));
		_w.back().print();
		_b.push_back(matrix(1, K_l[i+1]));
		_a.push_back(matrix(1, K_l[i+1]));
		_z.push_back(matrix(1, K_l[i+1]));
	}	
	_eta = eta;
};

vector<double> neuralnetwork::neuralnetwork::forward(vector<double> x){
	if (x.size() != _input_size) throw "Wrong Data Size";
	matrix mat_x(x);

	_a[0] = mat_x.dot(_w[0]) + _b[0];
	_z[0] = matrix::sigmoid(_a[0]);
	for (int i=1; i<_layer-1; i++){
		_a[i] = _z[i-1].dot(_w[i]) + _b[i];
		_z[i] = matrix::sigmoid(_a[i]);
	}
	return vector<double>(_z.back()._mat[0]);
}

void neuralnetwork::neuralnetwork::train_one_sample(vector<double> x, vector<double> y){
	if (x.size() != _input_size) throw "Wrong Data Size";
	if (y.size() != _output_size) throw "Wrong Label Size";
	
	forward(x);

	matrix mat_x(x), mat_y(y);

	matrix* delta = new matrix(mat_y - _z[_layer-2]);
	for(int i=_layer-2; i>0; i--){
		matrix da(_b[i]);
		da = (*delta) * (_z[i] * (matrix::identity(1, layer_info[i+1]) - _z[i]));
		delete delta;
		delta = new matrix(da.dot(_w[i].T()));
		_w[i] = _w[i] + (_z[i-1].T().dot(da)) * _eta;
		_b[i] = _b[i] + da * _eta;
	}
	matrix da((*delta) * (_z[0] * (matrix::identity(1, layer_info[1]) - _z[0])));
	_w[0] = _w[0] + (da * mat_x) * _eta;
	_b[0] = _b[0] + (da) * _eta;
}

void neuralnetwork::neuralnetwork::train(vector<vector<double> > x, vector<vector<double> > y){
	if(x.size() != y.size())return;
	for(int i=0; i<x.size(); i++){
		cout << (double) i / x.size() << '\r';
		train_one_sample(x[i], y[i]);
	}
}
void neuralnetwork::neuralnetwork::evaluate(vector<vector<double> > x, vector<vector<double> > y){
	vector<double> ret;
	for (int i=0; i<x.size(); i++){
		ret.push_back(forward(x[i])[0]);
	}
	ofstream out;
	out.open("result.txt");
	for(double each : ret){
		out << each << endl;	
	}
	out.close();	
}
		
neuralnetwork::neuralnetwork::~neuralnetwork(){

}
