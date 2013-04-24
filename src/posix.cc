#include <node.h>
#include <unistd.h>
#include <v8.h>

using namespace v8;

Handle<Value> Fork(const Arguments& args) {
  HandleScope scope;
  return scope.Close(Integer::New(fork()));
}

Handle<Value> Daemon(const Arguments& args) {
  HandleScope scope;
  return scope.Close(Integer::New(daemon(args[0]->IsTrue() ? 0 : -1,
                                         args[1]->IsTrue() ? 0 : -1)));
}

Handle<Value> Getpid(const Arguments& args) {
  HandleScope scope;
  return scope.Close(Integer::New(getpid()));
}

void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("fork"),
    FunctionTemplate::New(Fork)->GetFunction());
  exports->Set(String::NewSymbol("daemon"),
    FunctionTemplate::New(Daemon)->GetFunction());
  exports->Set(String::NewSymbol("getpid"),
    FunctionTemplate::New(Getpid)->GetFunction());
}

NODE_MODULE(posix, init)
