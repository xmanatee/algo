#pragma once

#include <vector>
#include <iostream>

template<class T>
void readVector(std::vector<T>& items, std::istream& in = std::cin);

void writeBoolYesNo(const std::vector<bool>& answers, std::ostream& out = std::cout);
