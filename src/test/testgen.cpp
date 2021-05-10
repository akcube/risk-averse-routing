#include <bits/stdc++.h>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]){
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
	int c = atoi(argv[3]);
	cout<<-1<<" "<<n<<" "<<m<<" "<<c<<"-1 "<<endl;

	srand(time(0));
	vector<string> names;

	for(int i=0; i<m; i++){
		int u = rand()%n;
		int v = rand()%n;
		while(u==v) v = rand()%n;
		string name = "";
		for(int j=0; j<5; j++){
			name += (char) (rand()%26)+97;
		}
		names.push_back(name);
		int len = rand()%100;
		cout<<u<<" "<<v<<" "<<name<<" "<<len<<endl;
	}

	for(int i=0; i<c; i++){
		int p = rand()%25;
		cout<<p<<" ";
		for(int j=0; j<p; j++){
			int idx = rand()%names.size();
			cout<<names[idx]<<" ";
		}
		cout<<endl;
	}

}