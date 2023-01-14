# libmatrix

A small `C++` library for various Matrix computations.

# Build from source

### Requirements:

- [**CMake**](https://cmake.org/download/ "CMake download page")
- make
- g++/cpp compiler

> **NOTE: For Windows users you can use the [MinGW tools](https://www.mingw-w64.org/downloads/ "MinGW downloads page")**

### Building and compiling examples:

```bash
git clone https://github.com/ZOASR/Matrix_cpp
cd libmatrix-master
cd build
cmake .. && make install
```

> If you're using **MinGW run `cmake -G "MinGW Makefiles" .. && make install`**


- # Compared to other tools
	- **numpy**:
	```
		Time:  0.018767299999999987
	```
	- **MATLAB**:
	```
		Elapsed time is 0.480114 seconds.
	```
	- **libmatrix**:
	```
		Seconds           : 3
		Milliseconds      : 834
	```

	## Metodology used
	- Calculating the inverse of a 100×100 Matrix of random integers
	- numpy:
		``` python
			  import numpy as np
			  import timeit
			  start = timeit.default_timer()
			  mat = np.random.random((500, 500))
			  print(np.linalg.inv(mat))
			  stop = timeit.default_timer()
			  print('Time: ', stop - start)
		```
	- libmatrix:
		``` c++
			  #include "include/matrix.h"
			  #include <iostream>
			  int main()
			  {
			  	Matrix A(500, 500);
			  	A.fill_random_int(1, 100);
			  	A.inverse();
			  	return 0;
			  }
		```
		- MATLAB:

		``` MATLAB
			>> r = randi(100, 500);
			>> inverse = inv(r)
		```