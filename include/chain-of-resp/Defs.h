#pragma once

namespace chain_of_resp
{

enum class ProcessingResult
{
    Undefined,
    Continue,
    Stop,
    Error
};

enum class ChainStatus
{
    Undefined,
    Success,
    Error
};

}
