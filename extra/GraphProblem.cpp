//
// Created by ubecerril on 1/28/26.
//
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <algorithm>

using namespace std;
struct Flight {
    string from;
    string to;

    Flight(string&& fromCity, string&& toCity) : from(std::move(fromCity)), to(std::move(toCity)) {};
};

void tryOne(map<string, vector<string>> graph, string ini, string end) ;
void tryTwo(map<string, vector<string>> graph, string ini, string end);
void DFS(string ini);
void printVector(vector<string> v) ;

int main(int argc, char *argv[]) {
    /*vector<Flight> flights={
        {"MX","IST"}, {"IST","FRA"}, {"AMS","IST"},{"MAD","MX"},
        {"MX","MAD"}, {"BAR","FRA"}, {"AMS","MX"}, {"MX","FRA"},
        {"FRA","AMS"}, {"FRA","IST"}, {"IST","MAD"}
    };*/

    vector<Flight> flights = {
        {"MX","IST"}, {"IST","FRA"}, {"FRA","AMS"}, {"AMS","LON"},
        {"LON","NYC"}, {"NYC","TOR"}, {"TOR","VAN"},
        {"MX","MAD"}, {"MAD","PAR"}, {"PAR","FRA"},
        {"MX","BAR"}, {"BAR","ROM"}, {"ROM","IST"},
        {"IST","MAD"}, {"MAD","MX"},
        {"FRA","LON"}, {"LON","PAR"},
        {"PAR","AMS"}, {"AMS","MX"},
        {"ROM","PAR"}, {"TOR","NYC"},
        {"VAN","LAX"}, {"LAX","MX"}
    };

    // Build the graph
    map<string, vector<string>> graph;
    for (const auto& x: flights) {
        graph[x.from].push_back(x.to);
    }

    // Print the map (debug)
    for (const auto& x: graph) {
        auto city = x.first;
        auto destinations = x.second;

        cout << city <<  " => ";
        for (const auto& d: destinations) {
            cout << d << " ";
        }
        cout << endl;
    }

    /**
     *  TRY NUMBER 1
     **/
    // Example
    const string ini {"MX"};
    const string end {"AMS"};

    // Try 1
    tryOne(graph, ini, end);


    /**
     * TRY NUMBER TWO
     **/
    tryTwo(graph,  ini, end);
}

void tryOne(map<string, vector<string>> graph, string ini, string end) {
    stack<string> st;
    st.push(ini);

    queue<string> que;
    vector<queue<string>> res;

    int limit = 10;
    while (!st.empty() && limit >= 0) {
        string node = st.top();
        st.pop();

        // Agregar nodo a la cola de vuelos
        que.push(node);
        if (node == end) {
            res.push_back(que);
        }

        for (const auto& x: graph[node]) {
            st.push(x);
        }
        limit --;
    }

    // Print the result
    cout << "Respuesta 1: " << res.size() << endl;
    for (auto r : res) {
        while (!r.empty()) {
            cout<<r.front() << "=>";
            r.pop();
        }
        cout << endl;
    }
}

vector<string> currentPath;
set<string> visited;
string end = "AMS";
map<string, vector<string>> graph;
void tryTwo(map<string, vector<string>> graph, string ini, string end) {
    ::graph = graph;

    cout<< "Respuesta 2: " << endl;
    DFS(ini);

}

void DFS(string ini) {
    currentPath.push_back(ini);
    visited.insert(ini);

    if (ini == ::end) {
        printVector(currentPath);
    }else {
        for (const auto& x: graph[ini]) {
            if (visited.find(x) == visited.end()) {
                DFS(x);
            }
        }
    }

    auto it = std::find(currentPath.begin(), currentPath.end(), ini);
    if (it != currentPath.end()) {
        currentPath.erase(it);
    }
    visited.erase(ini);
}


void printVector(vector<string> v) {
    for (int i = 0; i < v.size(); i++) {
        if (i != v.size() - 1) {
            cout << v[i] << "=>";
        }else {
            cout << v[i] << endl;
        }
    }
}