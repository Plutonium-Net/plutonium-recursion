# plutonium-recursion

> **An entire browser. Inside your browser.**

**plutonium-recursion** is a fully self-contained web browser compiled to **C++/WebAssembly** and running entirely inside another web browser.

It isn't a browser-themed webpage.

It isn't simply an iframe.

It isn't a frontend for the host browser.

**It's a browser running inside a browser.**

The goal of plutonium-recursion is to bring the functionality of a standalone browser into an environment where the only thing you need to launch it is another browser.

---

## 🧠 What Is plutonium-recursion?

Normally, when you open a website, your browser handles everything:

```text
Website
   ↓
Your Browser
   ↓
Operating System
```

plutonium-recursion flips that idea around:

```text
┌──────────────────────────────────────────────┐
│              Your Browser                    │
│                                              │
│   ┌──────────────────────────────────────┐   │
│   │         plutonium-recursion          │   │
│   │                                      │   │
│   │   ┌──────────────────────────────┐   │   │
│   │   │      Browser Engine          │   │   │
│   │   │                              │   │   │
│   │   │      Web Pages               │   │   │
│   │   │      Navigation              │   │   │
│   │   │      Browser Features        │   │   │
│   │   │                              │   │   │
│   │   └──────────────────────────────┘   │   │
│   │                                      │   │
│   └──────────────────────────────────────┘   │
│                                              │
└──────────────────────────────────────────────┘
```

The host browser provides the environment in which plutonium-recursion executes, while plutonium-recursion provides the browser itself.

In other words:

**Browser → Browser → Web**

---

## 🚀 Features

plutonium-recursion aims to provide the functionality you'd expect from a standalone browser, while running entirely within a browser.

### 🌐 Full Browser Environment

Rather than simulating a browser interface, plutonium-recursion is designed to function as an actual browser environment.

### ⚙️ C++ / WebAssembly

The core of the project is written in **C++** and compiled to **WebAssembly**, allowing the browser to execute native-style code directly within the web environment.

### 🖥️ Runs Inside the Browser

No native executable is required to launch the web version.

Open the application in a supported browser and plutonium-recursion runs inside it.

### 🔒 Independent Browser Stack

plutonium-recursion is designed to operate independently from the host browser's normal browsing interface and functionality.

The host browser is the container.

**plutonium-recursion is the browser inside it.**

### 🔄 Recursive Potential

And yes...

You can potentially run a browser inside plutonium-recursion.

Which means:

```text
Browser
  └── plutonium-recursion
        └── Browser
              └── plutonium-recursion
                    └── ...
```

Hence the name.

---

## 🛠️ Technology

plutonium-recursion is primarily built using:

| Technology      | Purpose                                              |
| --------------- | ---------------------------------------------------- |
| **C++**         | Core browser implementation                          |
| **WebAssembly** | Executes the C++ browser inside the web environment  |
| **HTML**        | Application structure                                |
| **CSS**         | User interface                                       |
| **JavaScript**  | WebAssembly integration and browser-side integration |

The project is designed around the idea that a complete browser environment can be brought into the web through WebAssembly.

---

## 📦 Running plutonium-recursion

### Requirements

To run the web version, you need:

* A modern web browser
* JavaScript enabled
* WebAssembly support

No native installation is required for the web version.

### From Source

Clone the repository:

```bash
git clone https://github.com/Plutonium-Net/plutonium-recursion.git
cd plutonium-recursion
```

Build the project using the provided build configuration and WebAssembly toolchain.

Once built, serve the resulting files through a web server.

For example:

```bash
python3 -m http.server
```

Then open the local address in your browser.

> Build instructions are currently evolving as the project develops.

---

## 🚧 Development Status

**plutonium-recursion is currently under active development.**

The project is experimental, and functionality may change significantly between versions.

Some browser features may not yet be implemented or may behave differently from a traditional standalone browser.

---

## 🗺️ Goals

The long-term goal of plutonium-recursion is simple:

> **Make a complete browser capable of running inside another browser.**

Development focuses on improving:

* Browser compatibility
* Rendering capabilities
* Navigation
* Web standards support
* Performance
* WebAssembly integration
* Browser APIs
* Stability
* Overall standalone-browser functionality

---

## 🚗 Roadmap

The official roadmap for the 2026 year is located at ['Roadmap'](ROADMAP.MD)

## 🤝 Contributing

Contributions, bug reports, suggestions, and improvements are welcome.

Before contributing, please review the project's license and ensure that any third-party code or assets introduced into the project retain their required attribution and licensing information.

If you distribute a modified version of plutonium-recursion, you must also follow the modified-version requirements specified in the license.

---

## 👥 Developers

### Plutonium-Net

The organization behind plutonium-recursion.

### xXmizzeryXx

Original developer and contributor.

### Craf1ed

Original developer and contributor.

---

## 📜 License

plutonium-recursion is licensed under the **Plutonium Recursion License (PRL) v1.0**.

The license permits non-commercial use, modification, forking, and redistribution subject to its terms.

Commercial use, selling the Software, and incorporating substantial portions of the Software into other projects are prohibited.

Redistributions and derivative versions must provide appropriate attribution to:

* **Plutonium-Net**
* **xXmizzeryXx**
* **Craf1ed**

Third-party assets must retain their applicable attribution and licensing information.

See [`LICENSE`](LICENSE) for the complete terms.

---

<div align="center">

**plutonium-recursion**

   *An entire browser. Inside your browser.*

</div>
