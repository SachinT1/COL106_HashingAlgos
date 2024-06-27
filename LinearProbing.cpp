#include "LinearProbing.h"
#include<vector>
#include<cmath>
using namespace std;

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

LinearProbing::LinearProbing(){
    for(int i =0;i<100003;i++){
        Account a;
        a.id = "";
        a.balance = -1;
        bankStorage1d.push_back(a);
    }
    size=0;
}

void LinearProbing::createAccount(std::string id, int count) {
    
    int index = hash(id);
    if(bankStorage1d[index].id == ""){
        bankStorage1d[index].id=id;
        bankStorage1d[index].balance = count;
        
    }
    else{
        int off = 1;
        
        while(bankStorage1d[(index)].id!=""){
            index+=off;
            index=index%100003;

        }
        bankStorage1d[index].id = id;
        bankStorage1d[index].balance = count;
        
    }
    size++;
    return;
}

vector<int> LinearProbing::getTopK(int k) {
    vector<int> a;
    for(int i=0;i<100003;i++){
        if(bankStorage1d[i].id!=""){
            a.push_back(bankStorage1d[i].balance);

        }
    }
    mergesort(a,0,a.size()-1);

    if(a.size()>=k){
        vector<int> answer;
        for(int i=0;i<k;i++){
            answer.push_back(a[i]);
        }
        
        return answer;
    }
    else{
        return a;

    }
}

int LinearProbing::getBalance(std::string id) {
    int index = hash(id);
    for(int i=0;i<100003;i++){
        if(bankStorage1d[(index+i)%100003].id==id){
            return bankStorage1d[(index+i)%100003].balance;

        }
    }
    return -1; // Placeholder return value
}

void LinearProbing::addTransaction(std::string id, int count) {
    if(doesExist(id)){
        bankStorage1d[truepos].balance+=count;
    }
    else{
        createAccount(id,count);


    }
    
}

bool LinearProbing::doesExist(std::string id) {
    int index = hash(id);
    if(bankStorage1d[index].id==id){
        truepos = index;
        return true;
    }
    else{
        for(int i=1;i<100003;i++){
            if(bankStorage1d[(index+i)%100003].id==id){
                truepos= (index+i)%100003;
                return true;
            }
        }
    }
    return false; 
}

bool LinearProbing::deleteAccount(std::string id) {
    
    if(doesExist(id)==false){
        return false;
    }
    else{
        bankStorage1d[truepos].id = "";
        bankStorage1d[truepos].balance = -1;
        size--;
        return true;
    }
}
int LinearProbing::databaseSize() {
    return size;
    
}

int LinearProbing::hash(std::string id) {
    long long unsigned int s = 0;
    int pee = 3 ;
    int amm = 100003; 
    for(int i=0;i<id.size();i++){
        s +=( (int(id[i])-'0' + 1)*(int((pow(pee,i)))*((i*i)+1)))%amm;

    }



    s = s%amm;

    return s;
}

