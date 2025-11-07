#include <stdio.h>
#include <stdlib.h>

struct ITEM {
  int noOfItem;
  int capacity;
  int *profit;
  int *weight;
  float *profitWeight;
};

int main() {
  struct ITEM *item = malloc(sizeof(struct ITEM));

  printf("Enter the number of items: ");
  scanf("%d", &item->noOfItem);

  printf("Enter the knapsack capacity: ");
  scanf("%d", &item->capacity);

  item->profit = malloc(item->noOfItem * sizeof(int));
  item->weight = malloc(item->noOfItem * sizeof(int));
  item->profitWeight = malloc(item->noOfItem * sizeof(float));

  for (int i = 0; i < item->noOfItem; i++) {
    printf("Enter the profit and weight of item %d: ", i + 1);
    scanf("%d %d", &item->profit[i], &item->weight[i]);
  }

  for (int i = 0; i < item->noOfItem; i++) {
    item->profitWeight[i] = (float)item->profit[i] / item->weight[i];
  }

  for (int i = 0; i < item->noOfItem - 1; i++) {
    for (int j = 0; j < item->noOfItem - i - 1; j++) {
      if (item->profitWeight[j] < item->profitWeight[j + 1]) {
        float tempRatio = item->profitWeight[j];
        item->profitWeight[j] = item->profitWeight[j + 1];
        item->profitWeight[j + 1] = tempRatio;

        int tempProfit = item->profit[j];
        item->profit[j] = item->profit[j + 1];
        item->profit[j + 1] = tempProfit;

        int tempWeight = item->weight[j];
        item->weight[j] = item->weight[j + 1];
        item->weight[j + 1] = tempWeight;
      }
    }
  }

  float totalProfit = 0.0;
  int remainingWeight = item->capacity;

  for (int i = 0; i < item->noOfItem; i++) {
    if (item->weight[i] <= remainingWeight) {
      totalProfit += item->profit[i];
      remainingWeight -= item->weight[i];
    } else {
      totalProfit += item->profit[i] * ((float)remainingWeight / item->weight[i]);
      break;
    }
  }

  printf("Maximum profit: %.5f\n", totalProfit);

  return 0;
}