# Lockless-Ring-Buffer

This is an in-progress Lockless Ring Buffer I'm making to be used in my OrderBook implementation.

# Design
This ring buffer will have a large chunck of pre-defined allocated memory that it will split into given x indices. An atomic read and write index will be used to point callers to their point in memory to read or write to. Memory will not auto grow in this implementation, and will give a failled bool on a failed read/write. 

# How To Use
Create the Ring Buffer by giving it a size. Note the size cannot be changed after initialization.
```
RingBuffer<int> intBuffer(10);
```

To add to the ringbuffer use the Append function.
```
RingBuffer<int> intBuffer(10);
intBuffer.Append(1);
```

To read from the ringbuffer use the PopBack function. PopBack removes the item from the RingBuffer.
```
RingBuffer<int> intBuffer(10);
intBuffer.Append(1);
int outVal = 0;
intBuffer.PopBack(&outVal);
// outVal now equals 1
```