class Solution {
public:
    vector<string> ans;

    void remove(string s, int last_i, int last_j, char open, char close) {

        int balance = 0;

        for (int i = last_i; i < s.size(); i++) {

            if (s[i] == open)
                balance++;

            if (s[i] == close)
                balance--;

            if (balance >= 0)
                continue;

            // s[0..i] has too many close parentheses
            for (int j = last_j; j <= i; j++) {

                if (s[j] == close &&
                    (j == last_j || s[j - 1] != close)) {

                    remove(
                        s.substr(0, j) + s.substr(j + 1),
                        i,
                        j,
                        open,
                        close
                    );
                }
            }

            return;
        }

        // No invalid close parentheses remain.
        // Reverse and solve the opposite direction.
        reverse(s.begin(), s.end());

        if (open == '(') {
            remove(s, 0, 0, ')', '(');
        }
        else {
            ans.push_back(s);
        }
    }

    vector<string> removeInvalidParentheses(string s) {

        remove(s, 0, 0, '(', ')');

        return ans;
    }
};