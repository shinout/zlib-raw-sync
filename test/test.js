var zlib_raw_sync = require('../build/Release/zlib_raw_sync');

function run() {
  var defBuf = require("fs").readFileSync(__dirname + "/header");
  var delta = defBuf.readUInt16LE(16) + 1;
  var input = defBuf.slice(18, delta-8);
  var ret = zlib_raw_sync.inflateRawSync(input);
  console.log(ret.toString().length);
}

run()
