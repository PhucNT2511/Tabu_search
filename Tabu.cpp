#include <bits/stdc++.h>

using namespace std;

struct dulieu{
	int x;
	int y;
};
struct dulieu a[10];

//
double distance(int i, int j){
    if(0<=i&&i<=9&&0<=j&&j<=9)
	return sqrt(pow((a[i].x-a[j].x),2)+pow((a[i].y-a[j].y),2));
    else return 0;
}

// Dinh nghia ham Object (fitness)
double objective_function( const vector<int>& solution)
{ 	vector<int> solutionCopy = solution; 
    int b[10];
    for(int i=0;i<=9;i++)
    b[i]=solutionCopy.at(i);
    double t=0;
    for(int i=0;i<9;i++) t+=distance(b[i],b[i+1]);
    return t;
}

// Dinh nghia lan can - tao ra 45 neighbor moi lan goi ham
vector<std::vector<int> > get_neighbors(const vector<int>& solution)
{ 
   	vector<vector<int> > neighbors;
    for (size_t i = 0; i < solution.size(); i++) {
        for (size_t j = i + 1; j < solution.size(); j++) {
            vector<int> neighbor = solution;
            swap(neighbor[i], neighbor[j]);
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}
// Ham Tabu_search
vector<int> tabu_search(const vector<int>& initial_solution, int max_iterations, int tabu_list_size)
{ 
    vector<int> best_solution = initial_solution;
    vector<int> current_solution = initial_solution;
    vector<vector<int> > tabu_list;
    // tao ra tat ca khoang 100*45 = 4500 bo solution
    for (int iter = 0; iter < max_iterations; iter++) {
        vector<vector<int> > neighbors  = get_neighbors(current_solution);
        vector<int> best_neighbor;
        int best_neighbor_fitness  = numeric_limits<int>::max();
 		
 		for (vector<vector<int> >::iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
    		const vector<int>& neighbor = *it;
            if (find(tabu_list.begin(), tabu_list.end(), neighbor) == tabu_list.end()) {
                double neighbor_fitness = objective_function(neighbor);
                if (neighbor_fitness  < best_neighbor_fitness) {
                    best_neighbor = neighbor;
                    best_neighbor_fitness = neighbor_fitness;
                }
            }
        }
 
        if (best_neighbor.empty()) {
            // No non-tabu neighbors found,
            // terminate the search
            break;
        }
        current_solution = best_neighbor;
        tabu_list.push_back(best_neighbor);
        if (tabu_list.size() > tabu_list_size) {
            // Remove the oldest entry from the
            // tabu list if it exceeds the size
            tabu_list.erase(tabu_list.begin());
        }
 
        if (objective_function(best_neighbor)
            < objective_function(best_solution)) {
            // Update the best solution if the
            // current neighbor is better
            best_solution = best_neighbor;
        }
    }
 
    return best_solution;
}
int main() {
	
	// Nhap toa do cac diem
	cout<<"Nhap toa do cua cac diem: ";
	for(int i =0;i<=9;i++) {
		cin>>a[i].x;
		cin>>a[i].y;
	}
	
	
	//	Thu_tu lan dau tien
		vector<int> initial_solution;
        // ex: { 1, 0, 9, 7, 6, 5, 3, 4, 8, 2};
        
        cout<<"initial_solution: ";
        for(int i =0;i<=9;i++) {int t;cin>>t;initial_solution.push_back(t);}
        //for(int i=0;i<=9;i++) cout<<initial_solution.at(i)<<" ";
        cout<<endl;
	//	
	int max_iterations = 100;
    int tabu_list_size = 10;
 
    vector<int> best_solution = tabu_search(initial_solution, max_iterations, tabu_list_size);
    cout << "Best solution fitness: " << objective_function(best_solution) <<endl;
    int b[10];
    cout << "Best solution:";
    //for(int i=0;i<=9;i++) b[i]=best_solution.at(i);
    for(int i=0;i<=9;i++) cout<<best_solution.at(i)<<" ";
    
    
	system("pause");
	return 0;
}

/*
15 40
28 96
55 73
36 90
06 64
33 21
19 54
80 23
85 42
75 20
*/