class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> firstArray = {nums[0]};
        vector<int> secondArray = {nums[1]};
        for(int i = 2 ; i < n ; ++i){
            if(firstArray.back() > secondArray.back()){
                firstArray.push_back(nums[i]);
            }
            else{
                secondArray.push_back(nums[i]);
            }
        }
        firstArray.insert(firstArray.end() , secondArray.begin() , secondArray.end());

        return firstArray;
    }
};