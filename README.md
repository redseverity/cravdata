# cravdata

**cravdata** — CPU‑bound brute‑force & cryptographic analysis toolkit

The project is now focused on **CPU‑intensive brute‑force operations**, targeting:

* Hash analysis and cracking
* Password‑protected files
* Cryptographic keyspace exploration
* Offline security research scenarios

Unlike traditional tools that rely purely on static wordlists, cravdata emphasizes **dynamic candidate generation** and deterministic keyspace traversal optimized for CPU performance.

Built for authorized pentests, CTFs, and security labs — modular, efficient, and designed for responsible use.

---

## 🛠 Build & Run

The project uses a `Makefile` for compilation and execution.

### Build

```bash
make build
```

### Start

```bash
make start
```

### Clean

```bash
make clean
```

The compiled binary is generated at:

```
build/cravdata
```

You may also run it directly:

```bash
./build/cravdata
```

---

## 🔧 Scope

cravdata is designed for:

* Offline brute‑force research
* Hash verification workflows
* Controlled cryptographic experiments
* Security lab environments

It is not intended for network‑bound directory enumeration anymore.
The focus is now purely computational.

---

> This tool must only be used in authorized environments.
> Unauthorized usage against third‑party systems is illegal.

---
