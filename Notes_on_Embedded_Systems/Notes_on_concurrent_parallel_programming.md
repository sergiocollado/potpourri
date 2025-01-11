# Notes on concurrent/parallel programming

related reference: [Stanford CS149 I Parallel Computing I 2023](https://www.youtube.com/watch?v=V1tINV2-9p4&list=PLoROMvodv4rMp7MTFr4hQsDEcX7Bx6Odp)

### Paralell programming in C++

There are 4 elements needed: 

References:
- https://cplusplus.com/reference/multithreading/
- https://www.cs.cmu.edu/afs/cs/academic/class/15210-f17/www/pasl.html

```c++
std::thread /join/detach
std::mutex  /lock/try_lock/unlock
std::atomic /atomic_thread_fence/memory_order_acquire/memory_order_release
std::future /std::promise/std::async(wait/get)
```

## Retrieve system GPU info

In linux: `lspci | grep -i --color 'vga|/3d|/2d'`

## Nvidia programming resources

 - https://developer.nvidia.com/

