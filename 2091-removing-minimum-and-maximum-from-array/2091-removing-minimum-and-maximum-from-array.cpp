class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minIndex = 0;
        int maxIndex = 0;

        for(int i = 0 ; i < n ; i++){
            if(nums[i] < nums[minIndex])
                minIndex = i;

            if(nums[i] > nums[maxIndex])
                maxIndex = i;
        }
        if (minIndex > maxIndex)
            swap(minIndex, maxIndex);

        // 1. Remove both from left
        int left = maxIndex + 1;

        // 2. Remove both from right
        int right = n - minIndex;

        // 3. Remove min from left and max from right
        int both = (minIndex + 1) + (n - maxIndex);

        return min({left, right, both});
    }
};