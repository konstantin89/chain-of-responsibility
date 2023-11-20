#pragma once

#include <memory>
#include <type_traits>

#include "Defs.h"

namespace chain_of_resp
{

template <typename DataType>
class Link
{
public:

    using DataRefType = DataType&;

public:

    virtual ProcessingResult Process(DataRefType data) = 0;
};


}