#include <lib/ThreeDArray.h>
#include <gtest/gtest.h>
#include <sstream>

TEST(ThreeDArrayTestSuit, MemoryTest) {
    ThreeDArray array = ThreeDArray::make_array(2, 2, 2);
    std::cout << array.CalculateTotalMemoryUsage();
    ASSERT_TRUE(array.CalculateTotalMemoryUsage() <= (5 * 5 * 5 * 17) / 8 + ThreeDArray::kExtraMemory);
}

TEST(ThreeDArrayTestSuit, GetElementTest) {
    ThreeDArray array = ThreeDArray::make_array(5, 5, 5);
    array(0, 0, 0) = 1;
    array(0, 1, 0) = 2;
    array(0, 0, 1) = 3;

    ASSERT_EQ(array[0][0][0], 1);
    ASSERT_EQ(array[0][1][0], 2);
    ASSERT_EQ(array[0][0][1], 3);
}

TEST(ThreeDArrayTestSuit, DefaultConstructorTest) {
    ThreeDArray array = ThreeDArray::make_array(3, 3, 3);

    ASSERT_EQ(array.GetSize(), 27);
    ASSERT_EQ(array.GetHeight(), 3);
    ASSERT_EQ(array.GetWidth(), 3);
    ASSERT_EQ(array.GetDepth(), 3);
}

// Test for the copy constructor
TEST(ThreeDArrayTestSuit, CopyConstructorTest) {
    ThreeDArray array1 = ThreeDArray::make_array(2, 2, 2);
    array1(0, 0, 0) = 1;

    ThreeDArray array2 = array1;

    ASSERT_EQ(array2.GetElement(0), 1);
}

// Test for the ExtraFieldToArray method
TEST(ThreeDArrayTestSuit, ExtraFieldToArrayTest) {
    ThreeDArray array = ThreeDArray::make_array(2, 2, 2);

    array.ExtraFieldToArray(4);

    ASSERT_EQ(array.GetElement(4), 0);  // ExtraFieldToArray should set the element to 0
}

// Test for the multiplication operator
TEST(ThreeDArrayTestSuit, MultiplicationOperatorTest) {
    ThreeDArray array = ThreeDArray::make_array(2, 2, 2);

    array[0][0][0] = 2;
    ThreeDArray result = array * 3;

    ASSERT_EQ(result[0][0][0], 6);
}

// Test for the addition operator
TEST(ThreeDArrayTestSuit, AdditionOperatorTest) {
    ThreeDArray array1 = ThreeDArray::make_array(2, 2, 2);
    ThreeDArray array2 = ThreeDArray::make_array(2, 2, 2);

    array1[0][0][0] = 5;
    array2[0][0][0] = 7;
    array1[1][0][0] = 2;
    array2[1][0][0] = 3;

    ThreeDArray result = array1 + array2;

    ASSERT_EQ(result[0][0][0], 12);
    ASSERT_EQ(result[1][0][0], 5);
}

// Test for the subtraction operator
TEST(ThreeDArrayTestSuit, SubtractionOperatorTest) {
    ThreeDArray array1 = ThreeDArray::make_array(2, 2, 2);
    ThreeDArray array2 = ThreeDArray::make_array(2, 2, 2);

    array1[0][0][0] = 10;
    array2[0][0][0] = 5;
    array1[1][0][0] = 10;
    array2[1][0][0] = 2;

    ThreeDArray result = array1 - array2;

    ASSERT_EQ(result[0][0][0], 5);
    ASSERT_EQ(result[1][0][0], 8);
}

// Test for negative result in subtraction
TEST(ThreeDArrayTestSuit, SubtractionNegativeResultTest) {
    ThreeDArray array1 = ThreeDArray::make_array(2, 2, 2);
    ThreeDArray array2 = ThreeDArray::make_array(2, 2, 2);

    array1[0][0][0] = 5;
    array2[0][0][0] = 10;

    ASSERT_THROW({
                     try {
                         ThreeDArray result = array1 - array2;
                     } catch (const std::runtime_error& e) {
                         ASSERT_STREQ(e.what(), "Negative result");
                         throw;
                     }
                 }, std::runtime_error);
}

// Test for different sizes in subtraction
TEST(ThreeDArrayTestSuit, SubtractionDifferentSizesTest) {
    ThreeDArray array1 = ThreeDArray::make_array(2, 2, 2);
    ThreeDArray array2 = ThreeDArray::make_array(2, 2, 3);

    ASSERT_THROW({
                     try {
                         ThreeDArray result = array1 - array2;
                     } catch (const std::runtime_error& e) {
                         ASSERT_STREQ(e.what(), "Different sizes");
                         throw;
                     }
                 }, std::runtime_error);
}

// Test for the output operator
TEST(ThreeDArrayTestSuit, OutputOperatorTest) {
    ThreeDArray array = ThreeDArray::make_array(2, 2, 2);
    array[0][0][0] = 1;
    array[0][1][0] = 2;
    array[1][1][1] = 3;

    std::ostringstream stream;
    stream << array;

    ASSERT_EQ(stream.str(), "1 0 2 0 0 0 0 3 ");
}

// Test for the input operator
TEST(ThreeDArrayTestSuit, InputOperatorTest) {
    ThreeDArray array = ThreeDArray::make_array(2, 2, 2);

    std::istringstream stream("1 0 2 0 0 0 0 3 ");
    stream >> array;

    ASSERT_EQ(array[0][0][0], 1);
    ASSERT_EQ(array[0][1][0], 2);
    ASSERT_EQ(array[1][1][1], 3);
}

// Test for the output and input operators together
TEST(ThreeDArrayTestSuit, OutputInputOperatorsTest) {
    ThreeDArray array1 = ThreeDArray::make_array(2, 2, 2);
    array1[0][0][0] = 4;
    array1[0][1][0] = 5;
    array1[0][0][1] = 6;

    std::ostringstream outputStream;
    outputStream << array1;

    ThreeDArray array2 = ThreeDArray::make_array(2, 2, 2);

    std::istringstream inputStream(outputStream.str());
    inputStream >> array2;

    ASSERT_EQ(array2[0][0][0], 4);
    ASSERT_EQ(array2[0][1][0], 5);
    ASSERT_EQ(array2[0][0][1], 6);
}

