// Segment tree class for sum over range

class SegmentTree {

    private int defVal;     // Default value for queries
    private int arrLen;     // Size of the original array
    private int[] tree;     // Storage for the data structure
    
    /**
     * Constructor for the Segment Tree
     * @param arr = the original array
     */
    SegmentTree (int[] arr, int defVal) {
    
        this.defVal = defVal;
        arrLen = arr.length;
        tree = new int[2*arrLen];
        
        // Copy elements to the leaf nodes
        for (int i = 0; i<arrLen; ++i) {
            tree[i+arrLen] = arr[i];
        }
        // Alternative
        // System.arraycopy(arr, 0, tree, arraySize, arraySize);
        
        build();
    
    }
  
    /** the operation to perform */
    private int operation (int a, int b) {
        return a+b;
    }
    
    /** Initialize the inner nodes */
    public void build() {
        
        for (int i = arrLen-1; i>=1; --i) {
            // Parents are the sum of their children
            tree[i] = operation(tree[2*i], tree[2*i+1]);
        }
    
    }
    
    /**
     * Update the value at index i to val
     * @param i = the index to update
     * @param val = value to be added
     */
    void update (int i, int val) {
        
        i += arrLen;        // Increment i to its leaf node counterpart
        tree[i] += val;     // Update the leaf node
        i /= 2;             // Go to i's parent
        
        // Bubble up to i's parents until the root node
        for (; i>=1; i /= 2) {
            // Update the parents
            tree[i] = operation(tree[2*i], tree[2*i+1]);
        }
        
    }
    
    /**
     * Get the sum over the interval [l, r]
     * @param l = left most index
     * @param r = right most index
     * @return sum over [l, r]
     */
    int query (int l, int r) {
        
        // Increment l and r to their leaf node counterparts
        l += arrLen;
        r += arrLen;
      
        int sum = defVal;
    
        // While l and r are still left and right
        while (l<=r) {
            
            if (l%2==1) {                          // If l is the right child of the parent
                sum = operation(sum, tree[l]);     // Add the right child to the sum
                ++l;                               // Make l to the right child of the next branch
            }
            
            if (r%2==0) {                   	   // If r is the left child of its parent
                sum = operation(sum, tree[r]);     // Add the left child to the sum
                --r;               				   // Move r to the left child of the next branch
            }
          
            l /= 2, r /= 2;         // traverse to their parents
        
        }
        
        return sum;
    
    }

}
