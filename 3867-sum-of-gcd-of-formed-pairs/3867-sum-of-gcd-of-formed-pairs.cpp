class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        vector<long long> prefixGcd;

        long long mx = 0;

        // Construct prefixGcd
        for (int x : nums) {
            mx = max(mx, (long long)x);
            prefixGcd.push_back(std::gcd((long long)x, mx));
        }

        // Sort in non-decreasing order
        sort(prefixGcd.begin(), prefixGcd.end());

        // Pair smallest with largest
        long long ans = 0;
        int i = 0;
        int j = prefixGcd.size() - 1;

        while (i < j) {
            ans += std::gcd(prefixGcd[i], prefixGcd[j]);
            i++;
            j--;
        }

        return ans;
    }
};