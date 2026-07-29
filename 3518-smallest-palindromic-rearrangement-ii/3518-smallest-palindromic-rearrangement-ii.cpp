class Solution {
public:
    const long long LIMIT = 1000001LL;
    vector<vector<long long>> C;

    long long countWays(vector<int>& freq) {
        int total = 0;
        for (int x : freq) total += x;

        long long ways = 1;
        int rem = total;

        for (int f : freq) {
            if (f == 0) continue;

            ways *= C[rem][f];
            if (ways > LIMIT) ways = LIMIT;

            rem -= f;
        }

        return ways;
    }

    string smallestPalindrome(string s, int k) {

        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        vector<int> half(26, 0);
        string middle = "";
        int halfLen = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2)
                middle.push_back(char('a' + i));

            half[i] = freq[i] / 2;
            halfLen += half[i];
        }

        // Pascal's Triangle for nCr
        C.assign(halfLen + 1, vector<long long>(halfLen + 1, 0));

        for (int i = 0; i <= halfLen; i++) {
            C[i][0] = C[i][i] = 1;

            for (int j = 1; j < i; j++) {
                C[i][j] = min(LIMIT, C[i - 1][j - 1] + C[i - 1][j]);
            }
        }

        if (countWays(half) < k)
            return "";

        string left = "";

        for (int pos = 0; pos < halfLen; pos++) {

            for (int ch = 0; ch < 26; ch++) {

                if (half[ch] == 0)
                    continue;

                half[ch]--;

                long long ways = countWays(half);

                if (ways >= k) {
                    left.push_back(char('a' + ch));
                    break;
                }

                k -= ways;
                half[ch]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        return left + middle + right;
    }
};