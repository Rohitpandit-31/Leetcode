class Solution {
public:
    static const long long LIMIT = 1000001LL;

    // Computes C(n, r), capped at LIMIT.
    long long comb(int n, int r) {
        if (r < 0 || r > n) return 0;
        r = min(r, n - r);

        long long ans = 1;

        for (int i = 1; i <= r; i++) {
            ans = ans * (n - r + i) / i;
            if (ans > LIMIT) return LIMIT;
        }

        return ans;
    }

    // Counts distinct permutations of the multiset represented by freq.
    long long countWays(vector<int>& freq) {
        int total = 0;
        for (int x : freq) total += x;

        long long ways = 1;
        int rem = total;

        for (int f : freq) {
            if (f == 0) continue;

            ways *= comb(rem, f);
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