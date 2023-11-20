#include <catch2/catch_test_macros.hpp>

#include "TestUtils.h"

TEST_CASE("Sanity test without pointers", "[Chain, basic, not pointer]")
{
    using ChainType = chain_of_resp::Chain<Number>;
    ChainType numbersProcessingChain;

    auto isEvenLink = std::make_unique<IsNumberEvenLink>();
    numbersProcessingChain.AddLink(std::move(isEvenLink));

    auto isPositiveLink = std::make_unique<IsNumberPositiveLink>();
    numbersProcessingChain.AddLink(std::move(isPositiveLink));

    auto num1 = Number(4);

    auto processStatus = numbersProcessingChain.ProcessData(num1);
    REQUIRE(chain_of_resp::ChainStatus::Success == processStatus);
    REQUIRE(num1.isEven);
    REQUIRE(num1.isPositive);

    auto num2 = Number(-3);

    processStatus = numbersProcessingChain.ProcessData(num2);
    REQUIRE(chain_of_resp::ChainStatus::Success == processStatus);
    REQUIRE(!num2.isEven);
    REQUIRE(!num2.isPositive);
}

TEST_CASE("Sanity test with pointers", "[Chain, basic, not pointer]")
{
    using ChainType = chain_of_resp::Chain<Text::TextPtrType>;
    ChainType textProcessingChain;

    auto linesCounterLink = std::make_unique<TextLinesCounterLink>();
    textProcessingChain.AddLink(std::move(linesCounterLink));

    auto charCounterLink = std::make_unique<TextCharacterCounterLink>();
    textProcessingChain.AddLink(std::move(charCounterLink));

    auto text1 = std::make_shared<Text>("This \n Is \n Text");

    auto processStatus = textProcessingChain.ProcessData(text1);
    REQUIRE(chain_of_resp::ChainStatus::Success == processStatus);
    REQUIRE(text1->numberOfCharacters == 16);
    REQUIRE(text1 ->numberOfLines == 3);

    auto text2 = std::make_shared<Text>("another text \n a\n n\n Is \n Text");

    processStatus = textProcessingChain.ProcessData(text2);
    REQUIRE(chain_of_resp::ChainStatus::Success == processStatus);
    REQUIRE(text2->numberOfCharacters == 30);
    REQUIRE(text2->numberOfLines == 5);
}
