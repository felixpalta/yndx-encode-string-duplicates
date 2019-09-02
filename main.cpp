#include <iostream>
#include <cstring>

const char * TestCases[] = {
    "","",
    "A","A",
    "AA","A2",
    "AAA","A3",
    "AB","AB",
    "ABC","ABC",
    "ABBC","AB2C",
    "AABBC","A2B2C",
    "AAAAA","A5",
    "AAAAABBBCCCCCC","A5B3C6",
    "AAAAAAAAAAAABBBBBBBBBBBBBBCCCCCC","A12B14C6",
    NULL
};

std::string DoIt(const char * s) {
    std::string ret;
    if (!s)
        return ret;

    char prev = *s;
    if (prev == 0)
        return ret;

    size_t count = 0;

    ret += prev;

    for (s += 1;; ++s) {
        char thisChar = *s;

        if (prev != thisChar) {
            if (count > 0) {
                ret += std::to_string(count + 1);
                count = 0;
            }
            if (thisChar == 0)
                break;
            ret += thisChar;
        } else {
            ++count;
        }
        prev = thisChar;
    }
    return ret;
}

void DoItInPlace(char * s)
{
    if (!s)
        return;
    char prev = *s;

    if (prev == 0) // empty string
        return;

    size_t totalOffset = 0;
    size_t count = 0;

    for (s += 1;; ++s) {
        char thisChar = *s;

        if (prev != thisChar) {
            if (count > 0) {
                std::string numString = std::to_string(count + 1);
                size_t numStringOffset = totalOffset + count;
                size_t numStringSz = numString.size();
                std::strncpy(s - numStringOffset, numString.c_str(), numStringSz);
                totalOffset += count - numStringSz;
                count = 0;
            }
            if (totalOffset != 0)
                s[-totalOffset] = thisChar;
            if (thisChar == 0)
                break;
        } else {
            ++count;
        }
        prev = thisChar;
    }
}

void TestDoit()
{
    size_t i = 0;
    const char *input;
    for (; (input = TestCases[i]) != NULL; i += 2) {

        const char * output = TestCases[i + 1];
        std::string result = DoIt(input);
        if (result != output) {
            std::cout << "TEST FAILED at input: [" << input << "], expected: [" << output << "], got: [" << result << "]!" << std::endl;
            return;
        }
    }
    std::cout << "DoIt: Success!" << std::endl;
}

void TestDoItInPlace()
{
    size_t i = 0;
    const char *input;
    for (; (input = TestCases[i]) != NULL; i += 2) {

        std::string inputCopy = input;

        const char * output = TestCases[i + 1];
        DoItInPlace(&inputCopy[0]);

        if (std::strcmp(inputCopy.c_str(), output) != 0) {
            std::cout << "TEST FAILED at input: [" << input << "], expected: [" << output << "], got: [" << inputCopy << "]!" << std::endl;
            return;
        }
    }
    std::cout << "DoItInPlace: Success!" << std::endl;
}

int main() {
    TestDoit();
    TestDoItInPlace();
}

