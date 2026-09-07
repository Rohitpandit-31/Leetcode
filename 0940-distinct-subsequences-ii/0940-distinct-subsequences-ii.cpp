class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1e9 + 7;

        vector<long long> dp(26, 0);

        long long total = 0;

        for (char c : s) {
            int idx = c - 'a';

            // New subsequences ending with c
            long long newSubseq = (total + 1) % MOD;

            // Replace old subsequences ending with c
            total = (total + newSubseq - dp[idx] + MOD) % MOD;

            dp[idx] = newSubseq;
        }

        return total;
    }
};