class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int total = 0;
        int fuel = 0;
        int start = 0;
        int n = gas.size();
        for(int i = 0 ; i < n ; i++){
            int difference = gas[i] - cost[i];
            total += difference;
            fuel += difference;
            if(fuel < 0){
                start = i + 1;
                fuel = 0;
            }
        }

        return total >= 0 ? start : -1;

    }
};