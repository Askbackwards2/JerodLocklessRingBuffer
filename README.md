# Lockless-Ring-Buffer

This is an in-progress Lockless Ring Buffer I'm making to be used in my OrderBook implementation.

# Design
This ring buffer will have a large chunck of pre-defined allocated memory that it will split into given x indices. An atomic read and write index will be used to point callers to their point in memory to read or write to. Memory will not auto grow in this implementation, and will give a failled bool on a failed read/write. 