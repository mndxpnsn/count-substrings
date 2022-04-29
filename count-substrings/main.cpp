//
//  main.cpp
//  count-substrings
//
//  Created by Derek Harrison on 29/04/2022.
//

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

bool differ_by_one(string s, string t) {
    int n = (int) s.length();
    
    int count = 0;
    
    for(int i = 0; i < n; ++i)
        if(s[i] == t[i]) count++;
    
    return count == n - 1;
}

int count_substr(string elem_s, vector<string> str_vec_t) {
    
    int count = 0;
    
    for(auto elem_t : str_vec_t) {
        bool diff_by_one = differ_by_one(elem_s, elem_t);
        if(diff_by_one) count++;
    }
    
    return count;
}

int count_substrings(string s, string t) {
    int m = (int) s.length();
    int n = (int) t.length();
    
    vector<string> str_vec_s;
    vector<string> str_vec_t;
    
    map<string, map<int, bool>> dup_map_s;
    map<string, map<int, bool>> dup_map_t;
    
    map<int, vector<string>> str_map_s;
    map<int, vector<string>> str_map_t;

    for(int i = 1; i <= m; ++i) {
        for(int j = 1; j <= i; ++j) {
            for(int k = j; k <= i; ++k) {
                string str_loc_s = s.substr(k - 1, i - k + 1);
                if(dup_map_s[str_loc_s][k - 1] == false) {
                    str_vec_s.push_back(str_loc_s);
                    int len = i - k + 1;
                    str_map_s[len].push_back(str_loc_s);
                    dup_map_s[str_loc_s][k - 1] = true;
                }
            }
        }
    }
    
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= i; ++j) {
            for(int k = j; k <= i; ++k) {
                string str_loc_t = t.substr(k - 1, i - k + 1);
                if(dup_map_t[str_loc_t][k - 1] == false) {
                    str_vec_t.push_back(str_loc_t);
                    int len = i - k + 1;
                    str_map_t[len].push_back(str_loc_t);
                    dup_map_t[str_loc_t][k - 1] = true;
                }
            }
        }
    }

    
    int count = 0;
    
    for(auto elem_s : str_vec_s) {
        int len = (int) elem_s.length();
        count = count + count_substr(elem_s, str_map_t[len]);
    }
    
    return count;
}

int main(int argc, const char * argv[]) {

    string s = "computer";
    string t = "computation";
    
    int num_substrings = count_substrings(s, t);
    
    cout << "number of substrings: " << num_substrings << endl;
    
    return 0;
}
