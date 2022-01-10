# KVPStorage

KVPStorage is used for persistently storing and retrieving key-value pairs, most commonly used to store settings. 

## Compilation

Run make to create the binary. 

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
$ cd src
$ ./KVPStorage
$ cd ../tst
$ ./KVPStorage_tst # To test and see results
```

## Usage

SET		[KEY] [VALUE]

- SET command requires a key.

GET		[KEY] 

- GET command requires a key. Any other input after the first key throws an exception.

DELETE	[KEY]

- DELETE command requires a key. Any other input after the first key throws an exception.

Example usage is given below:
```bash
$ ./KVPStorage
> SET DeviceName TestDevice_123
OK
> GET DeviceName
TestDevice_123
> DELETE DeviceName
OK
> GET DeviceName

>
```

## Used third-part tools
This project is built, tested, and documented using some third-party tools and services listed below. I would like to thank them.

- [Buildroot](https://github.com/buildroot/buildroot): Buildroot is a simple, efficient and easy-to-use tool to generate embedded
  Linux systems through cross-compilation.
- [Nlohman-Json](https://github.com/nlohmann/json): JSON for Modern C++ 

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
MIT License

Copyright (c) [2022] [Ege ENGIN]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
