#include "math/quarternion.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(QuarternionTest, Identities) {
  using Q = Quarternion<int>;

  // Multiplicitive identities.
  EXPECT_EQ(Q::i * Q::i, -1);
  EXPECT_EQ(Q::j * Q::j, -1);
  EXPECT_EQ(Q::k * Q::k, -1);
  EXPECT_EQ(Q::i * Q::j, Q::k);
  EXPECT_EQ(Q::j * Q::i, -Q::k);
  EXPECT_EQ(Q::j * Q::k, Q::i);
  EXPECT_EQ(Q::k * Q::j, -Q::i);
  EXPECT_EQ(Q::k * Q::i, Q::j);
  EXPECT_EQ(Q::i * Q::k, -Q::j);
  EXPECT_EQ(Q::i * Q::j * Q::k, -1);

  // Division identities.
  EXPECT_EQ(Q::i / Q::i, 1);
  EXPECT_EQ(Q::j / Q::j, 1);
  EXPECT_EQ(Q::k / Q::k, 1);
  EXPECT_EQ(Q::i / Q::j, -Q::k);
  EXPECT_EQ(Q::j / Q::i, Q::k);
  EXPECT_EQ(Q::j / Q::k, -Q::i);
  EXPECT_EQ(Q::k / Q::j, Q::i);
  EXPECT_EQ(Q::k / Q::i, -Q::j);
  EXPECT_EQ(Q::i / Q::k, Q::j);
}

TEST(QuarternionTest, DebugString) {
  using Q = Quarternion<int>;

  EXPECT_EQ(Q(0).DebugString(), "0");
  EXPECT_EQ(Q::i.DebugString(), "i");
  EXPECT_EQ(Q::j.DebugString(), "j");
  EXPECT_EQ(Q::k.DebugString(), "k");
  EXPECT_EQ(Q(1, 1, 1, 1).DebugString(), "1+i+j+k");
  EXPECT_EQ(Q(2, 2, 2, 2).DebugString(), "2+2i+2j+2k");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
