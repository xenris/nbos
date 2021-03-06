[Index](../index.hpp.md#index)

# Random

## Example

```c++
nblib::Random random;

int i = random.next<int>();
float f = random.next<float>();
```

## class Random

#### Random()
Constructor with seed defaulting to 0.

#### Random(uint32_t seed)
Constructor with user defined seed.

#### T next<class T>()
Get the next random value.<br>
Floating point between 0 and 1 inclusive.<br>
Other types between 0 and 32768 inclusive.<br>
Algorithm based on the POSIX.1-2001 example.
