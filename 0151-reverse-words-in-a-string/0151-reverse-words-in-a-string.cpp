class Solution {
public:
    string reverseWords(string s) {
        string ans;
        int i = s.size() - 1;
        while( i >= 0){
            while(i >= 0 && s[i] == ' ')
                i--;
            if(i < 0)
                break;
            int end = i;
            while(i >= 0 && s[i] != ' ')
                i--;
            int start = i + 1;

            if(!ans.empty())
                ans += " ";

            ans += s.substr(start , end - start + 1);
        
        }
        return ans;
    }
};