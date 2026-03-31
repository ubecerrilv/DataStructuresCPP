#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

void firstNonRepeating(const std::string &s) {
    std::unordered_map<char, int> freq;
    std::queue <char> q;

    for (const auto &c : s) {
        freq[c]++;
        if (freq[c] <= 1) {
            q.push(c);
        }

        while (!q.empty() && freq[q.front()] > 1) {
            q.pop();
        }
        if (q.empty()) {
            std::cout << '#';
        }else {
            std::cout<< q.front();
        }
    }
}

int subarraySum(const vector<int>& nums, const int k) {
    unordered_map<int, int> freq;
    freq[0] = 1;
    int sum = 0, answer = 0;

    for (auto const &n: nums) {
        sum += n;

        if (freq.count(sum - k)) {
            answer += freq[sum - k];
        }
        freq[sum]++;
    }
    return answer;
}

int countOddSumSubarrays(const vector<int>& nums) {
    int odd = 0, even = 1, sum = 0, answer = 0;

    for (auto const &n: nums) {
        sum += n;
        if (sum % 2 == 0) {
            answer += odd;
            even++;
        }else {
            answer += even;
            odd++;
        }
    }
    return answer;
}

string compressString(const string &s) {
    if (s.empty()) return s;
    string ans{};

    char lastRepeatedChar = s[0];
    int freq = 1;
    for (int i = 1; i < s.size(); i++) {
        if (lastRepeatedChar != s[i]) {
            ans += string (1, lastRepeatedChar) + to_string(freq);
            lastRepeatedChar = s[i];
            freq = 1;
        }else {
            freq++;
        }
    }
    ans += string (1, lastRepeatedChar) + to_string(freq);

    return s.size() <= ans.size() ? s : ans;
}

vector<int> arrayMulButNotItself(const vector<int> &nums) {
    vector<int> ans{};
    int leftProduct = 1;
    for (auto const &n: nums) {
        ans.push_back(leftProduct);
        leftProduct *= n;
    }

    int rightProduct = 1;
    for (int i = nums.size() - 1; i >= 0; i--) {
        ans[i] *= rightProduct;
        rightProduct *= nums[i];
    }
    return ans;
}

int largestNonRepeatingSubstring(const string &s) {
    if (s.empty()) return 0;

    unordered_map<char, int> lastIndexOf;
    int left = 0, max = 1;
    for (int right = 0; right < s.size(); right++) {
        if (lastIndexOf.count(s[right]) && lastIndexOf[s[right]] >= left) {
            left = lastIndexOf[s[right]] + 1;
        }
        max = max > right - left + 1 ? max : right - left + 1;
        lastIndexOf[s[right]] = right;
    }
    return max;
}

int main(int argc, char *argv[]) {
    cout << largestNonRepeatingSubstring("abcabcbb") << endl;
    cout << largestNonRepeatingSubstring("bbbbb") << endl;
    cout << largestNonRepeatingSubstring("pwwkew") << endl;
    cout << largestNonRepeatingSubstring("abcdefghijklmnopqrstuvwxyz") << endl;
}
