# A simple base64 convert c++ library
This is a base64 convert library writting in c++.

## How to use
Add "base64.h" to your include list
```
#include "base64.h"
```
Create a base64 converter object
```
b64::base64_codec _codec;
```
Convert buffer to string
```
std::string _buff_str = "hello string buffer";
std::string _base64_str = _codec.encode(_buff_str, _buff_str.size());
```
Convert base64 string back to buffer.
Use function decode with a base64 string will returns a buff object, this is a pair object with a smart pointer(buff.first) and size(buff.second)
```
auto _buff = _codec.decode(_base64_str);
```

## Problems?
Drop an email to mattxlee@gmail.com

## Build test and run
To build test project, please according the following lines in bash
```
mkdir build
cd build
cmake ..
make
```
To run test program
```
./base64_test
```
