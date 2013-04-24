# Posix-Fork

`posix-fork` is a `node.js` module providing functionality of 2 UNIX system calls: `fork()` and `daemon()`.

In order to install do `npm install posix-fork`. After that `require('posix-fork')` will return you an object with 3 methods: `fork()`, `daemon()` and `getpid()`:

`getpid()` is for getting current process' id. It is needed because `process.pid` will refer to parent's PID after `fork()` or `daemon()`.

`fork()` creates a copy of the process you called it from (`man fork` for more). Both child and master will continue running the code below the invocation of `fork()`. However in master process the function returns child's PID and in child it returns `0`. The following example will spawn 100 child processes:

```javascript
    var posix = require('posix-fork'),
        childPid = true,
        children = 0

    for (var children = 0; childPid && children < 100; children++) {
      if (childPid = posix.fork()) // we're in master
        console.log('spawned one more child!')
      else                         // we're in child
        console.log('I am a child #%s', children)
    }
```

`daemon()` will fork and immediately exit from master process, thus detaching the program from the controlling terminal (or other process). It accepts two arguments: `chdir` and `close`. If `chdir` is trueish then `daemon()` will change process' working directory to `/`, otherwise working dir will be left unchanged. If `close` is trueish then standard input and standard output will be redirected to `/dev/null`, otherwise no changes will be made to these file descriptors. If `daemon()` succeeds it returns `0`, if an error occurs it returns `-1`. The code below `daemon()` function invocation will run in child only. Warning: `process.pid` will report incorrect process id after `daemon()`, so use `posix.getpid()`. Read `man daemon` for more.
