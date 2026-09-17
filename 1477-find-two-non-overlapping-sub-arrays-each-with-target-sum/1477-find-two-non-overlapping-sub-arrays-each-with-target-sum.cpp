class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        
        // best[i] = minimum length of a valid subarray
        // completely within arr[0...i]
        vector<int> best(n, INT_MAX);

        int left = 0;
        long long sum = 0;
        int ans = INT_MAX;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            // Shrink window if sum becomes greater than target
            while (sum > target && left <= right) {
                sum -= arr[left];
                left++;
            }

            // We found a subarray [left...right] with sum = target
            if (sum == target) {
                int len = right - left + 1;

                // Check if there is a non-overlapping valid
                // subarray before this one
                if (left > 0 && best[left - 1] != INT_MAX) {
                    ans = min(ans, len + best[left - 1]);
                }

                // Store the shortest valid subarray ending
                // at or before right
                if (right == 0)
                    best[right] = len;
                else
                    best[right] = min(best[right - 1], len);
            } 
            else {
                // Carry forward the previous best
                if (right > 0)
                    best[right] = best[right - 1];
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};