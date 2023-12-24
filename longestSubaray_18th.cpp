#include <iostream>
using namespace std;

/*
          Q. longest subarray with given sum (positives)
    explanation - longest subarray with sum k,       subarray - contiguous part of the array
    arr[] = {1, 2, 3, 1, 1, 1, 1, 4, 2, 3}

    sol- Brute fore - can we say that subarray can move like- {1}, {2}, {3}, ...
                             next - {1, 2}, {1, 2, 3}, {1, 2, 3, 1}, {1, 2, 3, 1, 1}, ...
                             next - {2, 3}, {2, 3, 1}, {2, 3, 1, 1}, {2, 3, 1, 1, 1}, ...
                                    {3, 1}, {3, 1, 1}, {3, 1, 1, 1}, and so on

                        for this solution, we place both i and j at the index 0, while i being
                        at index 0 we move j to next index. after that we move j to next index
                        everytime j moves forward, i to j creates a subarray(till j reaches last array)     // entire array is also a subarray

                        then we move i and j to next index(index 1), while i being at index 1 we
                        move j to next index and after that next index in similar fashion till
                        last index

        pseudo code
len = 0                     // longestLength
for(i=0->n)
{
    for(j=i->n)
    {
        sum = 0
        for(k=i->j)
        {
            sum += a[k]
        }
        if(sum == k)
            len = max(len, j-i+1)           // length b/w i to j is -  "j-i+1"
    }
}
print(len)


                TC - O(n^3)     // nearly
                SC - O(1)

        to improve time complexity of brute force, we can write as
len = 0                     // longestLength
for(i=0->n)
{
    s = 0
    for(j=i->n)
    {
        s += a[j]

        if(sum == k)                
            len = max(len, j-i+1)
    }
}
print(len)


                from above brute TC = O(n^2)        //nearly
                                                    // this solution of brute force and this TC, will explained to the interviewer



                                 Better sol -  will use hashing

                                                lets take an array {1, 2, 3, 4, 5, 6}  and its sum is x
                                                here take 5, and make prefix sum(means sum of all the previous elements till 5) = k
                                                now make subarrays where 5 is the last element(we can say {5}, {4, 5}, {3, 4, 5}
                                                {2, 3, 4, 5}, {1, 2, 3, 4, 5}), there are 5 subarrays for that

                                                if there exists a subarray with sum 'k' as '5' as the last element
                                                let that array be {3, 4, 5}
                                                by this we can say that, 
                                                            if {1, 2, 3, 4, 5} sum is x
                                                            & {3, 4, 5} sum is k
                                                            then {1, 2} sum is 'x - k'

                                                by using this reverse mathmatics we can we can get the subarray of sum 'k' with 
                                                the help of 'x - k' and we can do this with every element by makin them last element
                                                of subarray

                                                lets create a hashing table for {1, 2, 3, 1, 1, 1, 1, 4, 2, 3}, take k = 3
                                                now take index 0 where element is 1 and prefix sum will be 1, so in hashing table
                                                we put  |1, 0|          // 1 for sum and 0 for index

                                                then take index 1 where element is 2 and prefix sum will be 3, whih is our desired o/p
                                                and length is 2,  in hashing table  |3, 1|          // 3 for sun and 1 for index

                                                take index 2 with element 3 and pre sum is 6, by applying reverse mathmetics we get sum 3
                                                x = 6, k=3 by reverse math x-k = 3 we got our desired sum but the length is 1 which is not 
                                                the longest so we will not take it as desired o/p,  in hash table  |6, 2|

                                                take index 3 with element 1 and pre sum is 7, by reverse math there must be a x - k = 3
                                                but there is none, so we will not take it. we put in hash table |7, 3|

                                                take index 4 with element 1 and pre sum is 8, by reverse math there must be a x - k = 5
                                                but there is none, so we will not take it. we put in hash table |8, 4|

                                                take index 5 with element 1 and pre sum is 9, by applying reverse mathmetics we get sum 3
                                                x = 9, k=3 by reverse math x-k = 6 we got our desired sum(k=3) and the length is 6 which is
                                                the longest so we will take it as desired o/p,  in hash table  |9, 5|

        Actual code         (this code is optimal if there is positive, zero and negative in the array)
int longestSubarrayWithSumK(vector<int> a, long long k)
{
    map<long long, int> preSumMap;
    long long sum = 0;
    int maxLen = 0;
    for(int i = 0; i < a.size(); i++)
    {
        sum += a[i];
        if(sum == k)
        {
            maxLen = max(maxLen, i+1);
        }
        long long rem = sum - k;                    // rem for remaining
        if(preSumMap.find(rem) != preSumMap.end())
        {
            int len = i - preSumMap[rem];
            maxLen = max(maxLen, len);
        }
        if(preSumMap.find(sum) == preSumMap.end())        // when there is zero in the array
        {
            preSumMap[sum] = 1;
        }
    }
    return maxLen;
}


                TC -  O(N*log N)        // for ordered map, if there is no collisions
                      O(N * 1)          // for unordered map
                SC - O(N)



                            OPtimal sol -  2 pointer approach           // when array contains onle positive and zeroes

                                        arr[] = {1, 2, 3, 1, 1, 1, 1, 3, 3},  k = 6

                    explanation -  we place 2 pointers at index 0 then we move second pointer in fwd direction untill we get
                                    our reqd sum, if we exceed our sum then we move first pointer in fwd direction
                            exa- we place both of the pointer at element 1, we move 2nd pntr till 3 where we get our desired 
                                 sum and len = 3
                                 then we move 2nd pntr to 1(index 3) but here we exceed our sum so we move 1st pntr to index 1,
                                 here we get our sum (i.e {2, 3, 1}) and len = 3

                                 then we move 2nd pntr to 1(index 4) but here we exceed our sum so we move 1st pntr to index 2,
                                 here we get sum as 5 (i.e {3, 1, 1}),  we will not take this condition

                                 then we move 2nd pntr to 1(index 5) but here we got our sum (i.e {3, 1, 1, 1}) and len = 4

                                 then we move 2nd pntr to 1(index 6) but here we exceed our sum so we move 1st pntr to index 3,
                                 here we get sum as (i.e {1, 1, 1, 1}), we will not take this condition

                                 then we move 2nd pntr to 3(index 7) but here we exceed our sum so we move 1st pntr to index 4,
                                 here we get our sum (i.e {1, 1, 1, 3}) and len = 4

                                 then we move 2nd pntr to 3(index 8) but here we exceed our sum so we move 1st pntr to index 5,
                                 here we again exceeded our sum (i.e {1, 1, 3, 3}), so again moving 1st pointer to index 6 which 
                                 again exceeded sum (i.e {1, 3, 3}), again moving 1st pntr to index 7 we got our sum 
                                 (i.e {3, 3}) and len = 2, which is not the longest

                                 again 2nd move out of the array

        Actual code         (this solution is optimal if there only positive and zeroes in the array)
int longestSubarrayWithSumK(vector<int> a, long long k)
{
    int left = 0, right = 0;
    long long sum = a[0];           // bcz initially pntrs are at 0, so sum will be a[0]
    int maxLen = 0;
    int n = a.size();
    while(right < n)
    {
        while(left <= right && sum > k)
        {
            sum -= a[left];
            left++;
        }
        if(sum == k)
        {
            maxLen = max(maxLen, right - left + 1);
        }
        right++;
        if(right < n)
            sum += a[right];
    }
    return maxLen;
}

                
                TC -  O(2N)
                SC -  O(1)
 */

int main()
{
    cout << "Hello World!\n";
}