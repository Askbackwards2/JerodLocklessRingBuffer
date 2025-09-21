#include <iostream>
#include "RingBuffer.h"

int main() {
    std::cout << "Creating Ringbuffer..." << std::endl;
    RingBuffer<int> rBuffer(10);

    std::cout << "Adding..." << std::endl;
    rBuffer.Append(1);

    std::cout << "Reading..." << std::endl;
    int outValue;
    auto returnVal = rBuffer.PopBack(&outValue);

    std::cout << rBuffer.GetStateString() << std::endl;
    return 0;
}
