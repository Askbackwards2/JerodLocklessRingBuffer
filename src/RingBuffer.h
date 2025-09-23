// Lockless Ring Buffer
// by Jerod D'Epifanio

#ifndef JEROD_RINGBUFFER_H
#define JEROD_RINGBUFFER_H

#include <atomic>
#include <cstdint>
#include <string>
#include <sstream>

template <typename T>
class RingBuffer
{
public:

    RingBuffer(const RingBuffer& other) = delete;   // Copy Constructor
    RingBuffer& operator=(const RingBuffer& other) = delete;    // Copy Assignment

private:
    T* m_data{nullptr};  // Chunk of contiguous memory
    std::atomic<std::uint32_t> m_readIndex{0};
    std::atomic<std::uint32_t> m_writeIndex{0};

    const std::uint32_t m_totalIndexes;

// Template member function definitions
public:
    RingBuffer(const std::uint32_t size) : m_totalIndexes(size)
    {
        m_data = new T[size];
    }

    ~RingBuffer()
    {
        delete[] m_data;
    }

    RingBuffer(RingBuffer<T>&& other)
    {
        // TODO: move constructor implementation
    }

    RingBuffer<T>& operator=(RingBuffer<T>&& other)
    {
        // TODO: move assignment implementation
        return *this;
    }

    bool Append(T&& item)
    {
        if (m_writeIndex >= m_totalIndexes)
        {
            m_writeIndex.store(0);
        }
        if (m_writeIndex == (m_readIndex == 0 ? m_totalIndexes-1 : m_readIndex-1))
        {
            return false;
        }
        std::uint32_t thisIndex = m_writeIndex.fetch_add(1);
        m_data[thisIndex] = item;
        return true;
    }

    bool PopBack(T* outVal)
    {
        if (!outVal)
        {
            printf("Invalid outValue given to RingBuffer");
            return false;
        }
        if (m_readIndex >= m_totalIndexes)
        {
            m_readIndex.store(0);
        }
        if (m_readIndex == m_writeIndex)
        {
            return false;
        }
        std::uint32_t thisIndex = m_readIndex.fetch_add(1);
        *outVal = m_data[thisIndex];
        return true;
    }

    std::size_t GetSize()
    {
        std::size_t size = m_writeIndex - m_readIndex;
        if (size < 0)
        {
            size = m_totalIndexes - size;
        }
        return size;
    }

    std::string GetStateString()
    {
        std::stringstream ss;
        ss << "Read Index: " << m_readIndex.load() << std::endl;
        ss << "Write Index: " << m_writeIndex.load() << std::endl;
        ss << "Total Indices: " << m_totalIndexes << std::endl;
        return ss.str();
    }
};

#endif