# Ring Buffer

## Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Usage](#usage)
- [Contributing](../CONTRIBUTING.md)

## About <a name = "about"></a>

Ring buffer in c.

## Getting Started <a name = "getting_started"></a>
Download the 'RingBuffer.h' and include it to your project.



### Prerequisites

What things you need to install the software and how to install them.

```
Give examples
```

### Installing

Include the 'RingBuffer.h' file to your project and define a RingBuffer_Handler_t object.
After that, initialize the RingBuffer, and now your ring buffer is ready. 
You are able to use it.

Definition of the ring buffer :
```
RingBuffer_Handler_t myRingBuffer;
```

Initialization of the ring buffer:
```
RingBuffer_init(&myRingBuffer);
```

## Usage <a name = "usage"></a>

If you want to insert a new data your ring buffer. Like this:

```
RingBuffer_insert(&myRingBuffer, yourData);
```

If you want to remove a new data your ring buffer. Like this:

```
RingBuffer_remove(&myRingBuffer);
```

You can also use it with the locking mechanism. Like this:

```
if (RingBuffer_getCount(&myRingBuffer) <= BUFFER_SIZE){
    RingBuffer_insert(&myRingBuffer, yourData);
}
```

Also, Like this:
```
if (RingBuffer_isEmpty(&myRingBuffer) == 1){
    RingBuffer_remove(&myRingBuffer);
}
```