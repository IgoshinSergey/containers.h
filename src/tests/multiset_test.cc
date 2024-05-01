#include <initializer_list>
#include <set>

#include "testing.h"

TEST(multiset, initializer_list_constructor) {
  std::initializer_list<int> values = {1, 2, 3, 4, 5};
  s21::multiset<int> s21_multiset{values};
  std::multiset<int> std_multiset{values};
  auto m1 = s21_multiset.begin();
  auto m1_end = s21_multiset.end();
  auto m2 = std_multiset.begin();
  auto m2_end = std_multiset.end();
  for (; m1 != m1_end && m2 != m2_end; ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
}

TEST(multiset, copy_constructor) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 4};
  s21::multiset<int> s21_multiset_res(s21_multiset);

  std::multiset<int> std_multiset = {1, 2, 3, 4};
  std::multiset<int> std_multiset_res(std_multiset);

  EXPECT_EQ(s21_multiset_res.size(), std_multiset_res.size());

  auto m1 = s21_multiset_res.begin();
  auto m1_end = s21_multiset_res.end();
  auto m2 = std_multiset_res.begin();
  auto m2_end = std_multiset_res.end();
  for (; m1 != m1_end && m2 != m2_end; ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
}

TEST(multiset, move_constructor) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 4};
  s21::multiset<int> s21_multiset_res(std::move(s21_multiset));

  std::multiset<int> std_multiset = {1, 2, 3, 4};
  std::multiset<int> std_multiset_res(std::move(std_multiset));

  EXPECT_EQ(s21_multiset_res.size(), std_multiset_res.size());

  auto m1 = s21_multiset_res.begin();
  auto m1_end = s21_multiset_res.end();
  auto m2 = std_multiset_res.begin();
  auto m2_end = std_multiset_res.end();
  for (; m1 != m1_end && m2 != m2_end; ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
}

TEST(multiset, overload_for_moving_object) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 4};
  s21::multiset<int> s21_multiset_res{};
  s21_multiset_res = std::move(s21_multiset);

  std::multiset<int> std_multiset = {1, 2, 3, 4};
  std::multiset<int> std_multiset_res{};
  std_multiset_res = std::move(std_multiset);

  EXPECT_EQ(s21_multiset_res.size(), std_multiset_res.size());

  auto m1 = s21_multiset_res.begin();
  auto m1_end = s21_multiset_res.end();
  auto m2 = std_multiset_res.begin();
  auto m2_end = std_multiset_res.end();
  for (; m1 != m1_end || m2 != m2_end; ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
}

TEST(multiset, begin_end) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 4};
  std::multiset<int> std_multiset = {1, 2, 3, 4};

  auto m1 = s21_multiset.begin();
  auto m1_end = s21_multiset.end();
  auto m2 = std_multiset.begin();
  auto m2_end = std_multiset.end();
  for (; m1 != m1_end && m2 != m2_end; ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
}

TEST(multiset, empty) {
  s21::multiset<int> s21_multiset_1 = {1, 2, 3, 4};
  std::multiset<int> std_multiset_1 = {1, 2, 3, 4};

  s21::multiset<int> s21_multiset_2;
  std::multiset<int> std_multiset_2;

  EXPECT_EQ(s21_multiset_1.size(), s21_multiset_1.size());
  EXPECT_EQ(s21_multiset_2.size(), s21_multiset_2.size());

  EXPECT_EQ(s21_multiset_1.empty(), s21_multiset_1.empty());
  EXPECT_EQ(s21_multiset_2.empty(), s21_multiset_2.empty());
}

TEST(multiset, max_size) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 4};
  std::multiset<int> std_multiset = {1, 2, 3, 4};

  EXPECT_EQ(s21_multiset.max_size(), std_multiset.max_size());
}

TEST(multiset, clear) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 4};
  std::multiset<int> std_multiset = {1, 2, 3, 4};

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  s21_multiset.clear();
  std_multiset.clear();

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
}

TEST(multiset, insert) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 4, 5};
  std::multiset<int> std_multiset = {1, 2, 3, 4, 5};

  auto res_1 = s21_multiset.insert(3);
  auto res_2 = std_multiset.insert(3);

  EXPECT_EQ(*res_1, *res_2);
  for (; res_1 != s21_multiset.end() && res_2 != std_multiset.end();
       ++res_1, ++res_2) {
    EXPECT_EQ(*res_1, *res_2);
  }
}

TEST(multiset, insert_2) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 4, 5};
  std::multiset<int> std_multiset = {1, 2, 3, 4, 5};

  s21_multiset.insert(10);
  s21_multiset.insert(5);
  s21_multiset.insert(2);

  std_multiset.insert(10);
  std_multiset.insert(5);
  std_multiset.insert(2);

  auto res_1 = s21_multiset.begin();
  auto res_2 = std_multiset.begin();
  for (; res_1 != s21_multiset.end() && res_2 != std_multiset.end();
       ++res_1, ++res_2) {
    EXPECT_EQ(*res_1, *res_2);
  }
}

TEST(multiset, erase) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 4, 5};
  std::multiset<int> std_multiset = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  s21_multiset.erase(s21_multiset.find(4));
  std_multiset.erase(std_multiset.find(4));

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  auto s21_begin = s21_multiset.begin();
  auto std_begin = std_multiset.begin();

  for (; s21_begin != s21_multiset.end(); ++s21_begin, ++std_begin) {
    EXPECT_EQ(*s21_begin, *std_begin);
  }
}

TEST(multiset, erase_2) {
  s21::multiset<int> s21_multiset = {1};
  std::multiset<int> std_multiset = {1};

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  s21_multiset.erase(s21_multiset.find(1));
  std_multiset.erase(std_multiset.find(1));

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  auto s21_begin = s21_multiset.begin();
  auto std_begin = std_multiset.begin();

  for (; s21_begin != s21_multiset.end(); ++s21_begin, ++std_begin) {
    EXPECT_EQ(*s21_begin, *std_begin);
  }
}

TEST(multiset, erase_3) {
  s21::multiset<int> s21_multiset = {1, 5, 7, 15, 10, 14, 12, 13, 9};
  std::multiset<int> std_multiset = {1, 5, 7, 15, 10, 14, 12, 13, 9};

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  s21_multiset.erase(s21_multiset.find(1));
  std_multiset.erase(std_multiset.find(1));
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  s21_multiset.erase(s21_multiset.find(12));
  std_multiset.erase(std_multiset.find(12));
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  s21_multiset.erase(s21_multiset.find(9));
  std_multiset.erase(std_multiset.find(9));
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  s21_multiset.erase(s21_multiset.find(13));
  std_multiset.erase(std_multiset.find(13));
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  s21_multiset.erase(s21_multiset.find(5));
  std_multiset.erase(std_multiset.find(5));
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  auto s21_begin = s21_multiset.begin();
  auto std_begin = std_multiset.begin();

  for (; s21_begin != s21_multiset.end(); ++s21_begin, ++std_begin) {
    EXPECT_EQ(*s21_begin, *std_begin);
  }
}

TEST(multiset, swap) {
  s21::multiset<int> s21_multiset_1 = {1, 2, 3, 4, 5};
  s21::multiset<int> s21_multiset_2 = {6, 7, 8, 9, 10, 11};
  std::multiset<int> std_multiset_1 = {1, 2, 3, 4, 5};
  std::multiset<int> std_multiset_2 = {6, 7, 8, 9, 10, 11};

  s21_multiset_1.swap(s21_multiset_2);
  std_multiset_1.swap(std_multiset_2);

  EXPECT_EQ(s21_multiset_1.size(), std_multiset_1.size());
  EXPECT_EQ(s21_multiset_2.size(), std_multiset_2.size());

  auto s21_begin_1 = s21_multiset_1.begin();
  auto std_begin_1 = std_multiset_1.begin();

  for (; s21_begin_1 != s21_multiset_1.end(); ++s21_begin_1, ++std_begin_1) {
    EXPECT_EQ(*s21_begin_1, *std_begin_1);
  }

  auto s21_begin_2 = s21_multiset_2.begin();
  auto std_begin_2 = std_multiset_2.begin();

  for (; s21_begin_2 != s21_multiset_2.end(); ++s21_begin_2, ++std_begin_2) {
    EXPECT_EQ(*s21_begin_2, *std_begin_2);
  }
}

TEST(multiset, merge) {
  s21::multiset<int> s21_multiset_1 = {1, 2, 3, 4, 5};
  s21::multiset<int> s21_multiset_2 = {6, 7, 8, 9, 10, 11};

  s21_multiset_1.merge(s21_multiset_2);

  EXPECT_EQ(s21_multiset_1.size(), 11);
  EXPECT_EQ(s21_multiset_1.empty(), false);

  EXPECT_EQ(s21_multiset_2.size(), 0);
  EXPECT_EQ(s21_multiset_2.empty(), true);

  auto s21_begin_1 = s21_multiset_1.begin();
  int i = 1;
  for (; s21_begin_1 != s21_multiset_1.end(); ++s21_begin_1) {
    EXPECT_EQ(*s21_begin_1, i++);
  }
}

TEST(multiset, count) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};
  std::multiset<int> std_multiset = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};

  auto s21_count = s21_multiset.count(1);
  auto std_count = std_multiset.count(1);
  EXPECT_EQ(s21_count, std_count);

  s21_count = s21_multiset.count(3);
  std_count = std_multiset.count(3);
  EXPECT_EQ(s21_count, std_count);

  s21_count = s21_multiset.count(1);
  std_count = std_multiset.count(1);
  EXPECT_EQ(s21_count, std_count);
}

TEST(multiset, find) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};
  std::multiset<int> std_multiset = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};

  auto s21_it = s21_multiset.find(1);
  auto std_it = std_multiset.find(1);

  for (; s21_it != s21_multiset.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(multiset, find_2) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};
  std::multiset<int> std_multiset = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};

  auto s21_it = s21_multiset.find(3);
  auto std_it = std_multiset.find(3);

  for (; s21_it != s21_multiset.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(multiset, contains) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};
  std::multiset<int> std_multiset = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};

  EXPECT_EQ(s21_multiset.contains(1), true);
  EXPECT_EQ(s21_multiset.contains(5), false);
  EXPECT_EQ(s21_multiset.contains(2), true);
  EXPECT_EQ(s21_multiset.contains(4), false);
}

TEST(multiset, eqaul_range) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};
  std::multiset<int> std_multiset = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};

  auto res1 = s21_multiset.equal_range(1);
  auto res2 = std_multiset.equal_range(1);

  auto s21_it = res1.first;
  auto std_it = res2.first;
  for (; s21_it != res1.second; ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(multiset, eqaul_range_2) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 1, 6, 10, 1, 3, 2, 6, 3, 3, 1};
  std::multiset<int> std_multiset = {1, 2, 3, 1, 6, 10, 1, 3, 2, 6, 3, 3, 1};

  auto res1 = s21_multiset.equal_range(3);
  auto res2 = std_multiset.equal_range(3);

  auto s21_it = res1.first;
  auto std_it = res2.first;
  for (; s21_it != res1.second; ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(multiset, lower_bound) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 1, 6, 10, 1, 3, 2, 6, 3, 3, 1};
  std::multiset<int> std_multiset = {1, 2, 3, 1, 6, 10, 1, 3, 2, 6, 3, 3, 1};

  auto s21_it = s21_multiset.lower_bound(1);
  auto std_it = std_multiset.lower_bound(1);

  for (; s21_it != s21_multiset.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(multiset, lower_bound_2) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 1, 6, 10, 1, 3, 2, 6, 3, 3, 1};
  std::multiset<int> std_multiset = {1, 2, 3, 1, 6, 10, 1, 3, 2, 6, 3, 3, 1};

  auto s21_it = s21_multiset.lower_bound(3);
  auto std_it = std_multiset.lower_bound(3);

  for (; s21_it != s21_multiset.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(multiset, upper_bound) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 1, 6, 10, 1, 3, 2, 6, 3, 3, 1};
  std::multiset<int> std_multiset = {1, 2, 3, 1, 6, 10, 1, 3, 2, 6, 3, 3, 1};

  auto s21_it = s21_multiset.upper_bound(1);
  auto std_it = std_multiset.upper_bound(1);

  for (; s21_it != s21_multiset.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(multiset, upper_bound_2) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 1, 6, 10, 1, 3, 2, 6, 3, 3, 1};
  std::multiset<int> std_multiset = {1, 2, 3, 1, 6, 10, 1, 3, 2, 6, 3, 3, 1};

  auto s21_it = s21_multiset.upper_bound(3);
  auto std_it = std_multiset.upper_bound(3);

  for (; s21_it != s21_multiset.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(multiset, insert_many) {
  s21::multiset<int> s21_multiset = {0, 1, 2, 3, 4, 5};

  auto res = s21_multiset.insert_many(5, 6, 7, 8, 9);

  EXPECT_EQ(s21_multiset.contains(5), true);
  EXPECT_EQ(s21_multiset.contains(6), true);
  EXPECT_EQ(s21_multiset.contains(7), true);
  EXPECT_EQ(s21_multiset.contains(8), true);
  EXPECT_EQ(s21_multiset.contains(9), true);

  EXPECT_EQ(*(res[0].first), 5);
  EXPECT_EQ(res[0].second, true);
  EXPECT_EQ(*(res[1].first), 6);
  EXPECT_EQ(res[1].second, true);
  EXPECT_EQ(*(res[2].first), 7);
  EXPECT_EQ(res[2].second, true);
  EXPECT_EQ(*(res[3].first), 8);
  EXPECT_EQ(res[3].second, true);
  EXPECT_EQ(*(res[4].first), 9);
  EXPECT_EQ(res[4].second, true);
}