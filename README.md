# Object-oriented programming project
## User instructions
For running from the terminal:
g++ main.cpp FileGenerator.cpp Student.cpp TextReader.cpp UserInterface.cpp -o main \
And: 
./main

Afterward you will be promoted to choose a version you want to run, please follow the prompted instructions.

## V.02
### Speed Tests
Testing was done 3 times, best results shown below.

| File Size<br/>  |   1000    |   10000    |   100000    |   1000000    |   10000000    |
|-----------------|:---------:|:----------:|:-----------:|:------------:|:-------------:|
| Read Times      |   4 ms    |   162 ms   |   1511 ms   |   11007 ms   |   152517 ms   |
| Sort Times      |   1 ms    |    7 ms    |    80 ms    |    731 ms    |   12374 ms    |
| Write Times     |   17 ms   |   74 ms    |   599 ms    |   4803 ms    |   85196 ms    |
| **Total Times** | **22 ms** | **243 ms** | **2110 ms** | **16541 ms** | **250087 ms** |


## V.03
### Speed Tests
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


**Notes:**
* Comparing time results with other projects, it is obvious that my Threading system does not add extra performance. This could be because:
  * There are 4 Threads used in this experiment for reading and writing, however there may be to much overhead for such operations when using Threads, thus making the program slower.
  * There could be a difference of performance just because of hardware differences. Program may even run faster on same systems.

## V1.0
### Speed Tests in regard to approaches
**Approach 1:**
In approach 1 we sort our students into two list type objects, either StudentsOver5, or StudentsUnder5

| File Size<br/>  | 1000 | 10000 | 100000 | 1000000 | 10000000 |
|-----------------|:----:|:-----:|:------:|:-------:|:--------:|
| Vector          | 0 ms | 3 ms  | 35 ms  | 417 ms  | 7814 ms  |
| List            | 0 ms | 4 ms  | 54 ms  | 419 ms  | 8555 ms  |

**Approach 2:**
In approach 2 we sort our students into two list type objects, by finding all students whos average grade is < 5 and delete them in the previous list type object. 

| File Size<br/> | 1000 | 10000 | 100000 | 1000000 | 10000000 |
|----------------|:----:|:-----:|:------:|:-------:|:--------:|
| Vector         | 0 ms | 0 ms  |  5 ms  |  60 ms  | 3160 ms  |
| List           | 0 ms | 0 ms  |  9 ms  |  92 ms  | 4153 ms  |

### Results:
* It is evident that he second approach is more efficient, from which vector type lists have shown the best results. I have no idea how to further optimise approach 2, so approach 3 will be an optimised approach 1.
* Results consist of averaged times over 5 different runs.

**Approach 3:**
In approach 3 we create two list type object, inserting students into subsequent list if there average is over 5 or under 5. To do this I've used optimised list type object methods.

| File Size<br/> | 1000 | 10000 | 100000 | 1000000 | 10000000 |
|----------------|:----:|:-----:|:------:|:-------:|:--------:|
| Vector         | 0 ms | 0 ms  |  4 ms  |  69 ms  | 2282 ms  |
| List           | 0 ms | 1 ms  | 12 ms  | 189 ms  | 3596 ms  |

### Results:
* An optimised approach 1 showed better results than approach 2

# System parameters:
* Processor: 2.3GHz Dual-core Intel Core i5
* Memory: 8 GB 2133 MHz LPDDR3
* Storage: APPLE SSD AP0128J 121 GB