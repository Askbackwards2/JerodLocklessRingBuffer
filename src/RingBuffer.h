// Lockless Ring Buffer
// by Jerod D'Epifanio

#ifndef JEROD_RINGBUFFER_H
#define JEROD_RINGBUFFER_H

#include <atomic>
#include <cstdint>

template <typename T>
class RingBuffer
{
public:
    RingBuffer(const std::uint32_t size);
    ~RingBuffer();

    RingBuffer(const RingBuffer& other) = delete;   // Copy Constructor
    RingBuffer& operator=(const RingBuffer& other) = delete;    // Copy Assignment
    RingBuffer(RingBuffer&& other); // Move Constructor
    RingBuffer& operator=(RingBuffer&& other); // Move Assignment

    bool Append(T& item);
    T* PopBack();

private:


public:

private:
    T* m_data{nullptr};  // Chunk of contiguous memory
    std::atomic<std::uint32_t> m_readIndex{0};
    std::atomic<std::uint32_t> m_writeIndex{0};

    const std::uint32_t m_totalIndexes;
};

#endif