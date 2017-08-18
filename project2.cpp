#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Vtop.h"
#include "Vtop__Syms.h"
using namespace std;

int main () {
  int x;
  int branch_not_cov=0; int vectors = 0;
  Vtop* circuit = new Vtop();
  string line;
  float coverage; float coverage2;
  
  ifstream myfile ("lev_vec.vec");
  ofstream myfile3 ("output_max_FC.vec");

  //number of inputs added to output file	
  getline(myfile, line);
  int n= atoi(line.c_str());
  myfile3 << n <<endl; 
  
  //1st set_vector sent to output file
  getline(myfile, line);
  string set_vector = line;
  myfile3 << set_vector << endl; 
  
  vector<bool> bitset(n, false);
  vector< vector<bool> > vectorset; //vectorset will be used for flagging 
  
  circuit->sim_init();

  while (line!="END"){
	 
char *fileName = (char*)line.c_str();
for(int s=0;s<n;s++)
{ if(fileName[s]=='0') {
	bitset[s]= false; }
else{ bitset[s]=true;}	}

vectorset.push_back(bitset); // saving all the vectors in vectorset
circuit-> set_input_with_reset(bitset);
circuit-> eval();
circuit-> toggle_clock();
circuit-> eval();
circuit->toggle_clock();
getline(myfile, line);
vectors++;
}
	int cov_pts=circuit->num_branch_cov_pts();
	int coverage_pts = cov_pts;
	
	for(int branch=0;branch<cov_pts;branch++){
		x=circuit->get_cov_pt_value(branch)	;
			if(x==0) {branch_not_cov++; }
			}
	
	coverage=(float)(((float)cov_pts-(float)branch_not_cov)/(float)cov_pts)*(float)100;
    cout << "Branch coverage of the circuit for lev_vec.vec in % = " << coverage << endl;
    circuit->clear_coverage();
    vector<bool> array((vectors), false);// array = false false false
    
    
    for (int b = 1; b< (vectors -1); b++){ 
		circuit->sim_init();
		circuit->clear_coverage();
		for (int a =0; a<vectors; a++){
				if ((a==b) || (array[a]==true)) 
				continue;
				else
				{
					circuit-> set_input_with_reset(vectorset[a]);
					circuit-> eval();
					circuit-> toggle_clock();
					circuit-> eval();
					circuit->toggle_clock();
				}
			}
		cov_pts=circuit->num_branch_cov_pts();
		branch_not_cov = 0;
	
	for(int branch=0;branch<cov_pts;branch++){
	x=circuit->get_cov_pt_value(branch)	;
	if(x==0){ branch_not_cov++; } }
	
	coverage2=(float)(((float)cov_pts-(float)branch_not_cov)/(float)cov_pts)*(float)100;
	if (coverage2==coverage){
	array[b] = true;
	}
}
	
	vector< vector<bool> > compacted_vectorset; 
	//compacted_vectorset, cannot contain all the compacted vectors needed
	//so we need to create compacted vectorset which will have some compacted vectors
	//adding random vectors to this compacted_vectorset
	vector< vector<bool> > compacted_vectorset2;
	
	int random; srand(time(0));
	
	//creating the vectorset of compacted vectors
	//Counting the number of compacted vectors
	
			int compacted_vectors = 0;
		
			for (int k =1; k<(vectors-1); k++){
				//adding the compacted vectors found 
				//this vectorset is not enough
				if (array[k]==false){
					compacted_vectorset.push_back(vectorset[k]);
					compacted_vectors++;
					//cout << compacted_vectorset.size();
					}
				}
				
				//cout << "compacted_vectorset.size() = " << compacted_vectorset.size() << endl;
				
				vector<bool> bitset_random(n, true);
				srand(time(0));
				int random_temp;
				//adding vectors into the file the compacted vectorset, count = vectors
				
				for ( int i = 0; i<vectors;i++){
					//adding more random vectors to the compacted set
					for (int j =0; j<n ; j++){
						random_temp = rand()%2;
						if (random_temp == 1)
						{
						bitset_random[j] = true;
						}
						else{
						bitset_random[j] = false;
						}
					}
					if (bitset_random != vectorset[0]){//making sure not adding the set vector to the compacted vectorset
					compacted_vectorset.push_back(bitset_random);
				}
			}
				
				
				
		//Generating test set to improve the coverage, only the vectors from compacted test set will be used
		
		circuit->sim_init();
		circuit->clear_coverage();
		
		//Passing the first vector
		circuit-> set_input_with_reset(vectorset[0]);
		circuit-> eval();
		circuit-> toggle_clock();
		circuit-> eval();
		circuit->toggle_clock();
		
		//Passing all the random vectors now
		for (int k =0; k<vectors*3; k++){
		random = rand()% (compacted_vectors); // random = 1 to 19, as first and last vectors are not needed
		compacted_vectorset2.push_back(compacted_vectorset[random]);
		//vectorset2 will be compacted to get the set of vectors which gives maximum coverage
		circuit-> set_input_with_reset(compacted_vectorset[random]);
		circuit-> eval();
		circuit-> toggle_clock();
		circuit-> eval();
		circuit->toggle_clock();
		}
		
		//Passing the last vector
		circuit-> set_input_with_reset(vectorset[0]);
		circuit-> eval();
		circuit-> toggle_clock();
		circuit-> eval();
		circuit->toggle_clock();
		
		//Finding the new coverage after using all the compacted vectors
		cov_pts=circuit->num_branch_cov_pts();
		branch_not_cov = 0;
		for(int branch=0;branch<cov_pts;branch++){
			x=circuit->get_cov_pt_value(branch)	;
			if(x==0){ branch_not_cov++; } }
			
		float new_coverage;
		new_coverage=(float)(((float)cov_pts-(float)branch_not_cov)/(float)cov_pts)*(float)100;
		cout << "Branch coverage of the circuit after optimization in % = " << new_coverage << endl;
		
		int length = compacted_vectorset2.size();
		vector<bool> array2((length), false);
		//cout << "compacted_vectorset2.size() = " << length << endl;
		
		if((new_coverage > coverage) || (new_coverage == coverage)){
			float temp_coverage;
			//compacting the vectors from vectorset2
			for (int b = 0; b< (length); b++){ 
		
				circuit->sim_init();
				circuit->clear_coverage();
				
				//set
				circuit-> set_input_with_reset(vectorset[0]);
				circuit-> eval();
				circuit-> toggle_clock();
				circuit-> eval();
				circuit->toggle_clock();

			for (int a =0; a<(length); a++){
				if ((a==b) || (array2[a]==true)) 
				continue;
				else
				{
					circuit-> set_input_with_reset(compacted_vectorset2[a]);
					circuit-> eval();
					circuit-> toggle_clock();
					circuit-> eval();
					circuit->toggle_clock();
				}
			}
			
			//reset
			circuit-> set_input_with_reset(vectorset[0]); // set and reset vectors are same
			circuit-> eval();
			circuit-> toggle_clock();
			circuit-> eval();
			circuit->toggle_clock();
			
			cov_pts=circuit->num_branch_cov_pts();
			branch_not_cov = 0;
	
			for(int branch=0;branch<cov_pts;branch++){
			x=circuit->get_cov_pt_value(branch)	;
			if(x==0){ branch_not_cov++; } }
	
	temp_coverage=(float)(((float)cov_pts-(float)branch_not_cov)/(float)cov_pts)*(float)100;
	
	if (temp_coverage==new_coverage){
	array2[b] = true;
	}
}

for (int m =0;m<length;m++){
		if (array2[m]==false){
			for (int k=0;k<n;k++){
				myfile3 << compacted_vectorset2[m][k]; // compacted vectors are added bit by bit to output file
				}
				myfile3<<endl; 
			}
		}
	}
			myfile3 << set_vector << endl; //reset vector sent to output file, set and reset vectors are same
			myfile3 << "END" << endl;	// output file ended with "END"
			cout << endl;
			if (new_coverage==coverage){
				cout << "Please run the program again if the coverage is not increased" << endl;
				cout << "As random function is used, required random vectors may not be generated" << endl;
				cout << "It is also possible that coverage cannot be increased for this circuit" << endl;
	}
				cout << endl;
				cout << "Please open output_max_FC.vec to find the test set which gives highest coverage" << endl; 
	
			

}



