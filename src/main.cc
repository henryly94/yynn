#include <iostream>
#include <fstream>
#include <cstring>
#include "nn.h"

using namespace std;

int main(int argc, char** argv){
	/*	
	neuralnetwork::matrix mat(3, 5);
	mat.print();
	neuralnetwork::matrix mat2(neuralnetwork::matrix::sigmoid(mat));
	mat2.print();
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
	*/
	int k = atoi(argv[1]);
	int batch = atoi(argv[2]);
	vector<int> k_l{1, k, 1};
	neuralnetwork::neuralnetwork nn(k_l, 0.02);
	ifstream in;
	in.open("data.txt");
	double x, y;
	vector<vector<double> > X, Y;
	while (in >> x >> y){
		X.push_back(vector<double>{x});
		Y.push_back(vector<double>{y});
	}
	for (int i=0; i<batch; i++){
		nn.train(X, Y);
		cout << i << "      "<< endl;	
	}
	nn.evaluate(X, Y);
	return 0;
}
