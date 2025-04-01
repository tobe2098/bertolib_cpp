#ifndef BERTOLIB_ALGORTHM_LIBRARY_HEADER
#define BERTOLIB_ALGORTHM_LIBRARY_HEADER

#include <array>
#include <vector>

static constexpr int LIMIT = 8;

void radix(std::vector<int>& nums, int bits, int min_num, int mask, int shifts, std::vector<std::vector<int>>& buckets) {
  // if (__popcnt(mask)!=bits) throw;
  for (int n : nums) {
    buckets[(n + min_num & mask) >> (bits * shifts)].push_back(n);
  }
  int i {};
  for (std::vector<int>& b : buckets) {
    for (int n : b) {
      nums[i++] = n;
    }
    b.clear();
  }
}
void merge(std::vector<int>& nums, int left, int mid, int right, std::vector<int>& temp) {
  int i = left;
  int j = mid;
  int k = left;

  while (i < mid && j < right) {
    if (nums[i] <= nums[j]) {
      temp[k++] = nums[i++];
    } else {
      temp[k++] = nums[j++];
    }
  }

  while (i < mid) {
    temp[k++] = nums[i++];
  }

  while (j < right) {
    temp[k++] = nums[j++];
  }

  for (int i = left; i < right; ++i) {
    nums[i] = temp[i];
  }
}
void mergeSort(std::vector<int>& nums) {
  int              n = nums.size();
  std::vector<int> temp(n);
  for (int size = 1; size < n; size *= 2) {
    for (int left = 0; left + size < n; left += 2 * size) {
      int mid { std::min(left + size, n) };
      int right { std::min(left + 2 * size, n) };
      merge(nums, left, mid, right, temp);
    }
  }
}
void merge2(std::vector<int>& nums, int start, int end, std::vector<int>& temp) {
  if (end - start <= 1) {
    return;
  }
  int mid { (start + (end - start) / 2) };
  merge2(nums, start, mid, temp);
  merge2(nums, mid, end, temp);
  int p1 { start }, p2 { mid }, k { p1 };
  while (p1 < mid && p2 < end) {
    if (nums[p1] > nums[p2]) {
      temp[k++] = nums[p2++];
    } else {
      temp[k++] = nums[p1++];
    }
  }
  while (p1 < mid) {
    temp[k++] = nums[p1++];
  }
  while (p2 < end) {
    temp[k++] = nums[p2++];
  }
  for (int i = start; i < end; i++) {
    nums[i] = temp[i];
  }
}
void mergeSort2(std::vector<int>& nums) {
  std::vector<int> temp(nums.size());
  merge2(nums, 0, nums.size(), temp);
}
std::vector<int> radixSortAll(std::vector<int>& nums) {
  std::vector<int> negs, pos;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] < 0) {
      negs.push_back(nums[i]);
    } else {
      pos.push_back(nums[i]);
    }
  }
  std::array<std::vector<int>, 2> buckets {};
  int                             mask { 1 };
  for (int i = 0; i < 31; i++, mask <<= 1) {
    for (int n : pos) {
      buckets[(n & mask) >> i].push_back(n);
    }
    int j {};
    for (std::vector<int>& b : buckets) {
      for (int n : b) {
        pos[j++] = n;
      }
      b.clear();
    }
    for (int n : negs) {
      buckets[(n & mask) >> i].push_back(n);
    }
    j = 0;
    for (std::vector<int>& b : buckets) {
      for (int n : b) {
        negs[j++] = n;
      }
      b.clear();
    }
  }
  negs.insert(negs.end(), pos.begin(), pos.end());
  return negs;
}
int getMedianIndex(int a, int aidx, int b, int bidx, int c, int cidx) {
  if (a > b) {
    if (c > a) {
      return aidx;
    } else if (c > b) {
      return cidx;
    } else {
      return bidx;
    }
  } else {
    if (c > b) {
      return bidx;
    } else if (c > a) {
      return cidx;
    } else {
      return aidx;
    }
  }
}
void quicksortInPlace(std::vector<int>& nums, int start, int end) {
  if (end - start <= 0) {
    return;
  }
  int mid { start + (end - start) / 2 };
  int medianIdx { getMedianIndex(nums[start], start, nums[mid], mid, nums[end], end) };
  std::swap(nums[start], nums[medianIdx]);
  int p1 { start + 1 }, p2 { end };
  while (p1 < p2) {
    if (nums[p1] > nums[start] && nums[p2] < nums[start]) {
      std::swap(nums[p1++], nums[p2--]);
    } else if (nums[p1] > nums[start]) {
      p2--;
    } else if (nums[p2] < nums[start]) {
      p1++;
    } else {
      p1++;
      p2--;
    }
  }
  if (nums[p2] > nums[start]) {
    std::swap(nums[start], nums[p2 - 1]);
    mid = p2 - 1;
  } else {
    std::swap(nums[start], nums[p2]);
    mid = p2;
  }
  quicksortInPlace(nums, start, mid - 1);
  quicksortInPlace(nums, mid + 1, end);
}
void maxHeapify(std::vector<int>& v, int index, int n) {
  int val { v[index] };
  int first { 2 * index + 1 };
  while (first < n) {
    if (first < n - 1 && v[first + 1] >= v[first]) {
      first++;
    }
    if (val > v[first]) {
      break;
    } else {
      v[(first - 1) / 2] = v[first];
      first              = 2 * first + 1;
    }
  }
  v[(first - 1) / 2] = val;
  return;
}

void makeMaxHeap(std::vector<int>& v, int n) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    maxHeapify(v, i, n);
  }
}
void heapSort(std::vector<int>& nums) {
  makeMaxHeap(nums, nums.size());
  for (int i = nums.size() - 1; i >= 0; i--) {
    std::swap(nums[0], nums[i]);
    maxHeapify(nums, 0, i);
  }
}

void heapSort2(std::vector<int>& nums) {
  const int n = nums.size();
  for (int i = n / 2 - 1; i >= 0; i--) {
    maxHeapify(nums, i, n);
  }
  for (int i = n - 1; i > 0; i--) {
    std::swap(nums[0], nums[i]);
    maxHeapify(nums, 0, i);
  }
}

void swapSort(std::vector<int>& nums) {
  for (int i = 1; i < nums.size(); i++) {
    int c { i };
    for (int j = i - 1; j >= 0; j--) {
      if (nums[j] > nums[c]) {
        std::swap(nums[j], nums[c]);
        c = j;
      } else {
        break;
      }
    }
  }
}
std::vector<int> countSort(std::vector<int>& nums) {
  vector<int> counting(2 * 50000 + 1, 0);
  for (int num : nums) {
    // we add 5 * 10^4 because for smallest possible element -5 * 10^4 index must be 0
    counting[num + 50000]++;
  }
  int write_ind = 0;
  for (int number_ind = 0; number_ind < counting.size(); ++number_ind) {
    int freq = counting[number_ind];
    while (freq != 0) {
      nums[write_ind] = number_ind - 50000;
      write_ind++;
      freq--;
    }
  }
  return nums;
}

void min_max(const vector<int>& nums, int& MIN, int& MAX) const {
  MIN = nums[0];
  MAX = nums[0];

  for (int i = 1; i < nums.size(); ++i) {
    if (nums[i] > MAX) {
      MAX = nums[i];
    } else if (nums[i] < MIN) {
      MIN = nums[i];
    }
  }
}

int index(const int MIN, const int MAX, const int size, const int val) const {
  return size * (long int)(val - MIN) / (MAX - MIN + 1);
}

void bucket_sort(vector<int>& nums, const int MIN, const int MAX) const {
  const int           BUCKET = nums.size();
  vector<vector<int>> data(BUCKET);
  for (int i : nums) {
    data[index(MIN, MAX, BUCKET, i)].push_back(i);
  }

  int j = 0;
  for (auto& it : data) {
    counting_sort(it);
    for (int i : it) {
      nums[j++] = i;
    }
  }
}

void bucket_sort(vector<int>& nums) const {
  if (nums.size() < LIMIT) {
    bubble_sort(nums);
    return;
  }

  int MIN, MAX;
  min_max(nums, MIN, MAX);

  bucket_sort(nums, MIN, MAX);
}

void counting_sort(vector<int>& nums, const int MIN, const int MAX) const {
  const int BUCKET = MAX - MIN + 1;

  vector<int> data(BUCKET, 0);
  for (int i : nums) {
    ++data[i - MIN];
  }

  int k = 0;
  for (int i = 0; i < BUCKET; ++i) {
    for (int j = 0; j < data[i]; ++j) {
      nums[k++] = i + MIN;
    }
  }
}

void counting_sort(vector<int>& nums) const {
  if (nums.size() < LIMIT) {
    bubble_sort(nums);
    return;
  }

  int MIN, MAX;
  min_max(nums, MIN, MAX);

  counting_sort(nums, MIN, MAX);
}

void count_buck_sort(vector<int>& nums) const {
  if (nums.size() < LIMIT) {
    bubble_sort(nums);
    return;
  }

  int MIN, MAX;
  min_max(nums, MIN, MAX);

  if (MAX > nums.size() * log2(nums.size()) + MIN) {
    bucket_sort(nums, MIN, MAX);
  } else {
    counting_sort(nums, MIN, MAX);
  }
}

void quick_sort(vector<int>& nums, vector<int>& data, const int begin) const {
  if (data.size() < LIMIT) {
    bubble_sort(data);
    if (&nums == &data) {
      return;
    }
    int j = begin;
    for (int i = 0; i < data.size();) {
      nums[j++] = data[i++];
    }
    return;
  }

  const int PIVOT = (data[0] + data[data.size() / 2] + data[data.size() - 1]) / 3;

  vector<int> smaller;
  vector<int> equal;
  vector<int> greater;

  for (int i = 0; i < data.size(); ++i) {
    if (data[i] < PIVOT) {
      smaller.push_back(data[i]);
    } else if (PIVOT < data[i]) {
      greater.push_back(data[i]);
    } else {
      equal.push_back(data[i]);
    }
  }

  int j = begin + smaller.size();
  for (int i = 0; i < equal.size();) {
    nums[j++] = equal[i++];
  }

  quick_sort(nums, smaller, begin);
  quick_sort(nums, greater, begin + smaller.size() + equal.size());
}

void quick_sort(vector<int>& nums) const {
  quick_sort(nums, nums, 0);
}

#endif