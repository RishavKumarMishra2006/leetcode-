

class Solution:
    def maxNumOfSubstrings(self, s: str) -> List[str]:
        n = len(s)
        a = [ord(ch) - 97 for ch in s]

        first = [n] * 26
        last = [-1] * 26
        for i, c in enumerate(a):
            if first[c] == n:
                first[c] = i
            last[c] = i

        def right_end(start: int) -> int:
            """Right end of the smallest valid substring beginning at `start`,
            or -1 if no valid substring can begin there."""
            end = last[a[start]]
            j = start
            while j <= end:
                c = a[j]
                if first[c] < start:  # would need a character from before `start`
                    return -1
                if last[c] > end:
                    end = last[c]
                j += 1
            return end

        res: List[str] = []
        prev_end = -1
        for i, c in enumerate(a):
            if i != first[c]:  # a valid substring can only start at a first occurrence
                continue
            end = right_end(i)
            if end == -1:
                continue
            if i > prev_end:
                res.append(s[i:end + 1])  # disjoint from the last pick
            else:
                res[-1] = s[i:end + 1]  # nested inside the last pick: keep the smaller one
            prev_end = end
        return res