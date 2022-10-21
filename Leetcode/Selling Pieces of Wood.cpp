class Solution {
public:
    long long getResult(int m, int n, const vector<vector<int>>& maxPrice, vector<vector<long long>>& memo) {
        if (memo[m][n] != -1) return memo[m][n];
        
        // option 1: just take the price for the whole piece
        long long price = maxPrice[m][n];
        
        for (int h = 1; h < m; ++h) {
            // option 2: make 1 horizontal cut, take 2 prices for the smaller pieces
            price = max(price, getResult(m-h, n, maxPrice, memo) + getResult(h, n, maxPrice, memo));
        }
        
        for (int w = 1; w < n; ++w) {
            // option 3: make 1 vertical cut, take 2 prices
            price = max(price, getResult(m, n - w, maxPrice, memo) + getResult(m, w, maxPrice, memo));
        }
        
        return memo[m][n] = price;
    }
    
    long long sellingWood(int m, int n, vector<vector<int>>& prices) {
        // pre-calculate array for fast lookup of "price for piece of size h*w"
        vector<vector<int>> maxPrice(m+1, vector<int>(n+1, 0));
        for (const vector<int>& p : prices) {
            int h = p[0];
            int w = p[1];
            maxPrice[h][w] = p[2];
        }
        
        vector<vector<long long>> memo(m+1, vector<long long>(n+1, -1));
        return getResult(m, n, maxPrice, memo);
    }
};
