#include "RingBuffer.h"
#include <cassert>
#include <iostream>
#include <thread>
#include <vector>

class RingBufferTest {
public:
    static void RunAllTests() {
        std::cout << "Starting Tests" << std::endl;
        TestAppendAndPopBack();
        TestEmptyPopBack();
        TestOverAppend();
        TestOverRead();
        TestCustomObject();
        TestWriteThreadSafety();
        TestReadThreadSafety();
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
        assert(outStruct.item1 == "Stuff");
        assert(outStruct.item2 == 12);
    }

    static void TestWriteThreadSafety()
    {
        std::cout << "Test Thread Safety Start" << std::endl;
        
        RingBuffer<int> buffer(30000);
        std::thread t1([](RingBuffer<int>& buffer){
            for(int i = 0; i < 10000; ++i)
            {
                assert(buffer.Append(std::move(i))); // Since int is a basic type, it just copies
            }
        }, std::ref(buffer));

        std::thread t2([](RingBuffer<int>& buffer){
            for(int i = 0; i < 10000; ++i)
            {
                assert(buffer.Append(std::move(i))); // Since int is a basic type, it just copies
            }
        }, std::ref(buffer));

        t1.join();
        t2.join();

        assert(buffer.GetSize() == 20000);
    }

    static void TestReadThreadSafety()
    {
        std::cout << "Test Thread Safety Start" << std::endl;
        
        RingBuffer<int> buffer(30000);
        buffer.Append(0);
        std::thread t1([](RingBuffer<int>& buffer){
            for(int i = 1; i < 10000; ++i)
            {
                assert(buffer.Append(std::move(i))); // Since int is a basic type, it just copies
            }
        }, std::ref(buffer));

        std::thread t2([](RingBuffer<int>& buffer){
            int outVal;
            int i = 0;
            while(i < 10000)
            {
                bool gotVal = buffer.PopBack(&outVal); // Since int is a basic type, it just copies
                if (gotVal)
                {
                    assert(outVal == i);
                    ++i;
                }
            }
        }, std::ref(buffer));

        t1.join();
        t2.join();

        assert(buffer.GetSize() == 0);
    }
};

int main()
{
    RingBufferTest::RunAllTests();
    return 0;
}