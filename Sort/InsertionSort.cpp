#include<iostream>

using namespace std;

int nums[50]={0};

void sort(int n) {
      
      for (int i = 1; i < n; i++) {
            
            int currentElement = nums[i]; 
            int j = i - 1;                

            while (j >= 0 && nums[j] > currentElement) {
                  nums[j + 1] = nums[j]; 
                  j--;                   
              }
            nums[j + 1] = currentElement;
        }
}



int main(void){
      int n;
      cin>>n;
      for(int i =0;i<n;i++){
            cin>>nums[i];
        }

      sort(n);
      for(int i=0;i<n;i++){
            cout<<nums[i];
            printf("%s",i==n-1?"":" ");
        }

      return 0;
}

