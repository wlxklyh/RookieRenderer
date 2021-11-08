#include "gtest/gtest.h"
#include "RPhysics.h"

using namespace RMath;
using namespace RPhysics;

TEST(BVH, TestSphereBoundindBox) {
    Hitable *list[1];
    list[0] = new Sphere(FVec3(0.1, 0.2, 0.3), 0.5, nullptr);
    BVHNode *node = new BVHNode(list, 1, 0, 0);

    AABB aabb;
    node->BoundindBox(0, 0, aabb);

    EXPECT_FLOAT_EQ(aabb.MinV.X(), -0.4);
    EXPECT_FLOAT_EQ(aabb.MinV.Y(), -0.3);
    EXPECT_FLOAT_EQ(aabb.MinV.Z(), -0.2);

    EXPECT_FLOAT_EQ(aabb.MaxV.X(), 0.6);
    EXPECT_FLOAT_EQ(aabb.MaxV.Y(), 0.7);
    EXPECT_FLOAT_EQ(aabb.MaxV.Z(), 0.8);
}


TEST(BVH, TestSphereBoundindBox2) {
    Hitable *list[2];
    list[0] = new Sphere(FVec3(0.1, 0.2, 0.3), 0.5, nullptr);
    list[1] = new Sphere(FVec3(0.6, 0.7, 0.8), 0.5, nullptr);
    BVHNode *node = new BVHNode(list, 2, 0, 0);

    AABB aabb;
    node->BoundindBox(0, 0, aabb);

    EXPECT_FLOAT_EQ(aabb.MinV.X(), -0.4);
    EXPECT_FLOAT_EQ(aabb.MinV.Y(), -0.3);
    EXPECT_FLOAT_EQ(aabb.MinV.Z(), -0.2);

    EXPECT_FLOAT_EQ(aabb.MaxV.X(), 1.1);
    EXPECT_FLOAT_EQ(aabb.MaxV.Y(), 1.2);
    EXPECT_FLOAT_EQ(aabb.MaxV.Z(), 1.3);
}


TEST(BVH, TestSphereBoundindBox10) {
    static const int sphereNum = 10;
    Hitable *list[sphereNum];
    for (int i = 0; i < sphereNum; i++) {
        list[i] = new Sphere(FVec3(i * 0.5, i * 0.5, i * 0.5), 0.5, nullptr);
    }
    BVHNode *node = new BVHNode(list, 10, 0, 0);
    AABB aabb;
    node->BoundindBox(0, 0, aabb);
    EXPECT_FLOAT_EQ(aabb.MinV.X(), -0.5);
    EXPECT_FLOAT_EQ(aabb.MinV.Y(), -0.5);
    EXPECT_FLOAT_EQ(aabb.MinV.Z(), -0.5);

    EXPECT_FLOAT_EQ(aabb.MaxV.X(), 0.5 * sphereNum);
    EXPECT_FLOAT_EQ(aabb.MaxV.Y(), 0.5 * sphereNum);
    EXPECT_FLOAT_EQ(aabb.MaxV.Z(), 0.5 * sphereNum);
}

TEST(BVH, Test10SpheresHitRay) {
    static const int sphereNum = 10;
    Hitable *list[sphereNum];
    for (int i = 0; i < sphereNum; i++) {
        list[i] = new Sphere(FVec3(i * 0.5, i * 0.5, i * 0.5), 0.5, nullptr);
    }
    BVHNode *node = new BVHNode(list, 10, 0, 0);
    HitRecord hitRecord;
    node->Hit(Ray(FVec3(0.0,0.0,0.0),FVec3(1,1,1)), 0,999999999, hitRecord);


    EXPECT_FLOAT_EQ(hitRecord.p.X(), 0.5 - sqrt(0.5*0.5/3));
    EXPECT_FLOAT_EQ(hitRecord.p.Y(), 0.5 - sqrt(0.5*0.5/3));
    EXPECT_FLOAT_EQ(hitRecord.p.Z(), 0.5 - sqrt(0.5*0.5/3));

}