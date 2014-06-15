#include <node.h>
#include <nan.h>

#include <zlib.h>
#include <cstring>
#include <cstdlib>
NAN_METHOD(InflateRawSync);


using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Local;
using node::Buffer;

#define ERR(msg) v8::ThrowException(v8::Exception::Error(String::New(msg)));


// function to export
NAN_METHOD(InflateRawSync) {
  NanScope();

  if(args.Length() < 1 || !Buffer::HasInstance(args[0])) {
    return ERR("argument must be a Buffer object")
  }
  Local<Object> input = args[0]->ToObject();
  Bytef* in_buf = (Bytef*)Buffer::Data(input);
  int in_len    = Buffer::Length(input);

  z_stream strm;
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = 0;
  strm.next_in = Z_NULL;
  int ret = inflateInit2(&strm, -15);
  if (ret != Z_OK)
    return ERR("could not initialize the data");

  const int delta = 2 * in_len;
  strm.avail_in = in_len;
  strm.next_in = in_buf;

  int inflated_len = 0;
  Bytef* inflated_buf = NULL;
  do {
    inflated_buf = (Bytef*)realloc(inflated_buf, inflated_len + delta);
    strm.avail_out = delta;
    strm.next_out = inflated_buf + inflated_len;
    ret = inflate(&strm, Z_NO_FLUSH);
    if (ret != Z_BUF_ERROR && ret != Z_STREAM_END && ret != Z_OK) {
      free(inflated_buf);
      return ERR("Invalid format");
    }

    inflated_len += delta - strm.avail_out;
  } while (strm.avail_out == 0);

  (void)inflateEnd(&strm);

  Buffer* buf = Buffer::New((const char*)inflated_buf, inflated_len);
  free(inflated_buf);

  NanReturnValue(NanNew<Object>(buf->handle_));
}

// exposing
void InitAll(Handle<Object> exports) {
  exports->Set(NanNew<String>("inflateRawSync"),
    NanNew<FunctionTemplate>(InflateRawSync)->GetFunction());
}

NODE_MODULE(zlib_raw_sync, InitAll)
