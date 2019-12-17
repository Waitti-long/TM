#include "gtest/gtest.h"

int pow2(int n) {
    return n * n;
}

#ifndef __TEST__

TEST(atest,t1){
    EXPECT_EQ(pow2(10),100);
    EXPECT_EQ(pow2(2),3) << "fuck";
}

#endif