#include <array>

#include "testing.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 0> a;
  EXPECT_TRUE(a.size() == 0);
}

TEST(ArrayTest, InitializerArrayConstructor1) {
  s21::array<int, 4> a = {1, 2, 3, 4};
  EXPECT_TRUE(a.size() == 4);

  auto it = a.begin();
  for (size_t i = 0; i < a.size(); i++) {
    EXPECT_EQ(i + 1, *(it));
    ++it;
  }
}

TEST(ArrayTest, InitializerArrayConstructor2) {
  EXPECT_THROW(([] {
                 s21::array<int, 4> a = {1, 2, 3, 4, 5};
               }()),
               std::invalid_argument);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> b1(a1);

  s21::array<int, 5> a2 = {1, 2, 3, 4, 5};
  s21::array<int, 5> b2(a2);
  EXPECT_EQ(b2.size(), b1.size());

  for (size_t i = 0; i < b2.size(); ++i) {
    EXPECT_EQ(b2[i], b1[i]);
  }
}

TEST(ArrayTest, MoveConstructor) {
  std::array<double, 5> a1 = {1.1, 4.3, 5.3, 5.2, 0.3};
  std::array<double, 5> a2(std::move(a1));

  s21::array<double, 5> b1 = {1.1, 4.3, 5.3, 5.2, 0.3};
  s21::array<double, 5> b2(std::move(b1));

  EXPECT_EQ(a2.size(), b2.size());
  for (std::size_t i = 0; i < a2.size(); ++i) {
    EXPECT_EQ(a2[i], b2[i]);
  }
}

TEST(ArrayTest, MoveAssignmentOperator) {
  std::array<double, 5> a1 = {1.1, 4.3, 5.3, 5.2, 0.3};
  std::array<double, 5> a2 = {2.2, 3.3, 4.4, 5.5, 6.6};

  s21::array<double, 5> b1 = {1.1, 4.3, 5.3, 5.2, 0.3};
  s21::array<double, 5> b2 = {2.2, 3.3, 4.4, 5.5, 6.6};

  a1 = std::move(a2);
  b1 = std::move(b2);

  EXPECT_EQ(a1.size(), b1.size());
  for (std::size_t i = 0; i < a2.size(); ++i) {
    EXPECT_EQ(a1[i], b1[i]);
  }
}

TEST(ArrayTest, CopyAssignmentOperator) {
  std::array<double, 5> a1 = {1.1, 4.3, 5.3, 5.2, 0.3};
  std::array<double, 5> a2;

  s21::array<double, 5> b1 = {1.1, 4.3, 5.3, 5.2, 0.3};
  s21::array<double, 5> b2;

  a2 = a1;
  b2 = b1;

  EXPECT_EQ(a2.size(), b2.size());
  for (std::size_t i = 0; i < a2.size(); ++i) {
    EXPECT_EQ(a2[i], b2[i]);
  }
}

TEST(ArrayTest, begin) {
  std::array<int, 5> a = {1, 2, 3, 4, 5};
  s21::array<int, 5> b = {1, 2, 3, 4, 5};

  auto it1 = a.begin();
  auto it2 = b.begin();
  EXPECT_EQ(*(it1), *(it2));

  *(it1) = 0;
  *(it2) = 0;
  EXPECT_EQ(a[0], b[0]);
}

TEST(ArrayTest, data) {
  std::array<int, 5> a = {1, 2, 3, 4, 5};
  s21::array<int, 5> b = {1, 2, 3, 4, 5};

  auto it1 = a.data();
  auto it2 = b.data();
  EXPECT_EQ(*(it1), *(it2));

  *(it1) = 0;
  *(it2) = 0;
  EXPECT_EQ(a[0], b[0]);
}

TEST(ArrayTest, end) {
  s21::array<int, 5> b = {1, 2, 3, 4, 5};
  int i = 1;
  for (auto it = b.begin(); it != b.end(); ++it, ++i) {
    EXPECT_EQ(*(it), i);
  }
}

TEST(ArrayTest, at1) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  int value = a.at(2);
  EXPECT_EQ(value, 3);
}

TEST(ArrayTest, at2) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  EXPECT_THROW(a.at(5), std::out_of_range);
}

TEST(ArrayTest, ConstAt1) {
  const s21::array<int, 5> a = {1, 2, 3, 4, 5};

  int value = a.at(2);
  EXPECT_EQ(value, 3);
}

TEST(ArrayTest, ConstAt2) {
  const s21::array<int, 5> a = {1, 2, 3, 4, 5};
  EXPECT_THROW(a.at(5), std::out_of_range);
}

TEST(ArrayTest, Front) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  int value = a.front();
  EXPECT_EQ(value, 1);
}

TEST(ArrayTest, ConstFront) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  int value = a.front();
  EXPECT_EQ(value, 1);
}

TEST(ArrayTest, Back) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  int value = a.back();
  EXPECT_EQ(value, 5);
}

TEST(ArrayTest, ConstBack) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  int value = a.back();
  EXPECT_EQ(value, 5);
}

TEST(ArrayTest, Empty1) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  EXPECT_FALSE(a.empty());
}

TEST(ArrayTest, Empty2) {
  s21::array<int, 0> a;
  EXPECT_TRUE(a.empty());
}

TEST(ArrayTest, Size1) {
  s21::array<int, 2> a = {1, 2};
  std::array<int, 2> b = {1, 2};

  EXPECT_EQ(a.size(), b.size());
}

TEST(ArrayTest, Size2) {
  s21::array<int, 0> a;
  std::array<int, 0> b;

  EXPECT_EQ(a.size(), b.size());
}

TEST(ArrayTest, MaxSize) {
  s21::array<int, 2> a = {1, 2};
  std::array<int, 2> b = {1, 2};

  EXPECT_EQ(a.max_size(), b.max_size());
}

TEST(ArrayTest, Swap) {
  std::array<int, 5> a1 = {1, 2, 3, 4, 5};
  std::array<int, 5> a2 = {6, 7, 8, 9, 10};

  s21::array<int, 5> b1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> b2 = {6, 7, 8, 9, 10};

  auto it1 = b2.begin();
  auto it2 = b1.begin();

  a1.swap(a2);
  b1.swap(b2);

  auto it3 = b2.begin();
  auto it4 = b1.begin();
  EXPECT_EQ(it1, it3);
  EXPECT_EQ(it2, it4);

  for (std::size_t i = 0; i < a1.size(); i++) {
    EXPECT_EQ(a1[i], b1[i]);
    EXPECT_EQ(a2[i], b2[i]);
  }
}

TEST(ArrayTest, Fill) {
  s21::array<int, 5> a;
  a.fill(11);
  for (std::size_t i = 0; i < a.size(); i++) EXPECT_EQ(a[i], 11);
}