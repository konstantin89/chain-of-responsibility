#include <iostream>
#include <memory>
#include <vector>
#include <unordered_set>

#include "Chain.h"

class EmailData
{
public:

    EmailData(std::string content, std::string sender) : mContent(content), mSender(sender) { }

    void MarkAsSpam()
    {
        mIsSpam = true;
    }

    bool IsMarkedAsSpam() const
    {
        return mIsSpam;
    }

    void MarkSenderAsBlocked()
    {
        mIsSenderBlocked = true;
    }

    bool IsSenderBlocked() const
    {
        return mIsSenderBlocked;
    }

    const std::string& GetContent() const
    {
        return mContent;
    }

    std::string GetSender() const
    {
        return mSender;
    }

private:

    bool mIsSpam = false;
    bool mIsSenderBlocked = false;
    std::string mContent = "";
    std::string mSender = "";

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

class SenderInspectionFilterLink : public chain_of_responsibility::Link<EmailData>
{
public:

    using ProcessingResult = typename chain_of_responsibility::Link<EmailData>::ProcessingResult;

    ProcessingResult Process(DataRefType data) override
    {
        auto sender = data.GetSender();

        if (mBlockedSenders.find(sender) != mBlockedSenders.end())
        {
            // Sender is in blocked senders list
            data.MarkSenderAsBlocked();
        }

        return ProcessingResult::Continue;
    }

private:
    std::unordered_set<std::string> mBlockedSenders = { "john@mail.com" };
};

int main()
{
    // Create chain link
    using ChainType = chain_of_responsibility::Chain<EmailData>;
    ChainType emailFilteringChain;

    // Create link that is responsible for spam detection in email
    auto spamFilterLink = std::make_unique<SpamFilterLink>();
    emailFilteringChain.AddLink(std::move(spamFilterLink));

    // Create link that is responsible for filtering senders
    auto senderFilterLink = std::make_unique<SenderInspectionFilterLink>();
    emailFilteringChain.AddLink(std::move(senderFilterLink));

    // Create basic email
    std::string simpleEmailContent = "Hello dear friend! This is a spam email to waste your time!";
    std::string senderEmail = "ela@yahoo.ru";
    EmailData email(simpleEmailContent, senderEmail);

    // Process email in chain
    auto processStatus = emailFilteringChain.ProcessData(email);
    if (ChainType::ChainStatus::Success != processStatus)
    {
        std::cout << "Failed to process email!" << std::endl;
        return -1;
    }

    // Check if email has been marked as spam
    if (email.IsMarkedAsSpam())
    {
        std::cout << "Email marked as spam" << std::endl;
    }

    // Check if email sender is blocked
    if (!email.IsSenderBlocked())
    {
        std::cout << "Email sender is not blocked" << std::endl;
    }

    return 0;
}
