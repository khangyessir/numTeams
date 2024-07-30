class FenwickTree {
public:
    FenwickTree(int size) : sums(size + 1, 0) {}

    void update(int i, int delta) {
        while (i < sums.size()) {
            sums[i] += delta;
            i += i & -i;
        }
    }

    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += sums[i];
            i -= i & -i;
        }
        return sum;
    }

private:
    vector<int> sums;
};

class Solution {
public:
    int numTeams(vector<int>& rating) {
        int n = rating.size();
        int maxVal = *max_element(rating.begin(), rating.end());
        FenwickTree fenwickLeft(maxVal), fenwickRight(maxVal);        
        for (int r : rating) {
            fenwickRight.update(r, 1);
        }
        int ans = 0;

        for (int r : rating) {
            fenwickRight.update(r, -1);
            int leftLess = fenwickLeft.query(r - 1);
            int leftGreater = fenwickLeft.query(maxVal) - fenwickLeft.query(r);
            int rightLess = fenwickRight.query(r - 1);
            int rightGreater = fenwickRight.query(maxVal) - fenwickRight.query(r);

            ans += leftLess * rightGreater + leftGreater * rightLess;
            
            fenwickLeft.update(r, 1);
        }        
        return ans;
    }
};
