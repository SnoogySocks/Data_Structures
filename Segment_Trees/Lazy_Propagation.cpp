// 03/2021
// Original source
// https://codeforces.com/blog/entry/18051

// SegmentTree class to calculate the sum given
// range updates nad queries. 
// The following is more readable code compared
// to the original source

#include <iostream>
#include <algorithm>
#include <vector>

class SegmentTree {

private:

    const int empty = -1;
    int arrLen, height;
    std::vector<int> tree, lazy;

    // (Only called for inner nodes)
    // Refresh the inner node if there is a pending modification
    void refresh (int node) {
        tree[node] = tree[node<<1]+tree[node<<1|1];
    }

    // Assign val to the current node
    void assign (int node, int nodeRange, int val) {

        // val*nodeRange simulates adding by 
        // val for each node in its range
        tree[node] = val*nodeRange;

        // Remember to update node's children
        if (node<arrLen)
            lazy[node] = val;

    }

public:

    SegmentTree (int arrLen) 
        : arrLen(arrLen), height(ceil(log2(arrLen))),
        tree(std::vector<int>(2*arrLen)), 
        lazy(std::vector<int>(arrLen, empty)) {
    }

    SegmentTree (const std::vector<int>& arr) : SegmentTree(arr.size()) {
        for (int i = 0; i<arrLen; ++i)
            tree[i+arrLen] = arr[i];
        build();
    }

    void build() {
        for (int node = arrLen-1; node>=1; --node)
            refresh(node);
    }

    void propagate (int node) {

        // Increment to the leaf node counterpart
        node += arrLen;

        // Traverse from root height to leaf height
        // (rootHeight = height, leafHeight = 1)
        for (int curHeight = height; curHeight>=1; --curHeight) {

            int curNode = node>>curHeight;
            int childRange = 1<<(curHeight-1);

            // Propagate the pending changes if any to curNode's children
            if (lazy[curNode]==empty) continue;
            assign(curNode<<1,   childRange, lazy[curNode]);
            assign(curNode<<1|1, childRange, lazy[curNode]);
            lazy[curNode] = empty;

        }

    }

    // Update all [l, r] to val
    void update (int l, int r, int val) {

        // Rejects values of empty since they 
        // are used to indicate lazy as empty
        if (val==empty) return;

        // Propagate pending changes up to the leaf nodes
        propagate(l);
        propagate(r);

        bool lHasChanged, rHasChanged;
        lHasChanged = rHasChanged = false;
        l += arrLen, r += arrLen;

        for (int nodeRange = 1; l<=r; l >>= 1, r >>= 1, nodeRange <<= 1) {

            // If a change was made to l-1/r+1's 
            // children, make the change to the 
            // parent as well
            if (lHasChanged) refresh(l-1);    // l-1 => previous l parent (or l's sibling)
            if (rHasChanged) refresh(r+1);    // r+1 => previous r parent (or r's sibling)

            if ((l&1)==1) assign(l++, nodeRange, val), lHasChanged = true;    // If l is right child, assign
            if ((r&1)==0) assign(r--, nodeRange, val), rHasChanged = true;    // If r is left child, assign

        }

        // Refresh to the root node
        for (--l, ++r; r>=1; l >>= 1, r >>= 1) {
            if (lHasChanged)
                refresh(l);
            if (rHasChanged&&(!lHasChanged||l!=r))
                refresh(r);
        }

    }

    // Quary from range [l, r]
    int query (int l, int r) {

        // Propagate pending changes up to the leaf nodes
        propagate(l);
        propagate(r);

        l += arrLen, r += arrLen;
        int res;
        for (res = 0; l<=r; l >>= 1, r >>= 1) {
            if ((l&1)==1) res += tree[l++];
            if ((r&1)==0) res += tree[r--];
        }
        return res;

    }

    int& operator[] (int i) {
        return tree[i+arrLen];
    }

};

// Test
const int mxN = 8;

int main() {

    SegmentTree seg(mxN);
    for (int i = 0; i<mxN; ++i)
        seg[i] = i;
    seg.build();
    seg.update(5, 6, 1);
    seg.update(0, 6, 2);
    seg.update(4, 5, 3);
    std::cout<<seg.query(0, mxN-1)<<'\n';
    
    return 0; 
}
