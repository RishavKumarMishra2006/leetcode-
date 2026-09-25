class Solution {
public:
    string s;
    int pos;

    set<string> unite(const set<string>& A, const set<string>& B) {
        set<string> result = A;
        result.insert(B.begin(), B.end());
        return result;
    }

    set<string> multiply(const set<string>& A, const set<string>& B) {
        set<string> result;

        for (const string& a : A) {
            for (const string& b : B) {
                result.insert(a + b);
            }
        }

        return result;
    }

    // expression := term (',' term)*
    set<string> parseExpression() {
        set<string> result = parseTerm();

        while (pos < s.size() && s[pos] == ',') {
            pos++;  // skip ','
            result = unite(result, parseTerm());
        }

        return result;
    }

    // term := factor*
    set<string> parseTerm() {
        set<string> result = {""};

        while (pos < s.size() && s[pos] != '}' && s[pos] != ',') {
            set<string> next = parseFactor();
            result = multiply(result, next);
        }

        return result;
    }

    // factor := letter | '{' expression '}'
    set<string> parseFactor() {
        if (s[pos] == '{') {
            pos++;  // skip '{'

            set<string> result = parseExpression();

            pos++;  // skip '}'

            return result;
        }

        // lowercase letter
        string ch(1, s[pos]);
        pos++;

        return {ch};
    }

    vector<string> braceExpansionII(string expression) {
        s = expression;
        pos = 0;

        set<string> result = parseExpression();

        return vector<string>(result.begin(), result.end());
    }
};