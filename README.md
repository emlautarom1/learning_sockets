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
$ client <hostname> <port>
```

### Server
```bash
$ server <port>
```

---

### Notes

This project was built using `cygwin` on **Windows 10**. Linux users should check the `make` file in order to set the appropriate `include` path.
