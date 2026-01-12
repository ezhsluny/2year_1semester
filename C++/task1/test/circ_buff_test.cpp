#include "../circ_buff.hpp"
#include <gtest/gtest.h>


TEST(CircullarBufferTest, FailedTest){
  EXPECT_TRUE(false);
}


TEST(CircularBufferTest, Constructor) {
  CircularBuffer buffer;
  EXPECT_TRUE(buffer.empty());
  EXPECT_EQ(buffer.capacity(), 0);
  EXPECT_EQ(buffer.size(), 0);
}

TEST(CircularBufferTest, ConstructorWithCapacity) {
  CircularBuffer buffer1(5);
  EXPECT_TRUE(buffer1.empty());
  EXPECT_EQ(buffer1.capacity(), 5);
  EXPECT_EQ(buffer1.size(), 0);
}

TEST(CircularBufferTest, ConstructorWithElem) {
  CircularBuffer buffer2(5, 1);
  EXPECT_FALSE(buffer2.empty());
  EXPECT_EQ(buffer2.capacity(), 5);
  EXPECT_EQ(buffer2.size(), 5);
  EXPECT_EQ(buffer2.front(), 1);
}

TEST(CircularBufferTest, CopyConstructor) {
  CircularBuffer buffer2(5, 1);
  CircularBuffer buffer3(buffer2);
  EXPECT_EQ(buffer3, buffer2);
}

TEST(CircularBufferTest, Idxs) {
  CircularBuffer buffer2(5, 1);
  EXPECT_EQ(buffer2[1], 1);
  EXPECT_EQ(buffer2.at(1), 1);
}

TEST(CircularBufferTest, FrontBackElem) {
  CircularBuffer buffer(3);
  buffer.push_back(2);
  buffer.push_front(1);
  buffer.push_front(3);
  EXPECT_EQ(buffer.front(), buffer[0]) << "front elem:" << (int)buffer.front();
  EXPECT_EQ(buffer.back(), buffer[buffer.size() - 1]);
}

TEST(CircularBufferTest, Rotate) {
  CircularBuffer buffer(3);
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);
  buffer.rotate(1);
  EXPECT_EQ(buffer.front(), 2);
}

TEST(CircularBufferTest, FullReserve) {
  CircularBuffer buffer(10, 8);
  EXPECT_TRUE(buffer.full());
  buffer.pop_front();
  buffer.pop_front();
  EXPECT_EQ(buffer.reserve(), 2);
}

TEST(CircularBufferTest, SetCapacityResize) {
  CircularBuffer buffer(10, 2);
  EXPECT_EQ(buffer.capacity(), 10);
  buffer.set_capacity(20);
  EXPECT_EQ(buffer.capacity(), 20);
  EXPECT_EQ(buffer.size(), 10);
  buffer.resize(15, 3);
  EXPECT_EQ(buffer.capacity(), 20);
  EXPECT_EQ(buffer.size(), 15);
}

TEST(CircularBufferTest, AssignmentOperator) {
  CircularBuffer buffer1(10, 8);
  CircularBuffer buffer2(10);
  buffer2 = buffer1;
  EXPECT_EQ(buffer1, buffer2);
}

TEST(CircularBufferTest, Swap) {
  CircularBuffer buffer1(10, 8);
  CircularBuffer buffer2(10, -8);
  buffer1.swap(buffer2);
  EXPECT_EQ(buffer1[0], -8);
  EXPECT_EQ(buffer2[0], 8);
}