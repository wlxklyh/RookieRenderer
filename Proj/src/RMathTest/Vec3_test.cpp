#include "gtest/gtest.h"
#include "Vec3.h"
#include "Ray.h"

using namespace RMath;

TEST(Vec3, Operater) {
    FVec3 vec1(1.2, 1.2, 1.2);
    FVec3 vec2(2.4, 2.4, 2.4);
    FVec3 vec3(2, 2, 2);

    ASSERT_EQ(vec1 + vec1, vec2);
    ASSERT_EQ(vec2 - vec1, vec1);
    ASSERT_EQ(vec1 * vec3, vec2);
    ASSERT_EQ(vec2 / vec3, vec1);
    ASSERT_EQ(vec2 / 2, vec1);
    ASSERT_EQ(vec1 * 2, vec2);
    ASSERT_EQ(2 * vec1, vec2);
}


TEST(Vec3, TestDoSomething) {
    EXPECT_EQ(1, 1);
}


