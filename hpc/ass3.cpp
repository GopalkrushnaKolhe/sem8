#include<bits/stdc++.h>

using namespace std;
using namespace std::chrono;

int seqmin(int a[],int n){
    int mini=a[0];
    for(int i=1;i<n;i++){
            if(a[i]<mini){
                mini=a[i];
            }
        }
    return mini;
}

int parmin(int a[],int n){
    int mini=a[0];
    #pragma omp parallel for reduction(min:mini)
    for(int i=1;i<n;i++){
            if(a[i]<mini){
                mini=a[i];
            }
        }
    return mini;
}

int seqmax(int a[],int n){
    int maxi=a[0];
    for(int i=1;i<n;i++){
            if(a[i]>maxi){
                maxi=a[i];
            }
        }
    return maxi;
}

int parmax(int a[],int n){
    int maxi=a[0];
     #pragma omp parallel for reduction(max:maxi)
    for(int i=1;i<n;i++){
            if(a[i]>maxi){
                maxi=a[i];
            }
        }
    return maxi;
}

long long seqsum(int a[],int n){
    long long sum=0;
    for(int i=0;i<n;i++){
        sum=sum+a[i];
    }
    return sum;
}

long long parsum(int a[],int n){
    long long sum=0;
     #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<n;i++){
        sum=sum+a[i];
    }
    return sum;
}


double seqavg(int a[],int n){
    return seqsum(a,n)/n;
}


double paravg(int a[],int n){
    return parsum(a,n)/n;
}


int main(){
    int n =10000;
    int a[n];
    int b[n];
    for(int i=0;i<n;i++){
        a[i]=rand();
        b[i]=rand();
    }
    auto start=high_resolution_clock::now();
    cout<<seqavg(a,n)<<endl;
    cout<<seqsum(a,n)<<endl;
    cout<<seqmin(a,n)<<endl;
    cout<<seqmax(a,n)<<endl;
    auto stop=high_resolution_clock::now();
    auto duration=duration_cast<microseconds>(stop-start);
    cout<<"Sequential time "<<duration.count()<<" microseconds"<<endl;

    start=high_resolution_clock::now();
    cout<<paravg(b,n)<<endl;
    cout<<parsum(b,n)<<endl;
    cout<<parmin(b,n)<<endl;
    cout<<parmax(b,n)<<endl;
    stop=high_resolution_clock::now();
    duration=duration_cast<microseconds>(stop-start);
    cout<<"Parallel time "<<duration.count()<<" microseconds"<<endl;


    return 0;
}