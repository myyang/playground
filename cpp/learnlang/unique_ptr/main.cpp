#include <memory>
#include <vector>

#include "dummy.h"

int main()
{
    print_unique_ptrs();

    static_int_vector = std::make_unique<std::vector<int>>();

    printf("static: %x\n", static_int_vector.get());

    print_unique_ptrs();
}
