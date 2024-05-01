#include <initializer_list>
#include <vector>

#include "testing.h"

TEST(vector, default_constructor) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.data(), std_vector.data());
}

TEST(vector, parameterized_constructor) {
  s21::vector<int> s21_vector(10);
  std::vector<int> std_vector(10);
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  for (int i{}; i < 10; i++) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(vector, initializer_list_constructor) {
  std::initializer_list<int> values = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector(values);
  std::vector<int> std_vector(values);
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  for (int i{}; i < 5; i++) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(vector, copy_constructor) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  s21::vector<int> s21_vector_res(s21_vector);

  std::vector<int> std_vector = {1, 2, 3, 4};
  std::vector<int> std_vector_res(std_vector);

  EXPECT_EQ(s21_vector_res.capacity(), std_vector_res.capacity());
  EXPECT_EQ(s21_vector_res.size(), std_vector_res.size());
  for (int i{}; i < 4; i++) {
    EXPECT_EQ(s21_vector_res[i], std_vector_res[i]);
  }
}

TEST(vector, move_constructor) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  s21::vector<int> s21_vector_res(std::move(s21_vector));

  std::vector<int> std_vector = {1, 2, 3, 4};
  std::vector<int> std_vector_res(std::move(std_vector));

  EXPECT_EQ(s21_vector_res.capacity(), std_vector_res.capacity());
  EXPECT_EQ(s21_vector_res.size(), std_vector_res.size());

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.data(), std_vector.data());

  for (int i{}; i < 4; i++) {
    EXPECT_EQ(s21_vector_res[i], std_vector_res[i]);
  }
}

TEST(vector, overload_for_moving_object) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  s21::vector<int> s21_vector_res;
  s21_vector_res = std::move(s21_vector);

  std::vector<int> std_vector = {1, 2, 3, 4};
  std::vector<int> std_vector_res;
  std_vector_res = std::move(std_vector);

  EXPECT_EQ(s21_vector_res.capacity(), std_vector_res.capacity());
  EXPECT_EQ(s21_vector_res.size(), std_vector_res.size());

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.size(), std_vector.size());

  for (unsigned i{}; i < s21_vector.size(); i++) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }

  for (unsigned i{}; i < s21_vector_res.size(); i++) {
    EXPECT_EQ(s21_vector_res[i], std_vector_res[i]);
  }
}

TEST(vector, at) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};

  for (int i{}; i < 4; i++) {
    EXPECT_EQ(s21_vector.at(i), std_vector.at(i));
  }
  EXPECT_THROW(s21_vector.at(-1), std::out_of_range);
  EXPECT_THROW(std_vector.at(-1), std::out_of_range);
  EXPECT_THROW(s21_vector.at(100), std::out_of_range);
  EXPECT_THROW(std_vector.at(100), std::out_of_range);
}

TEST(vector, front) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};

  auto s21_front = s21_vector.front();
  auto std_front = std_vector.front();

  EXPECT_EQ(s21_front, std_front);
}

TEST(vector, back) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};

  auto s21_back = s21_vector.back();
  auto std_back = std_vector.back();

  EXPECT_EQ(s21_back, std_back);
}

TEST(vector, data) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};

  auto s21_data = s21_vector.data();
  auto std_data = std_vector.data();

  for (int i{}; i < 4; i++) {
    EXPECT_EQ(*(s21_data + i), *(std_data + i));
  }
}

TEST(vector, begin_end_1) {
  s21::vector<int> s21_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};

  auto s21_begin = s21_vector.begin();
  auto s21_end = s21_vector.end();

  auto std_begin = std_vector.begin();
  auto std_end = std_vector.end();

  EXPECT_EQ(*s21_begin, *std_begin);
  EXPECT_EQ(*(s21_end - 1), *(std_end - 1));

  for (; s21_begin != s21_end; s21_begin++, std_begin++) {
    EXPECT_EQ(*s21_begin, *std_begin);
  }
}

TEST(vector, begin_end_2) {
  s21::vector<int> s21_vector = {0};
  std::vector<int> std_vector = {0};

  auto s21_begin = s21_vector.begin();
  auto s21_end = s21_vector.end();

  auto std_begin = std_vector.begin();
  auto std_end = std_vector.end();

  EXPECT_EQ(*s21_begin, *std_begin);
  EXPECT_EQ(*(s21_end - 1), *(std_end - 1));

  for (; s21_begin != s21_end; s21_begin++, std_begin++) {
    EXPECT_EQ(*s21_begin, *std_begin);
  }
}

TEST(vector, empty_1) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;

  auto s21_empty = s21_vector.empty();
  auto std_empty = std_vector.empty();

  EXPECT_EQ(s21_empty, std_empty);
}

TEST(vector, empty_2) {
  s21::vector<int> s21_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};

  auto s21_empty = s21_vector.empty();
  auto std_empty = std_vector.empty();

  EXPECT_EQ(s21_empty, std_empty);
}

TEST(vector, size_1) {
  s21::vector<int> s21_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};

  auto s21_size = s21_vector.size();
  auto std_size = std_vector.size();

  EXPECT_EQ(s21_size, std_size);
}

TEST(vector, size_2) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;

  auto s21_size = s21_vector.size();
  auto std_size = std_vector.size();

  EXPECT_EQ(s21_size, std_size);
}

TEST(vector, max_size_1) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;

  auto s21_size = s21_vector.max_size();
  auto std_size = std_vector.max_size();

  EXPECT_EQ(s21_size, std_size);
}

TEST(vector, max_size_2) {
  s21::vector<char> s21_vector;
  std::vector<char> std_vector;

  auto s21_size = s21_vector.max_size();
  auto std_size = std_vector.max_size();

  EXPECT_EQ(s21_size, std_size);
}

TEST(vector, max_size_3) {
  s21::vector<double> s21_vector;
  std::vector<double> std_vector;

  auto s21_size = s21_vector.max_size();
  auto std_size = std_vector.max_size();

  EXPECT_EQ(s21_size, std_size);
}

TEST(vector, max_size_4) {
  s21::vector<long long> s21_vector;
  std::vector<long long> std_vector;

  auto s21_size = s21_vector.max_size();
  auto std_size = std_vector.max_size();

  EXPECT_EQ(s21_size, std_size);
}

TEST(vector, reserve) {
  s21::vector<int> s21_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};

  s21_vector.reserve(3);
  std_vector.reserve(3);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

  s21_vector.reserve(10);
  std_vector.reserve(10);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

  for (unsigned i{}; i < s21_vector.size(); i++) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }

  s21_vector.reserve(7);
  std_vector.reserve(7);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

  for (unsigned i{}; i < s21_vector.size(); i++) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(vector, shrink_to_fit_1) {
  s21::vector<int> s21_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};

  s21_vector.reserve(10);
  std_vector.reserve(10);
  s21_vector.shrink_to_fit();
  std_vector.shrink_to_fit();

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

  for (unsigned i{}; i < s21_vector.size(); i++) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(vector, shrink_to_fit_2) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;

  s21_vector.reserve(10);
  std_vector.reserve(10);
  s21_vector.shrink_to_fit();
  std_vector.shrink_to_fit();

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
}

TEST(vector, clear) {
  s21::vector<int> s21_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};

  s21_vector.clear();
  std_vector.clear();

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
}

TEST(vector, insert_1) {
  s21::vector<int> s21_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};

  auto s21_res = s21_vector.insert(s21_vector.begin() + 3, 100);
  auto std_res = std_vector.insert(std_vector.begin() + 3, 100);

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

  for (; s21_res < s21_vector.end(); s21_res++, std_res++) {
    EXPECT_EQ(*s21_res, *std_res);
  }
}

TEST(vector, insert_2) {
  s21::vector<int> s21_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};

  s21_vector.reserve(10);
  std_vector.reserve(10);

  s21_vector.insert(s21_vector.begin() + 3, 100);
  std_vector.insert(std_vector.begin() + 3, 100);

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

  for (unsigned i{}; i < s21_vector.size(); i++) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(vector, insert_3) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;

  s21_vector.insert(s21_vector.begin(), 100);
  std_vector.insert(std_vector.begin(), 100);

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

  for (unsigned i{}; i < s21_vector.size(); i++) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }

  s21_vector.insert(s21_vector.begin(), 150);
  std_vector.insert(std_vector.begin(), 150);

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

  for (unsigned i{}; i < s21_vector.size(); i++) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(vector, erase) {
  s21::vector<int> s21_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};

  s21_vector.erase(s21_vector.begin());
  std_vector.erase(std_vector.begin());

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

  for (unsigned i{}; i < s21_vector.size(); i++) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(vector, push_back_1) {
  s21::vector<int> s21_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};

  s21_vector.push_back(100);
  std_vector.push_back(100);

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

  for (unsigned i{}; i < s21_vector.size(); i++) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(vector, push_back_2) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;

  s21_vector.push_back(100);
  std_vector.push_back(100);

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

  for (unsigned i{}; i < s21_vector.size(); i++) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }

  s21_vector.push_back(150);
  std_vector.push_back(150);

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

  for (unsigned i{}; i < s21_vector.size(); i++) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(vector, pop_back) {
  s21::vector<int> s21_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};

  for (unsigned i{}; i < s21_vector.size(); i++) {
    s21_vector.pop_back();
    std_vector.pop_back();

    EXPECT_EQ(s21_vector.size(), std_vector.size());
    EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

    for (unsigned i{}; i < s21_vector.size(); i++) {
      EXPECT_EQ(s21_vector[i], std_vector[i]);
    }
  }
}

TEST(vector, swap) {
  s21::vector<int> s21_vector = {1, 2, 3, 4, 5};
  s21::vector<int> s21_vector_swap = {10};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector_swap = {10};

  s21_vector.swap(s21_vector_swap);
  std_vector.swap(std_vector_swap);

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());

  for (unsigned i{}; i < s21_vector.size(); i++) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }

  EXPECT_EQ(s21_vector_swap.size(), s21_vector_swap.size());
  EXPECT_EQ(s21_vector_swap.capacity(), s21_vector_swap.capacity());

  for (unsigned i{}; i < s21_vector_swap.size(); i++) {
    EXPECT_EQ(s21_vector_swap[i], s21_vector_swap[i]);
  }
}

TEST(vector, insert_many) {
  s21::vector<int> s21_vector = {0, 1, 2, 3, 9};
  auto* res = s21_vector.insert_many(s21_vector.begin() + 4, 4, 5, 6, 7, 8);

  EXPECT_EQ(s21_vector.size(), 10);
  EXPECT_EQ(s21_vector.capacity(), 10);
  for (int i{}; res != s21_vector.end(); res++, i++) {
    EXPECT_EQ(*(res), i + 4);
  }
}

TEST(vector, insert_many_back) {
  s21::vector<int> s21_vector = {0, 1, 2, 3, 4};
  s21_vector.insert_many_back(5, 6, 7, 8, 9);

  EXPECT_EQ(s21_vector.size(), 10);
  EXPECT_EQ(s21_vector.capacity(), 10);

  for (unsigned i{4}; i < s21_vector.size(); i++) {
    EXPECT_EQ(s21_vector[i], i);
  }
}
