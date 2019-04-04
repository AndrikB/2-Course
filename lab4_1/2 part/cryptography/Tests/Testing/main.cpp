#include <gtest/gtest.h>

#include <QApplication>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(false) << "HUI";

  EXPECT_EQ(5,4);
}

int main(int argc,char*argv[])
{
    QApplication a(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
