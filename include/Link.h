#pragma once

#include <memory>
#include <type_traits>
namespace chain_of_responsibility
{

template <typename DataType>
class Link
{
public:

    static constexpr bool IsPointerType = std::is_pointer<DataType>::value;

    enum class ProcessingResult
    {
        Continue,
        Stop,
        Error
    };

    using DataRefType = DataType&;
    using ProcessingResultType = typename Link<DataType>::ProcessingResult;

public:

    virtual ProcessingResult Process(DataRefType data) = 0;
};


}