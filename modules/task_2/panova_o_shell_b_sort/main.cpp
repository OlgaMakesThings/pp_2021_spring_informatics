// Copyright 2021 Panova Olga
#include <gtest/gtest.h>
#include <vector>
#include "./shell_b_sort.h"
#include <omp.h>
#include <stdio.h>
#define TIME

TEST(Odd_Even_Shell, Division_Is_Correct) {
    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    std::vector<std::vector<int>> div_a = Division(a, 4);
    std::vector<std::vector<int>> b = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    ASSERT_EQ(div_a, b);
}

TEST(Odd_Even_Shell, Seq_And_Par_Sorts_Correct_And_Equal) {
    std::vector<int> a = { 10, 9, 18, 7, 6, -5, 1, 22 };
    std::vector<int> res_a = SequentialOddEvenShellSort(a, 4);
    std::vector<int> res_c = ParallelOddEvenShellSort(a, 4);
    std::vector<int> b = { -5, 1, 6, 7, 9, 10, 18, 22 };
    ASSERT_EQ(res_a, b);
    ASSERT_EQ(res_c, b);
}
TEST(Odd_Even_Shell, Vec_5001_Sort) {
    std::vector<int> a = CreateVector(5001);
    std::vector<int> b = ParallelOddEvenShellSort(a, 4);
    std::sort(a.begin(), a.end());
    ASSERT_EQ(a, b);
}
TEST(Odd_Even_Shell, Vec_10000_Par_Sort) {
    std::vector<int> a = CreateVector(10000);
    std::vector<int> b = ParallelOddEvenShellSort(a, 4);
    std::sort(a.begin(), a.end());
    ASSERT_EQ(a, b);
}

TEST(Odd_Even_Shell, Vec_10000_Seq_Sort) {
    std::vector<int> a = CreateVector(10000);
    std::vector<int> b = SequentialOddEvenShellSort(a, 4);
    std::sort(a.begin(), a.end());
    ASSERT_EQ(a, b);
}

TEST(Odd_Even_Shell, Seq_Sort_Time) {
    std::vector<int> a = CreateVector(100000);

    double begin = omp_get_wtime();
    std::vector<int> b = SequentialOddEvenShellSort(a, 8);
    double end = omp_get_wtime();

    #ifdef TIME
      printf("Sequential time: %lf seconds\n", end - begin);
    #endif

    std::sort(a.begin(), a.end());
    ASSERT_EQ(a, b);
}

TEST(Odd_Even_Shell, OMP_Sort_Time) {
    std::vector<int> a = CreateVector(100000);

    double begin = omp_get_wtime();
    std::vector<int> b = ParallelOddEvenShellSort(a, 8);
    double end = omp_get_wtime();

    #ifdef TIME
      printf("Parallel time: %lf seconds\n", end - begin);
    #endif

    std::sort(a.begin(), a.end());
    ASSERT_EQ(a, b);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
