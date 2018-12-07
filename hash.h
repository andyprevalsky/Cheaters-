#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

#define N 99991
#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */

class Hash {
    private:
        vector<int> table[N];
        
    public:
    //hashing function
        void insert(queue<string> s, int file) {
            string s2 = "";
            while (!s.empty()) {
                s2 += s.front() + " ";
                s.pop();
            }
            //cout << s2 << endl;
            int index = hash_str(s2);
            // cout << s << " " << index << endl;
            table[index].push_back(file);
        }

        int hash_str(string s) {
            unsigned h = FIRSTH;
            for (int i = 0; i < s.size(); i++) {
                h = (h * A) ^ (s[i] * B);
            }
            return h % N; // or return h % C;
        }
//organize the similarities between files
        void fileSimilarities(int numFiles, vector<string>& fileNames, int bound){
            int ind = 0;
            int result[numFiles][numFiles];
            int memo[numFiles][numFiles];
            memset(result, 0, sizeof(result));
            for (int i = 0; i < N; i++) {
                memset(memo,0,sizeof(memo));
                for (int j = 0; j < table[i].size(); j++) {
                    for(int k = 0; k < table[i].size(); k++){
                        memo[table[i][j]][table[i][k]] = 1; 
                    }
                }
                for(int j = 0; j < numFiles; j++){
                    for(int k = 0; k < numFiles; k++){
                        if(memo[j][k]==1){
                            result[j][k]+=1;
                        }
                    }
                }
            }


            //print after sorting the similarities bound by the lower limit!!
            vector<vector<int> > res2;
            for(int i = 0; i < numFiles; i++){
                for(int j = i+1; j < numFiles; j++){
                    if(result[i][j] > bound){
                        vector<int> a;
                        a.push_back(result[i][j]);
                        a.push_back(i+2);
                        a.push_back(j+2);
                        res2.push_back(a);
                    }
                }
            }
            sort(res2.begin(),res2.end());
            for(int i = res2.size()-1; i >= 0; i--){
                cout << res2[i][0] << ": " << fileNames[res2[i][1]] << ", " << fileNames[res2[i][2]] << endl;
            }

            //cout << "SIZE " << res.size() << endl;
        }

};