#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();

        // last[j] stores the maximum index in word1 where word1[i] == word2[j]
        // matching right-to-left.
        vector<int> last(m, -1);
        int j = m - 1;
        for (int i = n - 1; i >= 0 && j >= 0; i--) {
            if (word1[i] == word2[j]) {
                last[j] = i;
                j--;
            }
        }

        vector<int> ans;
        bool canSkip = true; // Flag for our 1 allowed character change
        j = 0;

        for (int i = 0; i < n; i++) {
            if (j == m) break;

            // Option 1: Exact character match
            if (word1[i] == word2[j]) {
                ans.push_back(i);
                j++;
            } 
            // Option 2: Mismatch (change word1[i] to word2[j])
            else if (canSkip && (j == m - 1 || i < last[j + 1])) {
                canSkip = false;
                ans.push_back(i);
                j++;
            }
        }

        return j == m ? ans : vector<int>();
    }
};