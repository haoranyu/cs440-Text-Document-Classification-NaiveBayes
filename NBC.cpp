#include "NBC.h"


void NBC::Train( vector< vector<string> > & traindata, vector<int> & ltrain)
{
	int train_size = ltrain.size();
	int train_cate_size[NUM_CLASS];

	for(int i=0; i < NUM_CLASS; i++)
		train_cate_size[i] = 0;
	

	for (vector<int>::iterator it = ltrain.begin() ; it != ltrain.end(); ++it){
		train_cate_size[*it]++;
	}

	for(int i = 0; i < NUM_CLASS; i++){
		this->prior[i] = (double)train_cate_size[i]/(double)train_size;
	}

	for (vector<int>::iterator it = ltrain.begin() ; it != ltrain.end(); ++it){
		train_cate_size[*it]++;
	}


	for (std::map<string, vector<int> >::iterator it = features.begin(); it != features.end(); ++it){
		vector<double> init;
		for (int i =0; i < NUM_CLASS; i++) {	
			init.push_back(0);
		}
		pTable.insert ( std::pair<string,vector<double> >(it->first, init) );
	}

	for (std::map<string, vector<double> >::iterator it = pTable.begin(); it != pTable.end(); ++it){
		for(int i = 0; i < NUM_CLASS; i++) {	
			(it->second).at(i) = (double)(features[it->first].at(i) + 1) / (double)(features.size() + numw_inclass[i]);
		}
	}
}

void NBC::Test( vector< vector<string> > & testdata) {
	int test_size = testdata.size();
	int hit_count[8] = {0,0,0,0,0,0,0,0};
	int real_count[8] = {0,0,0,0,0,0,0,0};
	int confusion_matrix[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};

//special code follows. very bad code . just for deadline
	double confusion_matrix2[8][8] = {{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}};
//special ends
	
	for (int s = 0; s < test_size; s++) {
		int plabel = test(testdata[s]);
		this->pltest.push_back(plabel);
		real_count[ltest.at(s)]++;
		if(plabel == ltest.at(s)){
			hit_count[ltest.at(s)]++;
		}
		confusion_matrix[ltest.at(s)][plabel]++;
		confusion_matrix2[ltest.at(s)][plabel] += 1.0;
	}
	
	for(int i = 0; i < 8; i ++){
		cout<<"The classification rate for class "<<i<<" is "<<(double)hit_count[i]/(double)real_count[i]<<endl;
	}

	int rowSum[8] = {0,0,0,0,0,0,0,0};

	for(int i = 0; i < 8; i ++){
		for(int j = 0; j < 8; j ++){
			rowSum[i] += confusion_matrix[i][j];
		}
		cout<<endl;
	}

	cout<<"The confusion matrix:"<<endl;
	for(int i = 0; i < 8; i ++){
		for(int j = 0; j < 8; j ++){
			cout<<confusion_matrix[i][j]<<"\t";
		}
		cout<<endl;
	}

//special code follows. very bad code . just for deadline
	for(int i = 0; i < 8; i ++){
		for(int j = 0; j < 8; j ++){
			confusion_matrix2[i][j] = (double)confusion_matrix[i][j]/(double)rowSum[i];
		}
		cout<<endl;
	}

	for (std::map<string, vector<double> >::iterator it = pTable.begin(); it != pTable.end(); ++it){
		logodds1.insert ( std::pair<string, double >(it->first, log(it->second.at(1)) - log(it->second.at(5))  ));
		logodds2.insert ( std::pair<string, double >(it->first, log(it->second.at(4)) - log(it->second.at(5))  ));
		logodds3.insert ( std::pair<string, double >(it->first, log(it->second.at(4)) - log(it->second.at(0))  ));
		logodds4.insert ( std::pair<string, double >(it->first, log(it->second.at(7)) - log(it->second.at(1))  ));
	}
//special ends
}

int NBC::test(const vector<string> &sample) {

    vector<double> posterior;
	double P[NUM_CLASS];
	for (int i = 0 ; i < NUM_CLASS; ++i){
		P[i] = log(this->prior[i]);
	}
    
	for(int f = 0; f < sample.size(); ++f) {
		for (int i = 0 ; i < NUM_CLASS; ++i){
			double pUnseen = (1.0f/(double)(features.size() + numw_inclass[i]));
			double pp;
			if(pTable.count(sample[f]) > 0){
				pp = this->pTable[sample[f]].at(i);
			}
			else{
				pp = pUnseen;
			}
			P[i] += log(pp);
		}
	}
	double max_num = P[0];
	int max_idx = 0;
	for (int i = 1 ; i < NUM_CLASS; ++i){
		if(max_num < P[i]){
			max_num = P[i];
			max_idx = i;
		}
	}
	return max_idx; 
}
