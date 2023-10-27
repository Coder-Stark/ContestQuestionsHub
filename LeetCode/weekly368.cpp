#include<bits/stdc++.h>
using namespace std;

//01. MINIMUM SUM OF MOUNTAIN TRIPLETS I                                         {T.C = O(N^3), S.C = O(1)}
//APPROACH
//brute force - use 3 for loops 1st loop mountain(peak element) then prev peak and then after peak elements
//if peak is more then prev and after peak then add all elements and return it
class Solution {
public:
    int minimumSum(vector<int>& nums) {
        int n = nums.size();
        int mini = INT_MAX;
        for(int j = 1 ; j < n ; j++){
            for(int i = 0 ; i < j ; i++){
                for(int k = j+1 ; k < n ; k++){
                    if(nums[i] < nums[j] && nums[k] < nums[j]){
                        int sum = nums[i]+nums[j]+nums[k];
                        mini = min(mini, sum);
                    }
                }
            }
        }
        if(mini == INT_MAX){
            return -1;
        }
        return mini;
    }
};
/*
Input: nums = [8,6,1,5,3]
Output: 9
Explanation: Triplet (2, 3, 4) is a mountain triplet of sum 9 since: 
- 2 < 3 < 4
- nums[2] < nums[3] and nums[4] < nums[3]
And the sum of this triplet is nums[2] + nums[3] + nums[4] = 9. It can be shown that there are no mountain triplets with a sum of less than 9.
*/


//02. MINIMUM SUM OF MOUNTAIN TRIPLETS II                                         {T.C = O(N), S.C = O(N)}
//APPROACH
//optimized version of above code - using prefix(minimum element before peak element) and suffix(minimum element after peak element) then
//iterate from index 1 to n-1 and store minimum sum
class Solution {
public:
    int minimumSum(vector<int>& nums) {
        int n = nums.size();
        
        vector<int>prefix(n);                  //stores left minimum element
        vector<int>suffix(n);                  //stores right minimum element
        
        int mini = nums[0];
        
        for(int i = 0 ; i < n ; i++){
            mini = min(mini, nums[i]);
            prefix[i] = mini;
        }
        
        int mini2 = nums[n-1];
        for(int i = n-1 ; i >= 0 ;i--){
            mini2 = min(mini2, nums[i]);
            suffix[i] = mini2;
        }
        
        int ans = INT_MAX;
        for(int j = 1 ; j < n-1 ; j++){
            if(prefix[j-1] < nums[j] && suffix[j+1] < nums[j]){
                int sum = prefix[j-1] + nums[j] + suffix[j+1];
                ans = min(ans, sum);
            }
        }
        if(ans == INT_MAX){
            return -1;
        }
        return ans;
    }
};
/*
Input: nums = [8,6,1,5,3]
Output: 9
Explanation: Triplet (2, 3, 4) is a mountain triplet of sum 9 since: 
- 2 < 3 < 4
- nums[2] < nums[3] and nums[4] < nums[3]
And the sum of this triplet is nums[2] + nums[3] + nums[4] = 9. It can be shown that there are no mountain triplets with a sum of less than 9.
*/


//03. MINIMUM NUMBER OF GROUPS TO CREATE A VALID ASSIGNMENT                                     {T.C = O(N*LOGN), S.C = O(N)}
//APPROACH
//This solution counts the frequencies of elements in 'nums,' then iterates through potential group sizes to find the minimum 
//number of groups needed to distribute the elements, considering constraints on group sizes.
class Solution 
{
public:
    int minGroupsForValidAssignment(vector<int>& nums) 
    {
        // Create a map to count the frequency of each element in 'nums'.
        map<int, int> mp;
        // Create a vector to store the frequency values.
        vector<int> v;
        for(auto it : nums)
            mp[it] ++;
        // Transfer the frequency values to the 'v' vector and sort it.
        for(auto it : mp)
        {
            v.push_back(it.second);
        }
        sort(v.begin(), v.end());
        int ans = INT_MAX;

        // Iterate through possible group sizes, starting from 1 to the maximum frequency.
        for(int i = 1; i <= v[0]; i++)
        {
            int a = i, b = i+1;
            int num = 0;
            bool bad = false;

            // Iterate through the frequencies of elements and calculate the minimum
            // number of groups required for each frequency.
            for(int i = 0; i < v.size(); i ++)
            {
                int cur = v[i];
                int mn = INT_MAX, cnt = 0;
                // Calculate the minimum groups required for the current frequency.
                while(cur >= 0)
                {
                    if(cur % a == 0) mn = cnt+cur/a;
                    cur -= b;
                    cnt ++;
                }
                // If 'mn' is still INT_MAX, it means it's not possible to form groups.
                if(mn == INT_MAX)
                {
                    bad = true;
                    break;
                }
                num += mn;
            }

            // If no bad configurations were encountered, update the answer.
            if(!bad)
                ans = min(ans, num);
        }
        return ans;
    }
};
/*
Input: nums = [3,2,3,2,3]
Output: 2
Explanation: One way the indices can be assigned to 2 groups is as follows, where the values in square brackets are indices:
group 1 -> [0,2,4]
group 2 -> [1,3]
All indices are assigned to one group.
In group 1, nums[0] == nums[2] == nums[4], so all indices have the same value.
In group 2, nums[1] == nums[3], so all indices have the same value.
The number of indices assigned to group 1 is 3, and the number of indices assigned to group 2 is 2.
Their difference doesn't exceed 1.
It is not possible to use fewer than 2 groups because, in order to use just 1 group, all indices assigned to that group must have the same value.
Hence, the answer is 2.
*/