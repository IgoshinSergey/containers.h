#include <initializer_list>
#include <map>

#include "testing.h"

TEST(map, default_constructor) {
  s21::map<int, int> s21_map{};
  std::map<int, int> std_map{};
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(map, initializer_list_constructor) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  std::map<int, int> std_map{values};
  auto m1 = s21_map.begin();
  auto m2 = std_map.begin();
  for (; m2 != std_map.end(); ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(map, copy_constructor) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  s21::map<int, int> s21_map_2{s21_map};

  std::map<int, int> std_map{values};
  std::map<int, int> std_map_2{std_map};

  auto m1 = s21_map_2.begin();
  auto m2 = std_map_2.begin();
  for (; m2 != std_map_2.end(); ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
  EXPECT_EQ(s21_map_2.size(), std_map_2.size());
  EXPECT_EQ(s21_map_2.empty(), std_map_2.empty());
}

TEST(map, move_constructor) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  s21::map<int, int> s21_map_2 = std::move(s21_map);

  std::map<int, int> std_map{values};
  std::map<int, int> std_map_2 = std::move(std_map);

  auto m1 = s21_map_2.begin();
  auto m2 = std_map_2.begin();
  for (; m2 != std_map_2.end(); ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
  EXPECT_EQ(s21_map_2.size(), std_map_2.size());
  EXPECT_EQ(s21_map_2.empty(), std_map_2.empty());
}

TEST(map, overload_for_moving_object) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  s21::map<int, int> s21_map_2{};
  s21_map_2 = std::move(s21_map);

  std::map<int, int> std_map{values};
  std::map<int, int> std_map_2{};
  std_map_2 = std::move(std_map);

  auto m1 = s21_map_2.begin();
  auto m2 = std_map_2.begin();
  for (; m2 != std_map_2.end(); ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
  EXPECT_EQ(s21_map_2.size(), std_map_2.size());
  EXPECT_EQ(s21_map_2.empty(), std_map_2.empty());
}

TEST(map, at) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  std::map<int, int> std_map{values};

  EXPECT_EQ(s21_map.at(1), std_map.at(1));
  EXPECT_EQ(s21_map.at(2), std_map.at(2));
  EXPECT_EQ(s21_map.at(3), std_map.at(3));
  EXPECT_EQ(s21_map.at(4), std_map.at(4));
  EXPECT_EQ(s21_map.at(5), std_map.at(5));

  EXPECT_THROW(s21_map.at(-1), std::out_of_range);
  EXPECT_THROW(s21_map.at(6), std::out_of_range);
}

TEST(map, access_or_insert_an_element) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  std::map<int, int> std_map{values};

  s21_map[10];
  std_map[10];

  EXPECT_EQ(s21_map.at(1), std_map.at(1));
  EXPECT_EQ(s21_map.at(2), std_map.at(2));
  EXPECT_EQ(s21_map.at(3), std_map.at(3));
  EXPECT_EQ(s21_map.at(4), std_map.at(4));
  EXPECT_EQ(s21_map.at(5), std_map.at(5));
  EXPECT_EQ(s21_map.at(10), std_map.at(10));

  s21_map[10] = 100;
  std_map[10] = 100;

  EXPECT_EQ(s21_map.at(10), std_map.at(10));
}

TEST(map, begin_end) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  std::map<int, int> std_map{values};

  auto m1 = s21_map.begin();
  auto m2 = std_map.begin();
  for (; m2 != std_map.end(); ++m1, ++m2) {
    EXPECT_EQ(*m1, *m2);
  }
}

TEST(map, empty_size) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map_1{values};
  std::map<int, int> std_map_1{values};

  s21::map<int, int> s21_map_2;
  std::map<int, int> std_map_2;

  EXPECT_EQ(s21_map_1.size(), std_map_1.size());
  EXPECT_EQ(s21_map_2.size(), std_map_2.size());

  EXPECT_EQ(s21_map_1.empty(), std_map_1.empty());
  EXPECT_EQ(s21_map_2.empty(), std_map_2.empty());

  s21_map_1[10] = 100;
  std_map_1[10] = 100;

  s21_map_2[10] = 100;
  std_map_2[10] = 100;
  EXPECT_EQ(s21_map_1.size(), std_map_1.size());
  EXPECT_EQ(s21_map_2.size(), std_map_2.size());
}

TEST(map, max_size) {
  s21::map<int, int> s21_map{};
  std::map<int, int> std_map{};

  EXPECT_EQ(s21_map.max_size(), std_map.max_size());
}

TEST(map, clear) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  std::map<int, int> std_map{values};
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());

  s21_map.clear();
  std_map.clear();
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(map, insert_1) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  std::map<int, int> std_map{values};

  std::pair<int, int> p = {10, 100};
  auto res_1 = s21_map.insert(p);
  auto res_2 = std_map.insert(p);

  EXPECT_EQ(res_1.second, res_2.second);

  auto iter_1 = res_1.first;
  auto iter_2 = res_2.first;

  for (; iter_2 != std_map.end(); ++iter_1, ++iter_2) {
    EXPECT_EQ((*iter_1).first, (*iter_2).first);
    EXPECT_EQ((*iter_2).second, (*iter_2).second);
  }
}

TEST(map, insert_2) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  std::map<int, int> std_map{values};

  std::pair<int, int> p = {1, 100};
  auto res_1 = s21_map.insert(p);
  auto res_2 = std_map.insert(p);

  EXPECT_EQ(res_1.second, res_2.second);

  auto iter_1 = res_1.first;
  auto iter_2 = res_2.first;

  for (; iter_2 != std_map.end(); ++iter_1, ++iter_2) {
    EXPECT_EQ((*iter_1).first, (*iter_2).first);
    EXPECT_EQ((*iter_2).second, (*iter_2).second);
  }
}

TEST(map, insert_3) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  std::map<int, int> std_map{values};

  const int key_value = 10;
  int mapped_value = 100;

  auto res_1 = s21_map.insert(key_value, mapped_value);
  auto res_2 = std_map.insert({key_value, mapped_value});

  EXPECT_EQ(res_1.second, res_2.second);
  EXPECT_EQ((*res_1.first).first, (*res_2.first).first);
  EXPECT_EQ((*res_1.first).second, (*res_2.first).second);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(map, insert_4) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  std::map<int, int> std_map{values};

  const int key_value = 1;
  int mapped_value = 100;

  auto res_1 = s21_map.insert(key_value, mapped_value);
  auto res_2 = std_map.insert({key_value, mapped_value});

  EXPECT_EQ(res_1.second, res_2.second);
  EXPECT_EQ((*res_1.first).first, (*res_2.first).first);
  EXPECT_EQ((*res_1.first).second, (*res_2.first).second);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(map, insert_5) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  std::map<int, int> std_map{values};

  auto res = s21_map.insert_or_assign(1, 100);

  EXPECT_EQ(res.second, false);
  EXPECT_EQ((*res.first).first, 1);
  EXPECT_EQ((*res.first).second, 100);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(map, insert_6) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  std::map<int, int> std_map{values};

  auto res = s21_map.insert_or_assign(10, 100);

  EXPECT_EQ(res.second, true);
  EXPECT_EQ((*res.first).first, 10);
  EXPECT_EQ((*res.first).second, 100);

  EXPECT_EQ(s21_map.size(), 6);
  EXPECT_EQ(s21_map.empty(), false);
}

TEST(map, erase_1) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  std::map<int, int> std_map{values};

  s21_map.erase(s21_map.begin());
  std_map.erase(std_map.begin());

  auto iter_1 = s21_map.begin();
  auto iter_2 = std_map.begin();

  for (; iter_2 != std_map.end(); ++iter_1, ++iter_2) {
    EXPECT_EQ(*iter_1, *iter_2);
  }
}

TEST(map, erase_2) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  std::map<int, int> std_map{values};

  while (!s21_map.empty()) {
    s21_map.erase(s21_map.begin());
    std_map.erase(std_map.begin());

    auto iter_1 = s21_map.begin();
    auto iter_2 = std_map.begin();

    for (; iter_2 != std_map.end(); ++iter_1, ++iter_2) {
      EXPECT_EQ(*iter_1, *iter_2);
    }
  }
}

TEST(map, swap) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  std::initializer_list<std::pair<const int, int>> values_2 = {
      {6, 60}, {7, 70}, {8, 80}, {9, 90}, {10, 100}};
  s21::map<int, int> s21_map{values};
  std::map<int, int> std_map{values};

  s21::map<int, int> s21_map_2{values_2};
  std::map<int, int> std_map_2{values_2};

  s21_map.swap(s21_map_2);
  std_map.swap(std_map_2);

  auto iter_1 = s21_map_2.begin();
  auto iter_2 = std_map_2.begin();

  for (; iter_2 != std_map_2.end(); ++iter_1, ++iter_2) {
    EXPECT_EQ(*iter_1, *iter_2);
  }
}

TEST(map, merge) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  std::initializer_list<std::pair<const int, int>> values_2 = {
      {6, 60}, {7, 70}, {8, 80}, {9, 90}, {10, 100}};
  s21::map<int, int> s21_map{values};
  s21::map<int, int> s21_map_2{values_2};

  s21_map.merge(s21_map_2);

  auto iter_1 = s21_map_2.begin();
  int i = 1;
  for (; iter_1 != s21_map.end(); ++iter_1, ++i) {
    EXPECT_EQ((*iter_1).first, i);
    EXPECT_EQ((*iter_1).second, i * 10);
  }
  EXPECT_EQ(s21_map.size(), 10);
}

TEST(map, contains) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  s21::map<int, int> std_map{values};

  auto iter_1 = s21_map.begin();
  int i = 1;
  for (; iter_1 != s21_map.end(); ++iter_1, ++i) {
    EXPECT_EQ(s21_map.contains(i), std_map.contains(2));
  }
}

using p = std::pair<const int, int>;
TEST(map, insert_many) {
  std::initializer_list<std::pair<const int, int>> values = {
      {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
  s21::map<int, int> s21_map{values};
  s21_map.insert_many(p(6, 60), p(7, 70), p(8, 80), p(9, 90), p(10, 100));
  auto iter_1 = s21_map.begin();
  int i = 1;
  for (; iter_1 != s21_map.end(); ++iter_1, ++i) {
    EXPECT_EQ(s21_map[i], i * 10);
  }
}