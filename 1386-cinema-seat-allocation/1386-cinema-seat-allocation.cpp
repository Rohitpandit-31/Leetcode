class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        for (auto &x : reservedSeats)
            mp[x[0]] |= 1 << x[1];

        int ans = 2 * (n - mp.size());

        for (auto &[row, mask] : mp) {
            bool left  = !(mask & 0b000000111100);
            bool right = !(mask & 0b001111000000);
            bool mid   = !(mask & 0b000011110000);

            if (left && right)
                ans += 2;
            else if (left || right || mid)
                ans += 1;
        }

        return ans;
    }
};