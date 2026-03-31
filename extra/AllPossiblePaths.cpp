//
// Created by ubecerril on 2/12/26.
//
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;
struct Flight {
    string from;
    string to;

    Flight(string&& fromCity, string&& toCity) : from(std::move(fromCity)), to(std::move(toCity)) {};
};

void printVector(const vector<string>& v) ;
void allPossiblePaths(map<string, vector<string>>& graph, const string& source, const string& destination);
void DFS(map<string, vector<string>>& graph, const string& current, const string& destination, unordered_set<string>& visited, vector<string>& path, vector<vector<string>>& paths);

int main(int argc, char *argv[]) {
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

    // Get the inputs
    cout << "This program gives all the possible paths between two cities" << endl;

    string source, destination;
    cout << "Type the city source: " << endl;
    getline(cin, source);

    cout << "Type the city destination: " << endl;
    getline(cin, destination);

    cout << "solving" << endl;
    // Solve
    allPossiblePaths(graph, source, destination);
}

void allPossiblePaths(map<string, vector<string>>& graph, const string& source, const string& destination) {
    vector<string> path;
    vector<vector<string>> paths;
    unordered_set<string> visited;

    // Do DFS with backtracking
    DFS(graph, source, destination,visited, path, paths);

    // Print solution
    cout << "All possible paths between "<< source << " and " << destination << ": " << endl;
    for (auto& p: paths) {
        printVector(p);
    }
}
void DFS(map<string, vector<string>>& graph, const string& current, const string& destination, unordered_set<string>& visited, vector<string>& path, vector<vector<string>>& paths) {
    path.push_back(current);
    visited.insert(current);

    if (current == destination) {
        paths.push_back(path);
    }else {
        for (auto& c: graph[current]) {
            if (!visited.count(c)) {
                DFS(graph, c, destination, visited, path, paths);
            }
        }
    }

    // Backtracking, if we reach this point, we reach a node that has no nodes left to visit, so we go back by removing itself from the current path,
    // and from the visited nodes so that it can be visited again from another path.
    path.pop_back();
    visited.erase(current);
}
void printVector(const vector<string>& v) {
    for (int i = 0; i < v.size(); i++) {
        if (i != v.size() - 1) {
            cout << v[i] << "=>";
        }else {
            cout << v[i] << endl;
        }
    }
}

int firstNonRepeating(const string &input) {
    if (input.empty()) return -1;

    // Fill the freq array
    vector<int> freq(26);
    for (const auto& c: input) {
        freq[c - 'a']++;
    }

    // Search for the first char in the original array with freq 1
    for (int i = 0; i< input.length(); i++) {
        if (freq[input[i] - 'a'] == 1) return i;
    }

    // If not exits return -1
    return -1;
}


// int firstNonRepeating(const string &input) {
//     if (input.empty()) return -1;
//
//     for (int i = 0; i < input.length(); i++) {
//         bool isRepeating = false;
//         for (int j = 0; j < input.length(); j++) {
//             if (i !=j ) {
//                 if (input[i] == input[j]) {
//                     isRepeating = true;
//                     break;
//                 }
//             }
//         }
//         if (!isRepeating) {
//             return i;
//         }
//     }
//     return -1;
// }

int longestSubstring(const string& input) {
    if (input.empty()) return 0;

    unordered_map<char, int> lastSeen;
    int max = 1;

    int begin = 0, end = 0;
    for (; end < input.length(); end++) {
        // Update beginning
        begin = std::max(begin, lastSeen[input[end]] +1);
        // Update max
        max = std::max(max, end-begin + 1);
        // Update map
        lastSeen[input[end]] = end;
    }

    return max;
}

vector<vector<int>> treeByLevels(BinaryTree* root) {
    if (root == nullptr)  return {};

    vector<vector<int>> levels;
    queue<BinaryTree*> q;
    q.push(root);
    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> level;

        for (int i = 0; i < levelSize; i++) {
            auto node = q.front();
            q.pop();

            level.push_back(node->data);

            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }
        levels.push_back(level);
    }

    return levels;
}

vector<int> productOfArray(vector<int>& nums) {
    // Build prefix
    vector<int> output(nums.size());
    output[0] = 1;
    for (int i = 1; i < nums.size(); i++) {
        output[i] = output[i-1] * nums[i-1];
    }

    int postfix = 1;
    for (int i = nums.size() - 2; i >= 0; i--) {
        output[i] *= postfix;
        postfix *= nums[i];
    }

    return output;
}