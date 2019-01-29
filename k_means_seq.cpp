#include <bits/stdc++.h>
using namespace std;

struct coord{
	float x,y,z;
};

vector<coord> dataset = vector<coord>();

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
	for (coord c: dataset){
		min_x = min(c.x, min_x);
		min_y = min(c.y, min_y);
		min_z = min(c.z, min_z);

		max_x = max(max_x, c.x);
		max_y = max(max_y, c.y);
		max_z = max(max_z, c.z);
	}
}

vector<vector<coord>> k_means_seq(){
	vector<vector<coord>> clusters;

	set_min_max();

	// Shuffle dataset and pick initial k points as initial means
	random_shuffle(dataset.begin(),dataset.end());
	vector<coord> means = vector<coord>(k);
	for (int i=0; i<k; i++){
		means[i].x=dataset[i].x;
		means[i].y=dataset[i].y;
		means[i].z=dataset[i].z;
	}

	vector<pair<int,float>> nearest_mean = vector<pair<int,float>>(n);
	float temp_dist, min_dist;
	int min_dist_mean;

	coord temp_mean;
	vector<coord> temp_cluster;

	cerr<<"Init means are\n";
	for (int m=0;m<k;m++){
		cerr<<m<<" --> "<< means[m].x <<" " <<means[m].y <<" "<< means[m].z<<endl;
	}
	cerr<<endl;

	for (int iter=0; iter<max_iter;iter++){
		// reset clusters
		clusters = vector<vector<coord>>(k);

		// Assign nearest mean to each point
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
			nearest_mean[p] = pair<int,float>(min_dist_mean,min_dist);
		}
		for (int p=0;p<n;p++){
			clusters[nearest_mean[p].first].push_back(dataset[p]);
		}

		//  Calculate new means
		for (int c = 0;c<k; c++){
			if (clusters[c].size()!=0){
				means[c].x=0; means[c].y=0; means[c].z=0;
				for (int p=0;p<clusters[c].size();p++){
					means[c].x+=clusters[c][p].x;
					means[c].y+=clusters[c][p].y;
					means[c].z+=clusters[c][p].z;
				}
				means[c].x/=clusters[c].size();
				means[c].y/=clusters[c].size();
				means[c].z/=clusters[c].size(); 
			}
			// cerr<<c<<" --> "<< means[c].x <<" " <<means[c].y <<" "<< means[c].z<<endl;
			else{
				if (rand()%5!=0){
					int max_dist_point;
					float max_dist=-1;
					for (int i=0;i<n;i++){
						if (nearest_mean[i].second>max_dist){
							max_dist_point = i;
							max_dist = nearest_mean[i].second;
						}
					}
					means[c] = dataset[max_dist_point];
					nearest_mean[max_dist_point].second = 0;
					nearest_mean[max_dist_point].first  = c;
				}
				else{
					means[c].x = rand()%(int)(max_x-min_x) + min_x;
					means[c].y = rand()%(int)(max_y-min_y) + min_y;
					means[c].z = rand()%(int)(max_z-min_z) + min_z;
				}

			}
		}
		// cerr<<"Cluster sizes are\n";
		for (auto c: clusters){
			if (c.size()==0)
			cerr<<"Found zero size cluster on iter"<<iter<<endl;
		}
		// cerr<<endl;
	}
	return clusters;
}

int main(int argc, char const *argv[])
{	
	srand(time(NULL));
	ifstream data;
	data.open(argv[1]);
	data>>n>>k;
	coord point;
	int r=0;
	while (r<n){
		data>>point.x>>point.y>>point.z;
		dataset.push_back(point);
		r++;
	}
	vector<vector<coord>> clusters =k_means_seq();

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