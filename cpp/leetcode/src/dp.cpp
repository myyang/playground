
// #70
int climbing_stairs(int n)
{
    if (n <= 0) return 0;
    int dp1 = 1, dp2 = 1, cur = 1;
    for (int i = 2; i <= n; ++i)
    {
        cur = dp1 + dp2;
        dp1 = dp2;
        dp2 = cur;
    }
    return cur;
}

// #1137
int tribonacci(int n)
{
    if (n <= 0) return 0;
    int dp0 = 0, dp1 = 1, dp2 = 1, cur = 1;
    for (int i = 3; i <= n; ++i)
    {
        cur = dp0 + dp1 + dp2;
        dp0 = dp1;
        dp1 = dp2;
        dp2 = cur;
    }
    return cur;
}
