#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "hash.h"

using namespace std;

string strip(string& t) { //changes string to all lower case and strips away special characters
    string res = "";
    for (int i = 0; i < t.size(); i++) {
        if (isalpha(t[i])) res += tolower(t[i]);
    }
    return res;
}

void getChunks(string fName, vector<queue<string> >& chunks, int nLength, string path) {
    queue<string> q;
    ifstream fin ((path + fName).c_str());
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
//check if parameters are accurate
    if (argc < 4) {
        cout << "Not Enough Parameters Added!" << endl;
        return 0;
    }

//get the arguments from the command line and put them in variables for use
    string dir = string(agrv[1]);
    vector<string> files = vector<string>();
    getdir(dir,files);

    int bound = atoi(agrv[3]);
    int nLength = atoi(agrv[2]);
//check if argument is wrong!    
    if (nLength == 0) {
        cout << "0 Length Chunks Aren't Allowed! " << endl;
        return 0;
    }


    cout << "Finding all " << nLength << " chunks!" << endl;
    vector<vector<queue<string> > > chunks;
    for (int i = 2; i < files.size(); i++) {
        vector<queue<string> > chunk;
        getChunks(files[i], chunk, nLength, dir);
        chunks.push_back(chunk);
    }
    //create hash
    Hash h;

    for (int i = 0; i < chunks.size(); i++){
        for(int j = 0; j < chunks[i].size(); j++){
            h.insert(chunks[i][j], i);
        }
    }
//organize the similarities between files and print out the similarities along with the file names in sorted order 
    h.fileSimilarities(files.size()-2, files,bound);
}