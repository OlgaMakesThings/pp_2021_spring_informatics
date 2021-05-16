// Copyright 2021 Tyurmina Alexandra 
#include <tbb/tbb.h>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <utility>
#include "../../../modules/task_3/tyurmina_a_shell_betcher/shell_betcher.h"

std::vector<int> Random(int size) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<int> vec1(size);
    for (int i = 0; i < size; i++) {
        vec1[i] = gen() % 100;
    }
    return vec1;
}

std::vector<std::vector<int>> Separat(const std::vector<int>& massiv, size_t n) {
    size_t remainder = massiv.size() % n;
    size_t integer = massiv.size() / n;
    size_t finish = 0;
    size_t start = 0;
    std::vector<std::vector<int>> result;

    for (size_t i = 0; i < n; ++i) {
        if (remainder > 0) {
            finish = finish + (integer + !!(remainder--));
        }
        else {
            finish = finish + integer;
        }
        std::vector<int> hal(massiv.begin() + start, massiv.begin() + finish);
        result.push_back(hal);
        start = finish;
    }
    return result;
}

std::vector<int> ShellSort(const std::vector<int>& massiv, int size) {
    int part;
    int i;
    int j;
    int temp;
    std::vector<int>mass(massiv);

    for (part = size / 2; part > 0; part = part / 2) {
        for (i = part; i < size; i++) {
            for (j = i - part; j >= 0; j = j - part) {
                if (mass[j] > mass[j + part]) {
                    temp = mass[j];
                    mass[j] = mass[j + part];
                    mass[j + part] = temp;
                }
            }
        }
    }
    return mass;
}

std::vector<int> BetcherEven(const std::vector<int>& massiv1, const std::vector<int>& massiv2) {
    int size1 = massiv1.size();
    int size2 = massiv2.size();
    int size_result = size1 / 2 + size2 / 2 + size1 % 2 + size2 % 2;
    std::vector <int> mass_result(size_result);
    int i1 = 0;
    int i2 = 0;
    int i = 0;

    while ((i1 < size1) && (i2 < size2)) {
        if (massiv1[i1] <= massiv2[i2]) {
            mass_result[i] = massiv1[i1];
            i1 += 2;
        }
        else {
            mass_result[i] = massiv2[i2];
            i2 += 2;
        }
        i++;
    }

    if (i1 >= size1) {
        for (int j = i2; j < size2; j += 2) {
            mass_result[i] = massiv2[j];
            i++;
        }
    }
    if (i2 >= size2) {
        for (int j = i1; j < size1; j += 2) {
            mass_result[i] = massiv1[j];
            i++;
        }
    }

    return mass_result;
}

std::vector<int> BetcherOdd(const std::vector<int>& massiv1, const std::vector<int>& massiv2) {
    int size1 = massiv1.size();
    int size2 = massiv2.size();
    int size_result = size1 / 2 + size2 / 2;
    std::vector <int> mass_result(size_result);
    int i1 = 1;
    int i2 = 1;
    int i = 0;

    while ((i1 < size1) && (i2 < size2)) {
        if (massiv1[i1] <= massiv2[i2]) {
            mass_result[i] = massiv1[i1];
            i1 += 2;
        }
        else {
            mass_result[i] = massiv2[i2];
            i2 += 2;
        }
        i++;
    }

    if (i1 >= size1) {
        for (int j = i2; j < size2; j += 2) {
            mass_result[i] = massiv2[j];
            i++;
        }
    }
    if (i2 >= size2) {
        for (int j = i1; j < size1; j += 2) {
            mass_result[i] = massiv1[j];
            i++;
        }
    }
    return mass_result;
}

std::vector<int> BetcherMerge(const std::vector<int>& massiveven, const std::vector<int>& massivodd) {
    int size1 = massiveven.size();
    int i1 = 0;
    int size2 = massivodd.size();
    int i2 = 0;
    int i = 0;
    int temp;
    int size_result = massiveven.size() + massivodd.size();
    std::vector <int> mass_result(size_result);

    while ((i1 < size1) && (i2 < size2)) {
        mass_result[i] = massiveven[i1];
        mass_result[i + 1] = massivodd[i2];
        i1 = i1 + 1;
        i2 = i2 + 1;
        i = i + 2;
    }
    if ((i1 < size1) && (i2 >= size2)) {
        for (int a = i; a < size_result; a++) {
            mass_result[a] = massiveven[i1];
            i1 = i1 + 1;
        }
    }
    else {
        for (int a = i; a < size_result; a++) {
            mass_result[a] = massiveven[i2];
            i2 = i2 + 1;
        }
    }
    for (int i = 1; i < size_result; i++) {
        if (mass_result[i] < mass_result[i - 1]) {
            temp = mass_result[i];
            mass_result[i] = mass_result[i - 1];
            mass_result[i - 1] = temp;
        }
    }
    return mass_result;
}

std::vector<int> ShellBetcherSeq(const std::vector<int>& massiv, const int n, int size) {
    std::vector<std::vector<int>> mass = Separat(massiv, n);
    const int n1 = n;

    for (int i = 0; i < static_cast<int>(mass.size()); i++) {
        mass[i] = ShellSort(mass[i], mass[i].size());
    }
    return ShellBetcherMerge(mass, n1, size); 
}

std::vector<int> ShellBetcherMerge(const std::vector<std::vector<int>>& massiv, const int n, int size) {
    std::vector<int> ev;
    std::vector<int> od;
    std::vector<int> result = massiv[0];

    for (int i = 1; i < n; i++) {
        od = BetcherOdd(result, massiv[i]);
        ev = BetcherEven(result, massiv[i]);
        result = BetcherMerge(ev,od);
    }
    return result;
}

std::vector<int> MergeTBB(const std::vector<int>& massiv, const int n, int size) {
    std::vector<std::vector<int>> mass = Separat(massiv, n);

    tbb::task_scheduler_init init(n);
    tbb::parallel_for(tbb::blocked_range<size_t>(0, mass.size(), 1),
        [&mass](const tbb::blocked_range<size_t>& r) {
            int start= r.begin(), finish = r.end();
            for (int i = start; i != finish; ++i)
                mass[i] = ShellSort(mass[i], mass[i].size());
        }, tbb::simple_partitioner());

    init.terminate();
    return ShellBetcherMerge(mass, n, size);
}
