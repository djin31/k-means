#include <fstream>
#include <climits>
#include <iostream>     
#include <algorithm>    
#include <vector>       
#include <ctime>        
#include <cstdlib>
using namespace std;

struct coord{
	float x,y,z;
};


vector<coord> dataset;
vector<vector<coord>> clusters;

int k=0;
int n=0;
int max_iter = 1000;

int reinit_param = 10;

float max_x = INT_MIN, max_y = INT_MIN, max_z = INT_MIN;
float min_x = INT_MAX, min_y = INT_MAX, min_z = INT_MAX;

int get_distance(coord a, coord b){
	return ((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z));
}

void set_min_max(){
	for (int c=0; c<n; c++){
		min_x = min(dataset[c].x, min_x);
		min_y = min(dataset[c].y, min_y);
		min_z = min(dataset[c].z, min_z);

		max_x = max(max_x, dataset[c].x);
		max_y = max(max_y, dataset[c].y);
		max_z = max(max_z, dataset[c].z);
	}
}

void k_means(){

	set_min_max();

	// Shuffle dataset and pick initial k points as initial means
	// random_shuffle(dataset.begin(),dataset.end());
	random_shuffle(dataset.begin(), dataset.end());

	int cluster_count[n] = {};
	coord means[n];
	for (int i=0; i<k; i++){
		means[i].x=dataset[i].x;
		means[i].y=dataset[i].y;
		means[i].z=dataset[i].z;
	}

	vector<pair<int,float>> nearest_mean = vector<pair<int,float>>(n);
	float temp_dist, min_dist;
	int min_dist_mean;	

	coord temp_mean;

	cerr<<"Init means are\n";
	for (int m=0;m<k;m++){
		cerr<<m<<" --> "<< means[m].x <<" " <<means[m].y <<" "<< means[m].z<<endl;
	}
	cerr<<endl;

	for (int iter=0; iter<max_iter;iter++){

		// Assign nearest mean to each point
		#pragma omp parallel for schedule(static,250) private(temp_dist, min_dist, min_dist_mean)		
		for (int p=0;p<n; p++){			
			min_dist = INT_MAX;
			min_dist_mean = -1;
			for(int m=0; m<k; m++){
				temp_dist = get_distance(dataset[p],means[m]);
				if (temp_dist<min_dist){
					min_dist = temp_dist;
					min_dist_mean = m;
				}
			} 
			nearest_mean[p].first = min_dist_mean;
			nearest_mean[p].second = min_dist;
		}

		//  Calculate new means
		for(int m=0; m<k; m++){
			means[m].x = 0;
			means[m].y = 0;
			means[m].z = 0;
		}

		// This should not be parallelised ideally since it is critical section
		// #pragma omp parallel for schedule(static,250) 
		for (int p = 0; p<n; p++){
			cluster_count[nearest_mean[p].first]++;
			means[nearest_mean[p].first].x +=dataset[p].x;
			means[nearest_mean[p].first].y +=dataset[p].y;
			means[nearest_mean[p].first].z +=dataset[p].z;
		}	

		for (int m=0; m<k; m++){
			if (cluster_count[m]!=0){
				means[m].x/=cluster_count[m];
				means[m].y/=cluster_count[m];
				means[m].z/=cluster_count[m];
			}
			else{
				if (1){
					int max_dist_point;
					float max_dist=-1;
					for (int i=0;i<n;i++){
						if (nearest_mean[i].second>max_dist){
							max_dist_point = i;
							max_dist = nearest_mean[i].second;
						}
					}
					means[m] = dataset[max_dist_point];
					nearest_mean[max_dist_point].second = 0;
					nearest_mean[max_dist_point].first  = m;
				}
				else{
					means[m].y = rand()%(int)(max_y-min_y) + min_y;
					means[m].x = rand()%(int)(max_x-min_x) + min_x;
					means[m].z = rand()%(int)(max_z-min_z) + min_z;
				}
			}
		}
		// cerr<<"Cluster sizes are\n";
		for (int c=0; c<k; c++){
			if (cluster_count[c]==0)
				cerr<<"Found zero size cluster on iter"<<iter<<endl;
			cluster_count[c]=0;
		}
		// cerr<<endl;
	}

	clusters = vector<vector<coord>>(k);
	for (int p=0; p<n; p++){
		clusters[nearest_mean[p].first].push_back(dataset[p]);
	}
	
}

int main(int argc, char const *argv[])
{	
	// srand(time(NULL));
	srand(3120);
	ifstream data;
	data.open(argv[1]);
	data>>n>>k;
	coord point;

	dataset = vector<coord>(n);
	int r=0;
	while (r<n){
		data>>point.x>>point.y>>point.z;
		dataset[r]=point;
		r++;
	}

	k_means();

	cerr<<"Cluster sizes are\n";
	for (auto c: clusters){
		cerr<<c.size()<<" ";
	}
	cerr<<endl;
	for (auto c: clusters){
		for (auto p:c){
			cout<<p.x<<" "<<p.y<<" "<<p.z<<endl;
		}
		cout<<endl;
	}

	return 0;
}