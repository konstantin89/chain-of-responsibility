#include <iostream>
#include <memory>
#include <vector>

#include "Chain.h"

class EmailData
{
public:

    EmailData(std::string content): mContent(content){ }

    void MarkAsSpam()
    {
        mIsSpam = true;
    }

    bool IsMarkedAsSpam()
    {
        return mIsSpam;
    }

    std::string GetContent()
    {
        return mContent;
    }

private:
    bool mIsSpam = false;
    std::string mContent;

};

class SpamFilterLink : public chain_of_responsibility::Link<EmailData>
{
public: 

    using ProcessingResult = typename chain_of_responsibility::Link<EmailData>::ProcessingResult;

    ProcessingResult Process(DataRefType data) override
    {
        auto content = data.GetContent();

        for (auto spamKeyword : mSpamKeywords)
        {
            auto pos = content.find(spamKeyword);
            if (pos != std::string::npos)
            {
                data.MarkAsSpam();
                return ProcessingResult::Continue;
            }
        }

        return ProcessingResult::Continue;
    }

private:
    std::vector<std::string> mSpamKeywords = { "spam", "hello" };
};

int main()
{
    using ChainType = chain_of_responsibility::Chain<EmailData>;
    ChainType emailFilteringChain;

    auto spamFilterLink = std::make_unique<SpamFilterLink>();
    emailFilteringChain.AddLink(std::move(spamFilterLink));

    std::string simpleEmailContent = "Hello dear friend! This is a spam email to waste your time!";
    EmailData email(simpleEmailContent);

    auto processStatus = emailFilteringChain.ProcessData(email);
    if (ChainType::ChainStatus::Success != processStatus)
    {
        std::cout << "Failed to process email!" << std::endl;
        return -1;
    }

    if (email.IsMarkedAsSpam())
    {
        std::cout << "Email marked as Spam!" << std::endl;
    }

    return 0;
}
