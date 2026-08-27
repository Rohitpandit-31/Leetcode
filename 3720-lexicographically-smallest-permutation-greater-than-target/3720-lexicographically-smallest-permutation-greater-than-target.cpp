#include <string>
#include <vector>

class Solution {
public:
    std::string lexGreaterPermutation(std::string s, std::string target) {
        int n = s.length();
        std::vector<int> total_count(26, 0);
        for (char c : s) {
            total_count[c - 'a']++;
        }

        // Try matching the longest prefix target[0 ... i-1]
        for (int i = n - 1; i >= 0; --i) {
            std::vector<int> prefix_count(26, 0);
            for (int j = 0; j < i; ++j) {
                prefix_count[target[j] - 'a']++;
            }

            // Verify target[0 ... i-1] can be formed using available characters in s
            bool valid = true;
            for (int c = 0; c < 26; ++c) {
                if (prefix_count[c] > total_count[c]) {
                    valid = false;
                    break;
                }
            }
            if (!valid) continue;

            // Compute remaining counts after placing target[0 ... i-1]
            std::vector<int> remaining(26, 0);
            for (int c = 0; c < 26; ++c) {
                remaining[c] = total_count[c] - prefix_count[c];
            }

            // Find smallest available character strictly greater than target[i]
            int target_char = target[i] - 'a';
            int choice = -1;
            for (int c = target_char + 1; c < 26; ++c) {
                if (remaining[c] > 0) {
                    choice = c;
                    break;
                }
            }

            if (choice != -1) {
                std::string result = target.substr(0, i);
                result += static_cast<char>('a' + choice);
                remaining[choice]--;

                // Append remaining characters in ascending order
                for (int c = 0; c < 26; ++c) {
                    if (remaining[c] > 0) {
                        result.append(remaining[c], static_cast<char>('a' + c));
                    }
                }
                return result;
            }
        }

        return "";
    }
};