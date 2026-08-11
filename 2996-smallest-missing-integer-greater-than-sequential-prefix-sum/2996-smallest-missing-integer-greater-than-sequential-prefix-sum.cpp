class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int n = nums.size();
        int sum = nums[0];
        for(int i = 1 ; i < n ; i++){
            if(nums[i] == nums[i - 1] + 1)
                sum += nums[i];
            else
                break;
            
        }
        bool present[101] = {};
        for(int x : nums)
            present[x] = true;

        while(sum <= 100 && present[sum])
            sum++;

        return sum;
    }
};