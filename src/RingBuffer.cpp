#include "RingBuffer.h"

template<typename T>
RingBuffer<T>::RingBuffer(const std::uint32_t size) : m_totalIndexes(size)
{
    m_data = new T[size];
}

template<typename T>
RingBuffer<T>::~RingBuffer() 
{
    free(m_data);
}

template<typename T>
RingBuffer<T>::RingBuffer(RingBuffer&& other) 
{
    // TODO copy
}

template<typename T>
RingBuffer<T>& RingBuffer<T>::operator=(RingBuffer&& other) 
{ 
    // TODO move
    return *this; 
}

template<typename T>
bool RingBuffer<T>::Append(T& item) 
{
    if (m_writeIndex >= m_totalIndexes)
    {
        m_writeIndex.store(0);
    }
    if (m_writeIndex == m_readIndex)
    {
        return false;
    }
    std::uint32_t thisIndex = m_writeIndex.fetch_add(1);
    m_data[thisIndex] = item;
    return true;
}

template<typename T>
T* RingBuffer<T>::PopBack() 
{
    if (m_readIndex >= m_totalIndexes)
    {
        m_readIndex.store(0);
    }
    if (m_readIndex == m_writeIndex)
    {
        return nullptr;
    }
    std::uint32_t thisIndex = m_readIndex.fetch_add(1);
    return std::move(m_data[thisIndex]);
}

