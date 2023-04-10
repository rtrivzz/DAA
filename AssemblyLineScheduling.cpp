//Assembly Line Scheduling using Dynamic Programming 
#include <iostream>
using namespace std;
 
int productAssembly(int a[][5], int t[][4], int e[2], int x[2]) 
{ 
    int f1[5], f2[5]; 
 
    // time taken to reach first station at line 1 
    f1[0] = e[0] + a[0][0]; 
     
    // time taken to reach first station at line 2 
    f2[0] = e[1] + a[1][0]; 
 
    // fill tables f1[] and f2[] using the 
    // given recursive relations 
    for(int j = 1; j< 5; j++) 
    { 
        f1[j] = min(f1[j - 1] + a[0][j], 
                    f2[j - 1] + t[1][j-1] + a[0][j]); 
        f2[j] = min(f2[j - 1] + a[1][j],
                    f1[j - 1] + t[0][j-1] + a[1][j]); 
    } 
 
    // Consider exit times and return minimum 
    return min(f1[4] + x[0], f2[4] + x[1]); 
} 
 
// Driver Code
int main() { 
    int a[2][5] = { {8, 10, 4, 5, 9}, 
                    { 9, 6, 7, 5, 6} }; 
    int t[2][4] = { {2, 3, 1, 3}, 
                    {2, 1, 2, 2} }; 
    int e[2] = {3, 5};
    int x[2] = {2, 1}; 
 
    cout<<"Optimal Time for completing the product is: "<<productAssembly(a, t, e, x); 
 
    return 0; 
} 