/*Hotel structure accepts the name of a room, its price per night and the area of the room in square feet. Write a code to initialise an array of 'n' hotel rooms from input. Pass the array to a function Ratio_Order. Calculate the squarefeet/price ratio for each of the rooms. Larger the ratio, the better it is for a customer. So sort the array in Descending order based on the ratios calculated and display. The displayed ratio must have two decimal values. Note that the price for a room is never 0. In case of a tie maintain the order same as in input.

Sample Input 1:

3

green 1000 1000

red 1000 2000

blue 1000 100

Sample Output 1:

red 1000 2000 2.00

green 1000 1000 1.00

blue 1000 100 0.10

Sample Input 2:

4

garden 10000 200

ocean 15000 500

skyline 12000 600

pool 11000 300

Sample Output 2:

skyline 12000 600 0.05

ocean 15000 500 0.03

pool 11000 300 0.03

garden 10000 200 0.02

Input Format

number of inputs room1_name room1_price room1_squarefeet room2_name room2_price room2_squarefeet

Constraints

NOT EXPLICIT CONSTRAINTS

Output Format

room1_name room1_price room1_squarefeet room1_ratio room2_name room2_price room2_squarefeet room2_ratio*/


#include <stdio.h>
#include <string.h>

typedef struct {
    char name[100];
    int price;
    int area;
    double ratio;
} HotelRoom;

void Ratio_Order(HotelRoom *h,int n){
    for (int i=0;i<n;i++){
        h[i].ratio=(double)h[i].area/h[i].price;
    }

    for (int i=0;i<n-1;i++){
        for(int j=0;j< n-i-1;j++){
            if (h[j].ratio < h[j+1].ratio){
                HotelRoom temp = h[j];
                h[j] = h[j+1];
                h[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d",&n);  
    HotelRoom h[n];
    for (int i=0;i<n;i++) {
        scanf("%s %d %d",h[i].name,&h[i].price,&h[i].area);
    }
    Ratio_Order(h,n);
    for (int i = 0; i < n; i++) {
        printf("%s %d %d %.2f\n",h[i].name,h[i].price,h[i].area,h[i].ratio);
    }
    return 0;
}
