class Solution {
public:
    vector<int> seg;
    int size;

    void build(vector<int>& gain) {
        int n = gain.size();

        size = 1;
        while (size < n)
            size <<= 1;

        seg.assign(2 * size, 0);

        for (int i = 0; i < n; i++)
            seg[size + i] = gain[i];

        for (int i = size - 1; i >= 1; i--)
            seg[i] = max(seg[2 * i], seg[2 * i + 1]);
    }

    int query(int l, int r) {
        if (l > r)
            return 0;

        l += size;
        r += size;

        int ans = 0;

        while (l <= r) {
            if (l & 1)
                ans = max(ans, seg[l++]);

            if (!(r & 1))
                ans = max(ans, seg[r--]);

            l >>= 1;
            r >>= 1;
        }

        return ans;
    }

    vector<int> maxActiveSectionsAfterTrade(
        string s,
        vector<vector<int>>& queries
    ) {
        int n = s.size();

        // Count original 1s
        int totalOnes = 0;

        for (char c : s) {
            if (c == '1')
                totalOnes++;
        }

        // Find all blocks of consecutive 1s
        vector<int> start, finish;

        for (int i = 0; i < n; ) {

            if (s[i] == '0') {
                i++;
                continue;
            }

            int j = i;

            while (j < n && s[j] == '1')
                j++;

            start.push_back(i);
            finish.push_back(j - 1);

            i = j;
        }

        int m = start.size();

        // gain[i] = number of zeroes surrounding
        // the i-th block of 1s
        vector<int> gain(m, 0);

        for (int i = 1; i + 1 < m; i++) {

            int leftZero =
                start[i] - finish[i - 1] - 1;

            int rightZero =
                start[i + 1] - finish[i] - 1;

            gain[i] = leftZero + rightZero;
        }

        build(gain);

        vector<int> answer;

        for (auto& q : queries) {

            int l = q[0];
            int r = q[1];

            // First 1-block whose start is > l
            int first =
                upper_bound(start.begin(), start.end(), l)
                - start.begin();

            // Last 1-block whose end is < r
            int last =
                lower_bound(finish.begin(), finish.end(), r)
                - finish.begin() - 1;

            // No valid 1-block
            if (first > last || first >= m || last < 0) {
                answer.push_back(totalOnes);
                continue;
            }

            int bestGain = 0;

            // -----------------------------------------
            // Only one candidate
            // -----------------------------------------
            if (first == last) {

                int i = first;

                int leftZero;

                if (i > 0 && finish[i - 1] >= l) {
                    leftZero =
                        start[i] - finish[i - 1] - 1;
                } else {
                    leftZero =
                        start[i] - l;
                }

                int rightZero;

                if (i + 1 < m && start[i + 1] <= r) {
                    rightZero =
                        start[i + 1] - finish[i] - 1;
                } else {
                    rightZero =
                        r - finish[i];
                }

                bestGain = leftZero + rightZero;
            }

            // -----------------------------------------
            // Multiple candidates
            // -----------------------------------------
            else {

                // First candidate
                {
                    int i = first;

                    int leftZero;

                    if (i > 0 && finish[i - 1] >= l) {
                        leftZero =
                            start[i] - finish[i - 1] - 1;
                    } else {
                        leftZero =
                            start[i] - l;
                    }

                    int rightZero =
                        start[i + 1] - finish[i] - 1;

                    bestGain =
                        max(bestGain,
                            leftZero + rightZero);
                }

                // Last candidate
                {
                    int i = last;

                    int leftZero =
                        start[i] - finish[i - 1] - 1;

                    int rightZero;

                    if (i + 1 < m && start[i + 1] <= r) {
                        rightZero =
                            start[i + 1] - finish[i] - 1;
                    } else {
                        rightZero =
                            r - finish[i];
                    }

                    bestGain =
                        max(bestGain,
                            leftZero + rightZero);
                }

                // Middle candidates
                if (first + 1 <= last - 1) {
                    bestGain =
                        max(bestGain,
                            query(first + 1, last - 1));
                }
            }

            answer.push_back(totalOnes + bestGain);
        }

        return answer;
    }
};