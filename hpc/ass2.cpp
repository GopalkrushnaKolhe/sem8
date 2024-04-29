#include <bits/stdc++.h>

using namespace std::chrono;
using namespace std;

void bubblesort(int a[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(a[j]>a[j+1]){
                swap(a[j],a[j+1]);
            }
        }
    }
}


void pabubblesort(int a[], int n){
    for(int i=0;i<n-1;i++){
       #pragma omp parallel for
        for(int j=0;j<n-i-1;j++){
            if(a[j]>a[j+1]){
                swap(a[j],a[j+1]);
            }
        }
    }
}



void merge(int a[],int low,int high,int mid){
    int n1=mid-low+1;
    int n2=high-mid;
    int left[n1];
    int right[n2];
    for(int i=0;i<n1;i++){
        left[i]=a[low+i];
    }
    for(int i=0;i<n2;i++){
        right[i]=a[mid+i+1];
    }
    int i=0,j=0;
    int k=low;
    while(i<n1 && j<n2){
        if(left[i]<=right[j]){
            a[k]=left[i];
            i++;
        }
        else{
            a[k]=right[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        a[k]=left[i];
        k++;
        i++;
    }
    while(j<n2){
        a[k]=right[j];
        k++;
        j++;
    }
}

void mergesort(int a[],int low,int high){
    
    if(low<high){
        int mid=low+(high-low)/2;
        mergesort(a,low,mid);
        mergesort(a,mid+1,high);
        merge(a,low,high,mid);
    }
}

void pmergesort(int a[],int low,int high){
    if(low<high){
        int mid=low+(high-low)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                pmergesort(a,low,mid);
            }
             #pragma omp section
            {
                 pmergesort(a,mid+1,high);
            }      
        }
        merge(a,low,high,mid);
    }
}


int main(){
    int n;
    cout<<"enter the size"<<endl;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int b[n];
    for(int i=0;i<n;i++){
        b[i]=a[i];
    }
    auto start=high_resolution_clock::now();
    pabubblesort(a,n);
    auto stop=high_resolution_clock::now();
    auto duration=duration_cast<microseconds>(stop-start);

    cout<<"parallel bubble sort "<<duration.count()<<" microseconds"<<endl;

    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }

    cout<<endl;
    start=high_resolution_clock::now();
    pmergesort(b,0,n);
     stop=high_resolution_clock::now();
     duration=duration_cast<microseconds>(stop-start);

    cout<<"parallel merge sort "<<duration.count()<<" microseconds"<<endl;
    for(int i=0;i<n;i++){
        cout<<b[i]<<" ";
    }

    cout<<endl;
    int n2=100000;
    int a1[n2],b1[n2],c1[n2],d1[n2];
    for(int i=0;i<n;i++)
    {
        a1[i]=rand();
        b1[i]=rand();
        c1[i]=rand();
        d1[i]=rand();
    }
    // int b1[5]={9,1,3,10,2};
    // int c1[5]={9,1,3,10,2};
    // int d1[5]={9,1,3,10,2};

   // cout<<"After Sequential Bubble sort: "<<endl;
    start=high_resolution_clock::now();
    bubblesort(a1,n);
    stop=high_resolution_clock::now();
    auto f=duration_cast<microseconds>(stop-start);
    // printa(a1,5);

    //cout<<"After Parallel Bubble sort: "<<endl;
    auto start2=high_resolution_clock::now();
    pabubblesort(b1,n);
    auto stop2=high_resolution_clock::now();
    auto f2=duration_cast<microseconds>(stop2-start2);
    // printa(b1,5);

   // cout<<"After Sequential Merge sort: "<<endl;
    auto start3=high_resolution_clock::now();
    mergesort(c1,0,n);
    auto stop3=high_resolution_clock::now();
    auto f3=duration_cast<microseconds>(stop3-start3);
    // printa(c1,5);

    //cout<<"After Parallel Merge sort: "<<endl;
    auto start4=high_resolution_clock::now();
    pmergesort(d1,0,n);
    auto stop4=high_resolution_clock::now();
    auto f4=duration_cast<microseconds>(stop4-start4);
    // printa(d1,5);

    cout<<"Time taken by seq bubble: "<<f.count()<<endl;
    cout<<"Time taken by parallel bubble: "<<f2.count()<<endl;
    cout<<"Time taken by seq merge: "<<f3.count()<<endl;
    cout<<"Time taken by parallel merge: "<<f4.count()<<endl;

    return 0;
}