#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

void initFile();
void seperateNodeOne(string line);
void seperateNodeTwo(string line);
void seperateWeight(string line);
void printArrays();
void printarray(int arg[], int length);
void printarray(string arg[], int length);
void printarray(vector<string> arg, int length);
void setupMatrix();
void printMatrix();
void populateMatrix();
void createMap();
void printMap();
void logic();
void djikstraAlgo();
void finalPrint();
void dijkstra(int graph[21][21], int src);
int printSolution(int dist[], int n);
int minDistance(int dist[], bool sptSet[]);

int positionOfArray = 0;
int positionOfCombined = 0;
string source[39];
string dest[39];
string combined[78];
string uniqueLocations[21];
int val[39];
int matrix[21][21];
map<string, int> dictionary;
int cost1, cost2, cost3;
string loc1 = "YYC";
string loc2,loc3;
int locKey1, locKey2, locKey3;
int hops = 0;
int hops2 = 0;
int hops3 = 0;


int main()
{
    initFile();
    setupMatrix();
    createMap();
    cout<<"\nHere are the indexes of the matrix and their representitve locations:\n\n";
    printMap();
    cout<<"\n\nHere is the matrix representation of the map:\n\n";
    printMatrix();
    cout<<"\n\n\nHere are the final results:";
    djikstraAlgo();
    cout<<"\n";
    return 0;
}

void initFile()
{
    string line;
    ifstream myfile("map.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            seperateNodeOne(line);
            seperateNodeTwo(line);
            seperateWeight(line);
            positionOfArray++;
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}

void seperateNodeOne(string line)
{
    string temp = "ABC";
    for (int i = 0; i < 3; i++)
    {
        temp[i] = line[i];
    }
    source[positionOfArray] = temp;
    combined[positionOfCombined] = temp;
    positionOfCombined++;
}

void seperateNodeTwo(string line)
{
    string temp = "XYZ";
    int start = 0;
    for (int i = 4; i < 7; i++)
    {
        temp[start] = line[i];
        start++;
    }
    dest[positionOfArray] = temp;
    combined[positionOfCombined] = temp;
    positionOfCombined++;
}

void seperateWeight(string line)
{
    string temp = "ABCD";
    int start = 0;
    for (int i = 8; i < 12; i++)
    {
        temp[start] = line[i];
        start++;
    }
    int weight = stoi(temp);
    val[positionOfArray] = weight;
}

void setupMatrix()
{
    vector<string> uniqueValues(78);
    copy(combined + 0, combined + 78, uniqueValues.begin());
    sort(uniqueValues.begin(), uniqueValues.end());
    uniqueValues.erase(unique(uniqueValues.begin(), uniqueValues.end()), uniqueValues.end());
    int counter = 0;
    for (int i = 0; i < uniqueValues.size(); i++)
    {
        string temp = uniqueValues[i];
        if (temp[0] == 'Y')
        {
            uniqueLocations[counter] = temp;
            counter++;
        }
    }
}

void printMatrix()
{
    int sizeOfMatrix = 21;
    populateMatrix();
    cout << "     ";
    for (int i = 0; i < sizeOfMatrix; i++)
    {
        cout << uniqueLocations[i] << "  ";
    }
    for (int i = 0; i < 21; i++)
    {
        cout << "\n--------------------------------------------------------------------------------------------------------------";
        cout << '\n';
        cout << uniqueLocations[i] << " |";
        for (int j = 0; j < 21; j++)
        {
            if (matrix[i][j] >= 1000)
            {
                cout << "" << matrix[i][j] << "|";
            }
            else if (matrix[i][j] >= 100 && matrix[i][j] < 1000)
            {
                cout << "" << matrix[i][j] << " |";
            }
            else if (matrix[i][j] >= 1 && matrix[i][j] < 100)
            {
                cout << " " << matrix[i][j] << " |";
            }
            else
            {
                cout << "  " << matrix[i][j] << " |";
            }
        }
    }
}

void populateMatrix()
{
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            matrix[i][j] = 0;
        }
    }
    logic();
}

void createMap()
{
    for (int i = 0; i < 21; i++)
    {
        string temp = uniqueLocations[i];
        dictionary[temp] = i;
    }
}

void printMap()
{
    for (auto const &pair : dictionary)
    {
        std::cout << "{ " << pair.first << " : " << pair.second << " }\n";
    }
}

void logic()
{
    for (int i = 0; i < 39; i++)
    {
        auto it = dictionary.find(source[i]);
        auto two = dictionary.find(dest[i]);
        int locationIdentifier = it->second;
        int destinationIdentifier = two->second;
        int weight = val[i];
        if (it->first == "YYZ")
        {
            loc1 = it->first;
            locKey1 = it->second;
        }
        else if (two->first == "YYZ")
        {
            loc1 = two->first;
            locKey1 = two->second;
        }
        else if (it->first == "YUL")
        {
            loc2 = it->first;
            locKey2 = it->second;
        }
        else if (two->first == "YUL")
        {
            loc2 = two->first;
            locKey2 = two->second;
        }
        else if (it->first == "YVR")
        {
            loc3 = it->first;
            locKey3 = it->second;
        }
        else if (two->first == "YVR")
        {
            loc2 = two->first;
            locKey3 = two->second;
        }
        matrix[locationIdentifier][destinationIdentifier] = weight;
        matrix[destinationIdentifier][locationIdentifier] = weight;
    }
}

void djikstraAlgo()
{
    dijkstra(matrix, 16);
}

#define V 21

int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index = 0;

    for (int v = 0; v < V; v++)
    {
        if (sptSet[v] == false && dist[v] <= min)
        {
            min = dist[v], min_index = v;
        }
    }

    return min_index;
}

void printPath(int parent[], int j)
{    
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);
    string temp;
    auto it = dictionary.find(uniqueLocations[j]);
    loc1 = loc1 + " -> " + it->first;
}

void printSolution(int dist[], int n, int parent[], int src)
{
    int min = INT_MAX;
    int nodo = -1;
    cout << "\n\nDestination     Cost            Hops            Path" << endl;
    cout << "----------------------------------------------------------------\n";
    for (int i = 0; i < V; i++)
    {
        auto it = dictionary.find(uniqueLocations[i]);
        if (it->first == "YYZ" || it->first == "YUL" || it->first == "YVR")
        {
            hops = 0;
            loc1 = "YYC";
            printPath(parent, i);
            for(int j= 0; j < loc1.length();j++) {
                if(loc1[j] == '>') {
                    hops++;
                }
            }
            cout << it->first << "\t\t" << dist[i] << "\t\t" << hops << "\t\t"
                 << loc1;
            cout << endl;

            if (dist[i] < min && dist[i] != 0)
            {
                min = dist[i];
                nodo = i;
            }
        }
    }
}

void dijkstra(int graph[V][V], int src)
{
    int dist[V];
    bool sptSet[V];
    int parent[V];

    parent[src] = -1;
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, sptSet);

        sptSet[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
    printSolution(dist, V, parent, src);
}
