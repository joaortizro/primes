#include <iostream>
#include <cstdio>
#include <unordered_set>
#include <fstream>
#include <string>
#define n 25
using namespace std;

int main(int argc, char **argv){

    string path;
    path=argv[1];
    //cout<< path<<endl;
    //ifstream checkfile("../omp/sieveList.txt");
    //ifstream checkfile("../cuda/cudaSieveList.txt");
    ifstream checkfile(path);
    unordered_set<string> primes;
    string line;
    for(int i=1;i<=n;i++){
        string location="primes/primes";
        location.append(to_string(i));
        location.append(".txt");
        ifstream file(location);
        getline(file,line); //skiping first lines
        while(file >> line){
            primes.insert(line);
        }
    }
    

    while(checkfile>>line){
        if(primes.find(line)==primes.end()){
            cout<<"not a prime "<<line<<endl;
            return 0;
        }
    }
    cout<<"correct"<<endl;
    return 0;
}