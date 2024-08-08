/*Given an integer array nums, return the most frequent even element. If there is a tie, return the smallest one. If there is no such element, return -1.

Sample Input1:

6

4 4 4 9 2 4

Output:

4

Sample Input2:

7

0 1 2 2 4 4 1

Output:

2

Sample Input3:

8

29 47 21 41 13 37 25 7

Output:

-1

Input Format

line 1: number of elements

line 2: n integers (space separated)

8

0 1 2 3 4 4 4 8

Constraints

1<= nums.length <= 1000

0<=nums[i]<=999

Output Format

An even integer appearing most frequently, else -1

ex: 4

Sample Input 0

6
4 4 4 9 2 4
Sample Output 0

4
Sample Input 1

6
4 4 4 9 2 4
Sample Output 1

4
Sample Input 2

6
4 4 4 9 2 4
Sample Output 2

4*/

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);    
    int num[n];
    for(int i=0;i<n;i++){
        scanf("%d",&num[i]);  
    }

    int frequency[1001]={0};  

    for (int i=0;i<n;i++) {
        if (num[i]%2 == 0){
            frequency[num[i]]++; 
        }
    }

    int most=-1;
    int max=0;

    for (int i=0;i <= 1000;i++){ 
        if (frequency[i] > max){
            max= frequency[i];
            most= i;
        } 
        else if (frequency[i]==max && i<most){
            most= i;
        }
    }

    printf("%d\n", most);  

    return 0;
}
