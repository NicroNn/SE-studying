#include <vector>
#include <gtest/gtest.h>
#include "lib/scheduler.h"

TEST(SchedulerTestSuite, AddAndExecuteUnaryTask) {
    TTaskScheduler scheduler;
    auto id1 = scheduler.add([](int x) { return x * 2; }, 5);
    scheduler.executeAll();
    auto result = scheduler.getResult<int>(id1);
    EXPECT_EQ(result, 10);
}

TEST(SchedulerTestSuite, AddAndExecuteBinaryTask) {
    TTaskScheduler scheduler;
    auto id1 = scheduler.add([](int x, int y) { return x + y; }, 3, 7);
    scheduler.executeAll();
    auto result = scheduler.getResult<int>(id1);
    EXPECT_EQ(result, 10);
}

TEST(SchedulerTestSuite, GetFutureResultFromCompletedTask) {
    TTaskScheduler scheduler;
    TaskNo taskNo = scheduler.add([]() { return 42; });
    scheduler.executeAll();
    FutureResult<int> futureResult = scheduler.getFutureResult<int>(taskNo);
    EXPECT_EQ(static_cast<int>(futureResult), 42);
}

TEST(SchedulerTestSuite, GetResultFromCompletedTask) {
    TTaskScheduler scheduler;
    TaskNo taskNo = scheduler.add([]() { return 42; });
    scheduler.executeAll();
    FutureResult<int> result = scheduler.getResult<int>(taskNo);
    EXPECT_EQ(static_cast<int>(result), 42);
}

TEST(SchedulerTestSuite, SchedulerTest1) {
    float a = 1;
    float b = -2;
    float c = 0;

    TTaskScheduler scheduler;

    auto id1 = scheduler.add([](float a, float c) { return -4 * a * c; }, a, c);
    auto fr1 = scheduler.getFutureResult<float>(id1);

    auto id2 = scheduler.add([](float b, float v) { return b * b + v; }, b, fr1);

    auto id3 =
        scheduler.add([](float b, float d) { return -b + std::sqrt(d); }, b, scheduler.getFutureResult<float>(id2));

    auto id4 =
        scheduler.add([](float b, float d) { return -b - std::sqrt(d); }, b, scheduler.getFutureResult<float>(id2));

    auto id5 = scheduler.add([](float a, float v) { return v / (2 * a); }, a, scheduler.getFutureResult<float>(id3));

    auto id6 = scheduler.add([](float a, float v) { return v / (2 * a); }, a, scheduler.getFutureResult<float>(id4));

    scheduler.executeAll();

    ASSERT_EQ(scheduler.getResult<float>(id1), 0);
    ASSERT_EQ(scheduler.getResult<float>(id2), 4);
    ASSERT_EQ(scheduler.getResult<float>(id3), 4);
    ASSERT_EQ(scheduler.getResult<float>(id4), 0);
    ASSERT_EQ(scheduler.getResult<float>(id5), 2);
    ASSERT_EQ(scheduler.getResult<float>(id6), 0);
}

TEST(SchedulerTestSuite, SchedulerTest2) {
    float a = 1;
    float b = -2;
    float c = 0;

    TTaskScheduler scheduler;

    auto id1 = scheduler.add([](float a, float c) { return -4 * a * c; }, a, c);
    auto fr1 = scheduler.getFutureResult<float>(id1);

    auto id2 = scheduler.add([](float b, float v) { return b * b + v; }, b, fr1);

    auto id3 =
        scheduler.add([](float b, float d) { return -b + std::sqrt(d); }, b, scheduler.getFutureResult<float>(id2));

    auto id4 =
        scheduler.add([](float b, float d) { return -b - std::sqrt(d); }, b, scheduler.getFutureResult<float>(id2));

    auto id5 = scheduler.add([](float a, float v) { return v / (2 * a); }, a, scheduler.getFutureResult<float>(id3));

    auto id6 = scheduler.add([](float a, float v) { return v / (2 * a); }, a, scheduler.getFutureResult<float>(id4));

    ASSERT_EQ(scheduler.getResult<float>(id4), 0);
    ASSERT_EQ(scheduler.getResult<float>(id5), 2);
    ASSERT_EQ(scheduler.getResult<float>(id2), 4);
    ASSERT_EQ(scheduler.getResult<float>(id6), 0);
    ASSERT_EQ(scheduler.getResult<float>(id3), 4);
    ASSERT_EQ(scheduler.getResult<float>(id1), 0);
}

TEST(SchedulerTestSuite, SchedulerTest3) {
    TTaskScheduler scheduler;
    auto id1 = scheduler.add([](int a) { return a; }, 1312);
    auto id2 = scheduler.add([](float a) { return a; }, 13.12);
    scheduler.executeAll();
    ASSERT_EQ(scheduler.getResult<int>(id1), 1312);
    ASSERT_LE(scheduler.getResult<float>(id2) - 13.12, 0.00001);
}

TEST(Defense, Defense) {
    TTaskScheduler scheduler;
    int b = 2;
    auto id1 = scheduler.add([](int a){return 1;}, b);
    id1 = TaskNo(5);
    auto id2 = scheduler.add([](int a){return 1;}, scheduler.getFutureResult<int>(id1));
    auto id3 = scheduler.add([](int a){return 1;}, scheduler.getFutureResult<int>(id2));
    ASSERT_EQ(scheduler.getResult<int>(id1), 1);
}

