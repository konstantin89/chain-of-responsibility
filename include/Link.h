#pragma once

namespace chain_of_responsibility
{

template <typename DataType>
class Link
{
public:

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