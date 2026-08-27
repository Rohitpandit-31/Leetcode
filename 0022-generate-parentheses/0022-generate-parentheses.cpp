class Solution {
public:
    vector<string> ans;

    void backtrack(string &cur, int open, int close, int n) {

        // If we used all parentheses
        if (cur.size() == 2 * n) {
            ans.push_back(cur);
            return;
        }

        // Add '(' if we still have some left
        if (open < n) {
            cur.push_back('(');
            backtrack(cur, open + 1, close, n);
            cur.pop_back();
        }

        // Add ')' only if it won't make the sequence invalid
        if (close < open) {
            cur.push_back(')');
            backtrack(cur, open, close + 1, n);
            cur.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        string cur;
        backtrack(cur, 0, 0, n);
        return ans;
    }
};