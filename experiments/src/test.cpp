#include "experiments/test.h"

std::string Test::GetName()
{
    return name_;
}

std::string Test::GetDescription()
{
    return description_;
}

void Test::Run(int i) {
    run_(i);
}
