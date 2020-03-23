# Learning Sockets

Create sockets, send and receive data.

![Sockets](program.png)

## How to build

### Requirements
- GNU Make
- GNU GCC

```bash
$ make [all | client | server | clean]
```
> Note: `$ make` defaults to `$ make all`

## How to run

### Client
```bash
$ ./build/client <hostname> <port>
```

### Server
```bash
$ ./build/server <port>
```

---

### Notes

This project was built using `cygwin` on **Windows 10**, but it should work on Linux as long as you fulfill the requirements.
