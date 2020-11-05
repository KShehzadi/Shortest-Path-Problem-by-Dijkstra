#include<iostream>
#include<climits>    
#include<vector>
#include<sstream>
using namespace std;
int vertex;
int minimumDist(int dist[], bool Dset[])   /*A method to find the vertex with minimum distance which is not yet included in Dset*/
{
	int min = INT_MAX, index;                 /*initialize min with the maximum possible value as infinity does not exist */
	for (int v = 0; v < vertex; v++)
	{
		if (Dset[v] == false && dist[v] <= min)
		{
			min = dist[v];
			index = v;
		}
	}
	return index;
}
void dijkstra(vector<vector<int>> graph, int src, vector<string> cityNames, int destination, int fuel, int capacity,vector<int> cityFuelAvailability) /*Method to implement shortest path algorithm*/
{
	int *dist= new int[vertex];
	bool *Dset= new bool[vertex];
	for (int i = 0; i < vertex; i++)                    /*Initialize distance of all the vertex to INFINITY and Dset as false*/
	{
		dist[i] = INT_MAX;
		Dset[i] = false;
	}
	dist[src] = 0;                                   /*Initialize the distance of the source vertec to zero*/
	for (int c = 0; c < vertex; c++)
	{
		int u = minimumDist(dist, Dset);              /*u is any vertex that is not yet included in Dset and has minimum distance*/
		Dset[u] = true;                              /*If the vertex with minimum distance found include it to Dset*/
		for (int v = 0; v < vertex; v++)
			/*Update dist[v] if not in Dset and their is a path from src to v through u that has distance minimum than current value of dist[v]*/
		{
			if (!Dset[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
		}
	}
	cout << "Minimum Distance from source to Destination:";	
	cout <<  dist[destination] << endl;
	
}
int getIndex(vector<string> v, string K)
{
	auto it = find(v.begin(), v.end(), K);

	// If element was found
	if (it != v.end())
	{

		// calculating the index
		// of K
		int index = it - v.begin();
		return index;
	}
	else {
		// If the element is not
		// present in the vector
		return -1;
	}
}
void PrintGraph(vector<string> cityNames, vector<int> fuelAvailabilty, vector <vector<int>> graph)
{
	cout << "City Name" << "," << "Fule";
	for (int k = 0; k < vertex; k++)
	{
		cout << ","<<cityNames[k];
	}
	for (int i = 0; i < vertex; i++)
	{
		cout << cityNames[i] << "," << fuelAvailabilty[i];
		for (int j = 0; j < vertex; j++)
		{
			cout << "," << graph[i][j];
		}
		cout << endl;
	}
}
int main()
{
	string tempCityName;
	
	cout << "Enter the Number of Cities" << endl;
	cin >> vertex;
	vector<string> cityNames;
	cityNames.resize(vertex);
	vector<int> cityFuelAvailability;
	cityFuelAvailability.resize(vertex);
	for (int i = 0; i < vertex; i++)
	{
		cin >> tempCityName;
		stringstream ss(tempCityName);
		int k = 0;
		while (ss.good()) {
			string substr;
			getline(ss, substr, ',');
			if (k == 1)
			{
				int num = std::stoi(substr);
				cityFuelAvailability[i]=num;
				
			}
			else
			{
				cityNames[i]=substr;
				k++;
			}
		}
	}
	std::vector<std::vector<int> > graph;
	string line;
	graph.resize(vertex);
	for (int j = 0; j < vertex; j++)
	{
		cin >> line;
		graph[j].resize(vertex);
		stringstream ss(line);
		int k = 0;
		while (ss.good()) {
			string substr;
			getline(ss, substr, ',');
			int num = std::stoi(substr);
			graph[j][k] = num;
			k++;
		}
	}
	cout << "Enter the Source" << endl;
	string srctemp;
	cin >> srctemp;
	int src= getIndex(cityNames,srctemp);
	cout << "Enter the Destination" << endl;
	string disttemp;
	cin >> disttemp;
	int destination= getIndex(cityNames,disttemp);
	cout << "Enter the Starting fuel amount" << endl;
	int fuel;
	cin >> fuel;
	cout << "Enter the fuel tank capacity" << endl;
	int capacity;
	cin >> capacity;
	dijkstra(graph, src, cityNames,destination,fuel,capacity, cityFuelAvailability);

	return 0;
}
