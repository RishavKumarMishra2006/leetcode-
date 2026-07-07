class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        long long total = 0;

        for (int x : nums) {
            long long add = sumIfFourDivisors(x);
            total += add;
        }
        return (int)total;
    }

private:
    bool isPrime(int n) {
        if (n < 2) return false;
        if (n % 2 == 0) return n == 2;
        for (int i = 3; 1LL * i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }

    long long sumIfFourDivisors(int n) {
        // Case 1: n = p^3
        int p = (int)round(cbrt((double)n));
        while (1LL * p * p * p < n) p++;
        while (1LL * p * p * p > n) p--;
        if (1LL * p * p * p == n && isPrime(p)) {
            // 1 + p + p^2 + p^3
            return 1LL + p + 1LL * p * p + n;
        }

        // Case 2: n = p*q (p != q, both prime)
        for (int i = 2; 1LL * i * i <= n; i++) {
            if (n % i == 0) {
                int a = i;
                int b = n / i;
                if (a != b && isPrime(a) && isPrime(b)) {
                    // divisors: 1, a, b, n
                    return 1LL + a + b + n;
                }
                return 0; // found a factor but not in correct form => can't have exactly 4 divisors
            }
        }

        return 0;
    }
};
