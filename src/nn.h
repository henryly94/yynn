#ifndef YYNN_NN_H_
#define YYNN_NN_H_

#include "matrix.h"
#include <vector>

using std::vector;

typedef double (*func)(vector<double>, vector<double>);

namespace neuralnetwork{


	class neuralnetwork{
	private:
		double _eta;
		int _input_size, _output_size;
		int _layer;
		vector<int> layer_info;
		vector<matrix> _w;
		vector<matrix> _b;
		
		vector<matrix> _a;
		vector<matrix> _z;
	public:
		neuralnetwork(vector<int> K_l, double eta);
		~neuralnetwork();
		void train_one_sample(vector<double> x, vector<double> y);
		void train(vector<vector<double> > x, vector<vector<double> > y);
		void evaluate(vector<vector<double> > x, vector<vector<double> > y);
		vector<double> forward(vector<double> x);	
		void set_eta(double e);
		
	};

};

#endif //YYNN_NN_H_
