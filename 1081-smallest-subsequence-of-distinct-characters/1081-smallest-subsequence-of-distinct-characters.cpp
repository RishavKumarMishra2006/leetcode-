class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> cnt(26, 0);
        vector<bool> vis(26, false);

        for (char c : s)
            cnt[c - 'a']++;

        stack<char> st;

        for (char ch : s) {
            cnt[ch - 'a']--;

            if (vis[ch - 'a'])
                continue;

            while (!st.empty() &&
                   st.top() > ch &&
                   cnt[st.top() - 'a'] > 0) {
                vis[st.top() - 'a'] = false;
                st.pop();
            }

            st.push(ch);
            vis[ch - 'a'] = true;
        }

        string ans;
        while (!st.empty()) {
            ans += st.top();
            st.pop();
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};