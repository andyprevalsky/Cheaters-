#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include "hash.h"

using namespace std;

string strip(string& t);
void getChunks(string files, vector<queue<string>>& chunks, int nLength);

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main(int argc, char* agrv[]) {
    string dir = string("mid_doc_set");
    vector<string> files = vector<string>();
    getdir(dir,files);

    if (argc < 3) {
        cout << "No Parameters Added!" << endl;
        return 0;
    }

    int bound = stoi(agrv[2]);
    int nLength = stoi(agrv[1]);
    if (nLength == 0) {
        cout << "0 Length Chunks Aren't Allowed! " << endl;
        return 0;
    }


    cout << "Finding all " << nLength << " chunks!" << endl;
    vector<vector<queue<string>>> chunks;
    for (int i = 2; i < files.size(); i++) {
        vector<queue<string>> chunk;
        getChunks(files[i], chunk, nLength);
        chunks.push_back(chunk);
    }
    Hash h;
    
    for (int i = 0; i < chunks.size(); i++){
        for(int j = 0; j < chunks[i].size(); j++){
            h.insert(chunks[i][j], i);
        }
    }

    h.fileSimilarities(files.size()-2, files,bound);

}

string strip(string& t) { //changes string to all lower case and strips away special characters
    string res = "";
    for (int i = 0; i < t.size(); i++) {
        if (isalpha(t[i])) res += tolower(t[i]);
    }
    return res;
}

void getChunks(string fName, vector<queue<string>>& chunks, int nLength) {
    queue<string> q;
    ifstream fin ("mid_doc_set/" + fName);
    int j = 0;
    while(fin.good()) { //loop through file while file is still readable 
        for (; j < nLength; j++) { // fill queue, first, then process each word once at a time
            string temp;
            fin >> temp;
            temp = strip(temp); //strip temp of all special characters and convert all characters to lowe case
            if (fin.eof()) break; // break so that last line isn't read twice
            if (temp == "") {
                j--; //if sttring is empty then don't count it as a word
                continue;
            }
            q.push(temp);
        }
        if (q.size() < nLength) return;
        chunks.push_back(q);
        if (!q.empty()) q.pop();
        j--;
    }

    // for (auto i: chunks) {
    //     while (!i.empty()) {
    //         cout << i.front() << " ";
    //         i.pop();
    //     }
    //     cout << endl;
    // }

    return;
}