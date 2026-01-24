**cravdata**  — dynamic URL & file brute‑forcing toolkit

cravdata is a Go tool for directory enumeration on URLs and offline analysis of files/hashes. Instead of relying solely on large static wordlists, cravdata dynamically generates candidates for path discovery and includes modules for processing and analyzing hashes/files. Built for authorized pentests, CTFs, and security labs — efficient, modular, and designed for responsible use.

---

## 📦 Installation

To install `forcepath`, you need to have [Go](https://go.dev/dl/) installed (version 1.16 or higher recommended).

Run the following command to install the tool:

```bash
go install github.com/redseverity/cravdata@latest

```

* Make sure your $GOPATH/bin is in your $PATH.

---

## 🔧 Subcommands Guide

### `url`

Defines the target URL to scan.

**Accepted formats:**

```
https://example.com/
http://example.com
```

---

## ⚙️ Flags Guide


### `--charset`

Specifies the set of characters used for generating directory names.

**supported characters (RFC 3986):**

```
a-z A-Z 0-9 - _ . ~ : / ? # [ ] @ ! $ & ' ( ) * + , ; =
```

* Duplicate characters are **automatically removed**.
* If omitted, the default charset is: `"abc"`

**Example:**

```bash
--charset "abbcc1232"  → becomes "abc123"
```

---

### `--min`

Sets the **minimum length** of generated directory names.
Default: `1`

### `--max`

Sets the **maximum length** of generated directory names.
Default: `3`

> The generator will start with the smallest combination (`min` length) and go up to the largest (`max` length).

---

### `--timeout`

Sets the timeout (in seconds) for each HTTP request.
Default: `2`

---

### `--delay`

Sets the delay (in milliseconds) between each HTTP request.  
Default: `0`

---