#include <iostream>
using namespace std;

        //check palindrome!

int main(){

    int n;
    cin>>n;
    char arr[n+1];

    cin>>arr;

    bool check = 1;

    for(int i=0; i<n; i++){
        if(arr[i] != arr[n-1-i]){
            check = 0;
        }
    }

    if(check==true){
        cout<<"PALINDROME!!";
    }
    else {
        cout<<"NOT A PALINDROME!";
    }


    return 0;
}