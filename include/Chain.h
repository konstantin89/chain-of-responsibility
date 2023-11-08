#pragma once

#include <memory>
#include <vector>

#include "Link.h"

namespace chain_of_responsibility
{

template <typename DataType>
class Chain
{
public: 
    using LinkType = Link<DataType>;
    using DataRefType = typename LinkType::DataRefType;
    using LinkPtrType = std::unique_ptr<LinkType>;
    using ProcessingResult = typename LinkType::ProcessingResult;

    enum class ChainStatus
    {
        Undefined,
        Success,
        Error
    };

public:
    Chain()
    {

    }

    bool AddLink(LinkPtrType link)
    {
        mLinks.push_back(std::move(link));
        return true;
    }

    ChainStatus ProcessData(DataRefType data) const
    {
        for (auto& link : mLinks)
        {
            ProcessingResult result = link->Process(data);
            if (result == ProcessingResult::Stop)
            {
                return ChainStatus::Success;
            }
            else if (result == ProcessingResult::Error)
            {
                return ChainStatus::Error;
            }
        }

        return ChainStatus::Success;
    }

private:
    std::vector<LinkPtrType> mLinks;

};


}