#include <iostream>
#include <cassert>
#include <complex>
#include <string>
#include "add_task.cc"

void TestCount() {
    Set<int> int_set;
    int_set.Insert(1);
    int_set.Insert(2);
    int_set.Insert(3);
    int_set.Insert(3);
    assert(int_set.Count(1) == 1);
    assert(int_set.Count(2) == 1);
    assert(int_set.Count(3) == 2);
    assert(int_set.Count(4) == 0);
}

void TestComplexFloat() {
    Set<std::complex<float>> complex_float_set;
    std::complex<float> c1(1.0f, 2.0f);
    std::complex<float> c2(3.0f, 4.0f);
    complex_float_set.Insert(c1);
    complex_float_set.Insert(c2);
    assert(complex_float_set.Contains(c1));
    assert(complex_float_set.Contains(c2));
}

void TestComplexDouble() {
    Set<std::complex<double>> complex_double_set;
    std::complex<double> c1(1.0, 2.0);
    std::complex<double> c2(3.0, 4.0);
    complex_double_set.Insert(c1);
    complex_double_set.Insert(c2);
    assert(complex_double_set.Contains(c1));
    assert(complex_double_set.Contains(c2));
}

void TestString() {
    Set<std::string> string_set;
    string_set.Insert("hello");
    string_set.Insert("world");
    assert(string_set.Contains("hello"));
    assert(string_set.Contains("world"));
}


void TestIterators() {
    Set<int> int_set;
    int_set.Insert(1);
    int_set.Insert(2);
    int_set.Insert(3);
    int_set.Insert(4);

    auto it = int_set.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 3);
    ++it;
    assert(*it == 4);
    ++it;
    assert(it == int_set.end());
}

int main() {
    TestCount();
    TestComplexFloat();
    TestComplexDouble();
    TestString();
    TestIterators();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
