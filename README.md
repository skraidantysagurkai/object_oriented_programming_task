# Object-oriented programming project
## Context





## Speed Tests
**Vector speed tests:**

| File Size<br/>  |   1000    |   10000    |   100000    |   1000000    |   10000000    |
|-----------------|:---------:|:----------:|:-----------:|:------------:|:-------------:|
| Read Times      |   4 ms    |   162 ms   |   1511 ms   |   11007 ms   |   152517 ms   |
| Sort Times      |   1 ms    |    7 ms    |    80 ms    |    731 ms    |   12374 ms    |
| Write Times     |   17 ms   |   74 ms    |   599 ms    |   4803 ms    |   85196 ms    |
| **Total Times** | **22 ms** | **243 ms** | **2110 ms** | **16541 ms** | **250087 ms** |

**List speed tests:**

| File Size<br/>  |    1000    |   10000    |   100000    |   1000000    |   10000000    |
|-----------------|:----------:|:----------:|:-----------:|:------------:|:-------------:|
| Read Times      |   19 ms    |   159 ms   |   1477 ms   |   11988 ms   |   153359 ms   |
| Sort Times      |    0 ms    |    6 ms    |   106 ms    |    695 ms    |   13972 ms    |
| Write Times     |   237 ms   |   79 ms    |   800 ms    |   6021 ms    |   58267 ms    |
| **Total Times** | **256 ms** | **244 ms** | **2383 ms** | **18704 ms** | **225598 ms** |

# System parameters:
* Processor: 2.3GHz Dual-core Intel Core i5
* Memory: 8 GB 2133 MHz LPDDR3
* Storage: APPLE SSD AP0128J 121 GB

**Notes:**
* Comparing time results with other projects, it is obvious that my Threading system does not add extra performance. This could be because:
  * There are 4 Threads used in this experiment for reading and writing, however there may be to much overhead for such operations when using Threads, thus making the program slower.
  * There could be a difference of performance just because of hardware differences. Program may even run faster on same systems.