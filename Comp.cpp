#include "Comp.h"
using namespace std;
#include<vector>
#include<cmath>

void merge(vector<int>& vec, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    
    vector<int> lefty(n1);
    vector<int> righty(n2);

    
    for (int p = 0; p < n1; p++) {
        lefty[p] = vec[left + p];
    }
    for (int q = 0; q < n2; q++) {
        righty[q] = vec[middle + 1 + q];
    }

    
    int leftpoint = 0, rightpoint = 0, k = left;
    while (leftpoint < n1 && rightpoint < n2) {
        if (lefty[leftpoint] >= righty[rightpoint]) {
            vec[k++] = lefty[leftpoint++];
        } else {
            vec[k++] = righty[rightpoint++];
        }
    }

    
    while (leftpoint < n1) {
        vec[k++] = lefty[leftpoint++];
    }

    
    while (rightpoint < n2) {
        vec[k++] = righty[rightpoint++];
    }
}

void mergesort(vector<int>& vec, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        
        mergesort(vec, left, middle);
        mergesort(vec, middle + 1, right);
        merge(vec, left, middle, right);
    }
}

Comp::Comp(){
    for(int i=0;i<100003;i++){
        vector<Account> arri;
        bankStorage2d.push_back(arri);
    }
    size=0;
}

void Comp::createAccount(string id, int count) {
    Account a;
    a.id = id;
    a.balance = count;
    size++;
    bankStorage2d[hash(id)].push_back(a);   
}

vector<int> Comp::getTopK(int k) {
    vector<int> balansh;
    
    for(int i=0;i<bankStorage2d.size();i++){
        for(int j=0;j<bankStorage2d[i].size();j++){
            balansh.push_back(bankStorage2d[i][j].balance);
        }
    }
    mergesort(balansh,0,balansh.size()-1);
    

    if(balansh.size()>=k){
        vector<int>answer;
        
        for(int i=0;i<k;i++){
            answer.push_back(balansh[i]);
        }
        return answer;
    }
    else{
        return balansh;
        
    }

    
}

int Comp::getBalance(std::string id) {
    if(doesExist(id)){
        return bankStorage2d[hashval][position].balance;
    }
    else{
    return -1; // Placeholder return value
}
}

void Comp::addTransaction(std::string id, int count) {
    
    
    if(doesExist(id)){
        bankStorage2d[hashval][position].balance+=count;
    }
    else{
    
        createAccount(id,count);

    }

    return;

}

bool Comp::doesExist(std::string id) {
    int index = hash(id);
    for(int i=0;i<bankStorage2d[index].size();i++){
        if(bankStorage2d[index][i].id==id){
            hashval=index;
            position = i;
            return true;
        }
    }
    return false;
}

bool Comp::deleteAccount(std::string id) {
    if(doesExist(id)==false){
        return false;

    }
    else{
        
        
        bankStorage2d[hashval].erase(bankStorage2d[hashval].begin()+position);
        size--;
        return true;
    }
}

int Comp::databaseSize() {
    return size;
}

int Comp::hash(string id) {
    
    long long unsigned int s = 0;
    int pee = 3 ;
    int amm = 100003;
     
    for(int i=0;i<id.size();i++){
        
        s +=((int(id[i])-'0' + 1)*(int((pow(pee,i)))*((i*i)+1)))%amm;
        
    }



    s = s%amm;

    return s;
}



