zlib-raw-sync
==================
zlib sync written in C++ using NAN (Native Abstractions for Node.js)
Released in June, 2014.
Available in Node greater than 0.8

installation
----------------
$ npm install zlib-raw-sync

usage
-----------
```js
var zrs = require("zlib-raw-sync");
var buf = require("fs").readFileSync(some_deflated_file);
var inflated = zrs.inflate(buf); // inflated buffer
```

limitation
------------
currently, inflateRawSync() is the only function available.
In future, deflateRawSync() will be implemented.
Feel free to

1. contact me to urge implementation
2. fork this repository and implement deflateRawSync()
