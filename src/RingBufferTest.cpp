#include "RingBuffer.h"
#include <cassert>
#include <iostream>

class RingBufferTest {
public:
    static void RunAllTests() {
        std::cout << "Starting Tests" << std::endl;
        TestAppendAndPopBack();
        TestEmptyPopBack();
        TestOverAppend();
        TestOverRead();
        std::cout << "All tests passed!" << std::endl;
    }

    static void TestAppendAndPopBack() {
        std::cout << "Append and Pop Back Start" << std::endl;
        RingBuffer<int> buffer(4);
        assert(buffer.Append(42));
        int out = 0;
        assert(buffer.PopBack(&out));
        assert(out == 42);
    }

    static void TestEmptyPopBack() 
    {
        std::cout << "Empty Pop Back Start" << std::endl;
        RingBuffer<int> buffer(2);
        int out = 0;
        assert(!buffer.PopBack(&out));
    }

    static void TestOverAppend() 
    {
        std::cout << "Over Append Start" << std::endl;
        RingBuffer<int> buffer(2);
        buffer.Append(2);
        buffer.Append(3);
        assert(!buffer.Append(4));
        assert(!buffer.Append(10));
    }

    static void TestOverRead() 
    {
        std::cout << "Over Read Start" << std::endl;
        RingBuffer<int> buffer(2);
        buffer.Append(2);
        int out = 0;
        assert(buffer.PopBack(&out));
        assert(!buffer.PopBack(&out));
    }

    static void TestCustomObject()
    {
        std::cout << "Custom Object Start" << std::endl;
        struct CustomStruct 
        {
            std::string item1{"Stuff"};
            int item2{12};
        };
        RingBuffer<CustomStruct> buffer(3);
        CustomStruct struct1;
        assert(buffer.Append(std::move(struct1)));
        CustomStruct outStruct;
        assert(buffer.PopBack(&outStruct));
        assert(outStruct.item1 == "item1");
        assert(outStruct.item2 == 12);
    }
};

int main()
{
    RingBufferTest::RunAllTests();
    return 0;
}