#ifndef _UNI_PTR_DUMMY_H_
#define _UNI_PTR_DUMMY_H_

#include <memory>
#include <vector>

//std::unique_ptr<std::vector<int>> int_vector;
static std::unique_ptr<std::vector<int>> static_int_vector;

void print_unique_ptrs();

#endif
