class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int left = 0;
        int ones = 0;

        int bestStart = -1;
        int bestLen = INT_MAX;

        for (int right = 0; right < n; right++) {
            if (s[right] == '1')
                ones++;

            // Keep exactly k ones
            while (ones > k) {
                if (s[left] == '1')
                    ones--;
                left++;
            }

            // We have exactly k ones
            if (ones == k) {
                // Remove leading zeros to make substring shortest
                while (s[left] == '0')
                    left++;

                int len = right - left + 1;

                if (len < bestLen) {
                    bestLen = len;
                    bestStart = left;
                }
                else if (len == bestLen) {
                    // Compare without creating substrings
                    int i = 0;

                    while (i < len && 
                           s[bestStart + i] == s[left + i]) {
                        i++;
                    }

                    if (i < len && s[left + i] < s[bestStart + i])
                        bestStart = left;
                }
            }
        }

        if (bestStart == -1)
            return "";

        return s.substr(bestStart, bestLen);
    }
};