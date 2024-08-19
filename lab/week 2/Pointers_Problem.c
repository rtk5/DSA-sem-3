/*Alice is a digital artist who loves playing with numbers and strings. One day, she came across a challenge involving a string of digits. The challenge was to transform the string into the lexicographically smallest possible string by performing at most one swap of adjacent digits. However, there is a twist: you can only swap adjacent digits that have the same parity.

Digits are considered to have the same parity if both are even or both are odd. For example, '2' and '4' are both even and have the same parity, while '2' and '3' have different parity.

Alice needs your help to solve this challenge. Given a string s containing only digits, return the lexicographically smallest string that can be obtained after swapping adjacent digits with the same parity at most once.

Your task is to complete the below function

Function Signature:

void lexicographically_smallest_string(char *s);

Test case -1

Input: "45320"

Output: "43520"

Explanation:

The only adjacent digits with the same parity are '5' and '3'. Swapping them results in "43520", which is the smallest possible string.

Test-case-2

Input: "001"

Output: "001"

Explanation:

No adjacent digits with the same parity can be swapped to make the string smaller. The string is already the smallest possible.

Input Format

A single string contains only digits (0-9). The length of the string is between 1 and 100.

Constraints

No explicit constraints.

Output Format

The lexicographically smallest string that can be obtained.*/


#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void lexi(char *s) {
    int len = strlen(s);
    
    for (int i = 0; i < len - 1; i++) {
        if ((s[i] % 2 == s[i + 1] % 2) && s[i] > s[i + 1]) {
            char temp = s[i];
            s[i] = s[i + 1];
            s[i + 1] = temp;
            break; 
        }
    }
}

int main() {
    char s[100];
  
    scanf("%s", s);
  
    lexi(s);
  
    printf("%s\n", s);
  
    return 0;
}