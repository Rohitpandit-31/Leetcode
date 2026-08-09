class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        // suffix[i] = total stones from i to n-1
        vector<int> suffix(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        // dp[i][M] = maximum stones current player can get
        // starting from index i with current M
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = n - 1; i >= 0; i--) {

            for (int M = 1; M <= n; M++) {

                // If we can take all remaining piles
                if (i + 2 * M >= n) {
                    dp[i][M] = suffix[i];
                    continue;
                }

                int best = 0;

                // Try taking X piles
                for (int X = 1; X <= 2 * M && i + X <= n; X++) {

                    // Opponent starts at i + X
                    // with new M = max(M, X)
                    int opponent =
                        dp[i + X][max(M, X)];

                    // Total remaining - opponent's best
                    int current =
                        suffix[i] - opponent;

                    best = max(best, current);
                }

                dp[i][M] = best;
            }
        }

        return dp[0][1];
    }
};