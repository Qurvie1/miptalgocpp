#include <iostream>

int Max(int a, int b) {
  return (a <= b ? b : a);
}

struct Pair {
  int cost;
  int weight;
};

void FindItems(Pair* items, int dp[101][10001], int index, int w) {
  if (dp[index][w] == 0) {
    return;
  }
  if (dp[index - 1][w] == dp[index][w]) {
    FindItems(items, dp, index - 1, w);
  } else {
    FindItems(items, dp, index - 1, w - items[index].weight);
    std::cout << index << '\n';
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  auto items = new Pair[n + 1]{};
  for (int i = 1; i < n + 1; ++i) {
    Pair pair;
    std::cin >> pair.weight;
    items[i] = pair;
  }
  for (int i = 1; i < n + 1; ++i) {
    std::cin >> items[i].cost;
  }
  int dp[101][10001];
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < m + 1; ++j) {
      if (j >= items[i].weight) {
        dp[i][j] = Max(dp[i - 1][j], dp[i - 1][j - items[i].weight] + items[i].cost);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  FindItems(items, dp, n, m);
  delete[] items;
  return 0;
}