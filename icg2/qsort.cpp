#include<bits/stdc++.h>
// using namespace std;

int part(vector<int> arr,int low,int high)
{
  int pivot=arr[high];
  int i = (low-1);
  
  for(int j=low;j<=high;j++)
  {
    if(arr[j]<pivot)
    {
      i++;
      int temp1 = arr[i];
      arr[i] = arr[j];
      arr[j] = temp1;
    }
  }
  int temp1 = arr[i+1];
  arr[i+1] = arr[high];
  arr[high] = temp1;
  return (i+1);
}

           
void qsort(vector<int> arr,int low,int high){

  if(low<high){
    int pi = part(arr,low,high);
    qsort(arr,low,pi-1);
    qsort(arr,pi+1,high);
  }
  
}
             
int main() {
  vector<int> arr{10,7,8,9,1,5};
  int n = arr.size();
  qsort(arr,0,n);
  cout<<"Sorted Array\n";
  for(int i=0;i<n;i++)
  {
    cout<<arr[i]<<" ";
  }
  return 0;
}
