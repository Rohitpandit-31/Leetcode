class Solution {
public:
    struct Node {
        char lc, rc;
        int pre, suf, best, len;

        Node() : lc(0), rc(0), pre(0), suf(0), best(0), len(0) {}

        Node(char c) {
            lc = rc = c;
            pre = suf = best = len = 1;
        }
    };

    vector<Node> seg;

    Node merge(Node &a, Node &b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;

        res.len = a.len + b.len;
        res.lc = a.lc;
        res.rc = b.rc;

        // Prefix
        res.pre = a.pre;
        if (a.pre == a.len && a.rc == b.lc)
            res.pre = a.len + b.pre;

        // Suffix
        res.suf = b.suf;
        if (b.suf == b.len && a.rc == b.lc)
            res.suf = b.len + a.suf;

        // Best
        res.best = max(a.best, b.best);

        if (a.rc == b.lc)
            res.best = max(res.best, a.suf + b.pre);

        return res;
    }

    void build(int node, int l, int r, string &s) {
        if (l == r) {
            seg[node] = Node(s[l]);
            return;
        }

        int mid = l + (r - l) / 2;

        build(node * 2, l, mid, s);
        build(node * 2 + 1, mid + 1, r, s);

        seg[node] = merge(seg[node * 2], seg[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, char c) {
        if (l == r) {
            seg[node] = Node(c);
            return;
        }

        int mid = l + (r - l) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, c);
        else
            update(node * 2 + 1, mid + 1, r, idx, c);

        seg[node] = merge(seg[node * 2], seg[node * 2 + 1]);
    }

    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {

        int n = s.size();

        seg.resize(4 * n);

        build(1, 0, n - 1, s);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {

            int idx = queryIndices[i];
            char c = queryCharacters[i];

            update(1, 0, n - 1, idx, c);

            ans.push_back(seg[1].best);
        }

        return ans;
    }
};