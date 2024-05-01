#include <initializer_list>
#include <set>

#include "testing.h"

TEST(set, initializer_list_constructor) {
  std::initializer_list<int> values = {1, 2, 3, 4, 5};
  s21::set<int> s21_set{values};
  std::set<int> std_set{values};
  auto m1 = s21_set.begin();
  auto m1_end = s21_set.end();
  auto m2 = std_set.begin();
  auto m2_end = std_set.end();
  for (; m1 != m1_end && m2 != m2_end; ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(set, copy_constructor) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  s21::set<int> s21_set_res(s21_set);

  std::set<int> std_set = {1, 2, 3, 4};
  std::set<int> std_set_res(std_set);

  EXPECT_EQ(s21_set_res.size(), std_set_res.size());

  auto m1 = s21_set_res.begin();
  auto m1_end = s21_set_res.end();
  auto m2 = std_set_res.begin();
  auto m2_end = std_set_res.end();
  for (; m1 != m1_end || m2 != m2_end; ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
}

TEST(set, move_constructor) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  s21::set<int> s21_set_res(std::move(s21_set));

  std::set<int> std_set = {1, 2, 3, 4};
  std::set<int> std_set_res(std::move(std_set));

  EXPECT_EQ(s21_set_res.size(), std_set_res.size());

  auto m1 = s21_set_res.begin();
  auto m1_end = s21_set_res.end();
  auto m2 = std_set_res.begin();
  auto m2_end = std_set_res.end();
  for (; m1 != m1_end && m2 != m2_end; ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
}

TEST(set, overload_for_moving_object) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  s21::set<int> s21_set_res{};
  s21_set_res = std::move(s21_set);

  std::set<int> std_set = {1, 2, 3, 4};
  std::set<int> std_set_res{};
  std_set_res = std::move(std_set);

  EXPECT_EQ(s21_set_res.size(), std_set_res.size());

  auto m1 = s21_set_res.begin();
  auto m1_end = s21_set_res.end();
  auto m2 = std_set_res.begin();
  auto m2_end = std_set_res.end();
  for (; m1 != m1_end || m2 != m2_end; ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
}

TEST(set, begin_end) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  std::set<int> std_set = {1, 2, 3, 4};

  auto m1 = s21_set.begin();
  auto m1_end = s21_set.end();
  auto m2 = std_set.begin();
  auto m2_end = std_set.end();
  for (; m1 != m1_end && m2 != m2_end; ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(set, empty) {
  s21::set<int> s21_set_1 = {1, 2, 3, 4};
  std::set<int> std_set_1 = {1, 2, 3, 4};

  s21::set<int> s21_set_2;
  std::set<int> std_set_2;

  EXPECT_EQ(s21_set_1.size(), s21_set_1.size());
  EXPECT_EQ(s21_set_2.size(), s21_set_2.size());

  EXPECT_EQ(s21_set_1.empty(), s21_set_1.empty());
  EXPECT_EQ(s21_set_2.empty(), s21_set_2.empty());
}

TEST(set, max_size) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  std::set<int> std_set = {1, 2, 3, 4};

  EXPECT_EQ(s21_set.max_size(), std_set.max_size());
}

TEST(set, clear) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  std::set<int> std_set = {1, 2, 3, 4};

  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());

  s21_set.clear();
  std_set.clear();

  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(set, insert) {
  s21::set<int> s21_set = {1, 2, 3, 4, 5};
  std::set<int> std_set = {1, 2, 3, 4, 5};

  auto res_1 = s21_set.insert(3);
  auto res_2 = std_set.insert(3);

  auto it_1 = res_1.first;
  auto it_2 = res_2.first;

  EXPECT_EQ(*it_1, *it_2);
  for (; it_1 != s21_set.end() && it_2 != std_set.end(); ++it_1, ++it_2) {
    EXPECT_EQ(*it_1, *it_1);
  }
}

TEST(set, insert_2) {
  s21::set<int> s21_set = {1, 2, 3, 4, 5};
  std::set<int> std_set = {1, 2, 3, 4, 5};

  s21_set.insert(10);
  s21_set.insert(5);
  s21_set.insert(2);

  std_set.insert(10);
  std_set.insert(5);
  std_set.insert(2);

  auto res_1 = s21_set.begin();
  auto res_2 = std_set.begin();
  for (; res_1 != s21_set.end() && res_2 != std_set.end(); ++res_1, ++res_2) {
    EXPECT_EQ(*res_1, *res_2);
  }
}

TEST(set, erase) {
  s21::set<int> s21_set = {1, 2, 3, 4, 5};
  std::set<int> std_set = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());

  s21_set.erase(s21_set.find(3));
  std_set.erase(std_set.find(3));

  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());

  auto s21_begin = s21_set.begin();
  auto std_begin = std_set.begin();

  for (; s21_begin != s21_set.end(); ++s21_begin, ++std_begin) {
    EXPECT_EQ(*s21_begin, *std_begin);
  }
}

TEST(set, erase_2) {
  s21::set<int> s21_set = {1};
  std::set<int> std_set = {1};

  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());

  s21_set.erase(s21_set.find(1));
  std_set.erase(std_set.find(1));

  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());

  auto s21_begin = s21_set.begin();
  auto std_begin = std_set.begin();

  for (; s21_begin != s21_set.end(); ++s21_begin, ++std_begin) {
    EXPECT_EQ(*s21_begin, *std_begin);
  }
}

TEST(set, swap) {
  s21::set<int> s21_set_1 = {1, 2, 3, 4, 5};
  s21::set<int> s21_set_2 = {6, 7, 8, 9, 10, 11};
  std::set<int> std_set_1 = {1, 2, 3, 4, 5};
  std::set<int> std_set_2 = {6, 7, 8, 9, 10, 11};

  s21_set_1.swap(s21_set_2);
  std_set_1.swap(std_set_2);

  EXPECT_EQ(s21_set_1.size(), std_set_1.size());
  EXPECT_EQ(s21_set_2.size(), std_set_2.size());

  auto s21_begin_1 = s21_set_1.begin();
  auto std_begin_1 = std_set_1.begin();

  for (; s21_begin_1 != s21_set_1.end(); ++s21_begin_1, ++std_begin_1) {
    EXPECT_EQ(*s21_begin_1, *std_begin_1);
  }

  auto s21_begin_2 = s21_set_2.begin();
  auto std_begin_2 = std_set_2.begin();

  for (; s21_begin_2 != s21_set_2.end(); ++s21_begin_2, ++std_begin_2) {
    EXPECT_EQ(*s21_begin_2, *std_begin_2);
  }
}

TEST(set, merge) {
  s21::set<int> s21_set_1 = {1, 2, 3, 4, 5};
  s21::set<int> s21_set_2 = {6, 7, 8, 9, 10, 11};

  s21_set_1.merge(s21_set_2);

  EXPECT_EQ(s21_set_1.size(), 11);
  EXPECT_EQ(s21_set_1.empty(), false);

  EXPECT_EQ(s21_set_2.size(), 0);
  EXPECT_EQ(s21_set_2.empty(), true);

  auto s21_begin_1 = s21_set_1.begin();
  int i = 1;
  for (; s21_begin_1 != s21_set_1.end(); ++s21_begin_1) {
    EXPECT_EQ(*s21_begin_1, i++);
  }
}

TEST(set, find) {
  s21::set<int> s21_set = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};
  std::set<int> std_set = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};

  auto s21_it = s21_set.find(1);
  auto std_it = std_set.find(1);

  for (; s21_it != s21_set.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(set, find_2) {
  s21::set<int> s21_set = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};
  std::set<int> std_set = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};

  auto s21_it = s21_set.find(3);
  auto std_it = std_set.find(3);

  for (; s21_it != s21_set.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(set, contains) {
  s21::set<int> s21_set = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};
  std::set<int> std_set = {1, 2, 3, 1, 6, 10, 6, 3, 3, 1};

  EXPECT_EQ(s21_set.contains(1), true);
  EXPECT_EQ(s21_set.contains(5), false);
  EXPECT_EQ(s21_set.contains(2), true);
  EXPECT_EQ(s21_set.contains(4), false);
}

TEST(set, insert_many) {
  s21::set<int> s21_set = {0, 1, 2, 3, 4, 5};

  auto res = s21_set.insert_many(5, 6, 7, 8, 9);

  EXPECT_EQ(s21_set.contains(5), true);
  EXPECT_EQ(s21_set.contains(6), true);
  EXPECT_EQ(s21_set.contains(7), true);
  EXPECT_EQ(s21_set.contains(8), true);
  EXPECT_EQ(s21_set.contains(9), true);

  EXPECT_EQ(*(res[0].first), 5);
  EXPECT_EQ(res[0].second, false);
  EXPECT_EQ(*(res[1].first), 6);
  EXPECT_EQ(res[1].second, true);
  EXPECT_EQ(*(res[2].first), 7);
  EXPECT_EQ(res[2].second, true);
  EXPECT_EQ(*(res[3].first), 8);
  EXPECT_EQ(res[3].second, true);
  EXPECT_EQ(*(res[4].first), 9);
  EXPECT_EQ(res[4].second, true);
}
