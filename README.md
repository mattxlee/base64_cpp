# A simple base64 convert c++ library [![Build Status](https://travis-ci.org/mattxlee/base64_cpp.svg?branch=master)](https://travis-ci.org/mattxlee/base64_cpp)
This is a base64 convert library writting in c++.

## How to use
Add `<base64_cpp/base64.h>` to your include list
```
#include <base64_cpp/base64.h>
```
Convert buffer to string
```
std::string _buff_str = "hello string buffer";
std::string _base64_str = base64::Encode(_buff_str, _buff_str.size());
```
Convert base64 string back to buffer.
Use function decode with a base64 string will returns a buff object, this is a pair object with a smart pointer(buff.first) and size(buff.second)
```
auto _buff = base64::Decode(_base64_str);
```

## Build test and run
To build test project, please according the following lines in bash
```
cmake . && make
```

## Install library
Library will be installed to `/usr/local/include/base64_cpp/`
```
cmake . && make && make install
```

## Run test
To run test program
```
./base64_test
```

## Problems?
Drop an email to mattxlee@gmail.com.
