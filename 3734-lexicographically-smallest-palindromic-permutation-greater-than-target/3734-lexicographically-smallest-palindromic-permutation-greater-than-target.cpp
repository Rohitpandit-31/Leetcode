class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        int m = n / 2;

        // Count characters
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        // Check palindrome possibility
        int odd = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
        }

        if (odd > 1)
            return "";

        // Count characters available in first half
        vector<int> halfCnt(26);

        for (int i = 0; i < 26; i++)
            halfCnt[i] = cnt[i] / 2;

        // Build palindrome from half
        auto build = [&](string half) {
            string ans = half;

            if (n % 2)
                ans += mid;

            for (int i = m - 1; i >= 0; i--)
                ans += half[i];

            return ans;
        };

        // ------------------------------------------------
        // CASE 1:
        // Try to make first half exactly equal to target
        // ------------------------------------------------

        vector<int> rem = halfCnt;
        string half = "";
        bool possible = true;

        for (int i = 0; i < m; i++) {
            int x = target[i] - 'a';

            if (rem[x] == 0) {
                possible = false;
                break;
            }

            half += target[i];
            rem[x]--;
        }

        // Important:
        // Even if the first half is equal, the middle/reverse
        // part can make the palindrome greater than target.
        if (possible) {
            string ans = build(half);

            if (ans > target)
                return ans;
        }

        // ------------------------------------------------
        // CASE 2:
        // Make the first half strictly greater
        // ------------------------------------------------

        for (int pos = m - 1; pos >= 0; pos--) {

            rem = halfCnt;
            string prefix = "";
            bool ok = true;

            // Match target before pos
            for (int i = 0; i < pos; i++) {
                int x = target[i] - 'a';

                if (rem[x] == 0) {
                    ok = false;
                    break;
                }

                prefix += target[i];
                rem[x]--;
            }

            if (!ok)
                continue;

            // Put smallest character > target[pos]
            for (int c = target[pos] - 'a' + 1; c < 26; c++) {

                if (rem[c] == 0)
                    continue;

                string h = prefix;
                h += char('a' + c);
                rem[c]--;

                // Fill remaining positions smallest first
                for (int x = 0; x < 26; x++) {
                    while (rem[x] > 0) {
                        h += char('a' + x);
                        rem[x]--;
                    }
                }

                string ans = build(h);

                if (ans > target)
                    return ans;
            }
        }

        return "";
    }
};