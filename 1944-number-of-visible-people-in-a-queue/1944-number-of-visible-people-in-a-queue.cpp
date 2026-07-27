class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        int n = heights.size();
        vector<int> ans(n, 0);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {

            // Current person can see all shorter people
            while (!st.empty() && st.top() < heights[i]) {
                ans[i]++;
                st.pop();
            }

            // Can also see the first taller person
            if (!st.empty())
                ans[i]++;

            st.push(heights[i]);
        }

        return ans;
    }
};