// Lockless Ring Buffer
// by Jerod D'Epifanio

#ifndef JEROD_RINGBUFFER_H
#define JEROD_RINGBUFFER_H

#include <atomic>
#include <cstdint>

class RingBuffer
{
public:
    RingBuffer();
    ~RingBuffer();

    RingBuffer(const RingBuffer& other) = delete;   // Copy Constructor
    RingBuffer& operator=(const RingBuffer& other) = delete;    // Copy Assignment
    RingBuffer(RingBuffer&& other); // Move Constructor
    RingBuffer& operator=(RingBuffer&& other); // Move Assignment

    void Append();
    void PopBack();

private:


public:

private:
    void* m_data{nullptr};  // Chunck of contiguous memory
    std::atomic<std::uint32_t> m_readIndex{0};
    std::atomic<std::uint32_t> m_writeIndex{0};

    std::uint32_t m_totalIndexes{0};
    std::uint32_t m_chunkSize{0};
};

#endif