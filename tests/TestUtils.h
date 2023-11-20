#pragma once

#include <string>
#include <algorithm>

#include "chain-of-resp/Chain.h"


// ------------------- Number processing chain --------------------

class Number
{
public:

    Number(int number) : mNumber(number) { }
    int& GetValue() { return mNumber; }

    bool isEven = false;
    bool isPositive = false;

private:
    int mNumber;
};

class IsNumberEvenLink : public chain_of_resp::Link<Number>
{
public:


    chain_of_resp::ProcessingResult Process(DataRefType data) override
    {

        data.isEven = !(data.GetValue() % 2);
        return chain_of_resp::ProcessingResult::Continue;
    }
};

class IsNumberPositiveLink : public chain_of_resp::Link<Number>
{
public:

    chain_of_resp::ProcessingResult Process(DataRefType data) override
    {
        data.isPositive = data.GetValue() >= 0;
        return chain_of_resp::ProcessingResult::Continue;
    }
};

// ------------------- Text processing chain --------------------
class Text
{
public:
    using TextPtrType = std::shared_ptr<Text>;

    Text(std::string text) : mText(text) {};
    std::string& GetText() { return mText; }

    long numberOfLines = 0;
    long numberOfCharacters = 0;

private:
    std::string mText;
};

class TextLinesCounterLink : public chain_of_resp::Link<Text::TextPtrType>
{
    chain_of_resp::ProcessingResult Process(DataRefType data) override
    {
        auto text = data->GetText();
        
        data->numberOfLines = std::count_if(text.begin(), text.end(), [](char c)
        {
            return (c == '\n');
        });

        if (data->numberOfLines) data->numberOfLines++;

        return chain_of_resp::ProcessingResult::Continue;
    }
};

class TextCharacterCounterLink : public chain_of_resp::Link<Text::TextPtrType>
{
    chain_of_resp::ProcessingResult Process(DataRefType data) override
    {
        auto text = data->GetText();
        data->numberOfCharacters = text.length();
        return chain_of_resp::ProcessingResult::Continue;
    }
};