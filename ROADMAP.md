# plutonium-recursion Roadmap

> **An entire browser. Inside your browser.**

This roadmap outlines the planned development of **plutonium-recursion**.
The project is experimental and actively evolving, so features and priorities may change as development progresses.

---

## 🟢 Phase 1 — Foundation

The foundation required to run an independent browser environment inside a host browser.

* [x] Establish the plutonium-recursion project
* [x] C++ core
* [x] WebAssembly compilation
* [x] Browser UI foundation
* [ ] Establish the core browser architecture
* [ ] Implement the internal browser process model
* [ ] Implement internal networking
* [ ] Establish the internal rendering pipeline
* [ ] Establish communication between the C++ core and WebAssembly layer
* [ ] Improve initialization and startup performance

---

## 🔵 Phase 2 — Browser Core

Build the fundamental components required for plutonium-recursion to operate as a real browser.

* [ ] URL parsing
* [ ] URL navigation
* [ ] HTTP/HTTPS handling
* [ ] Request and response handling
* [ ] Redirect handling
* [ ] Cookie management
* [ ] Cache system
* [ ] History
* [ ] Bookmarks
* [ ] Download management
* [ ] Local storage
* [ ] Session storage
* [ ] Browser preferences
* [ ] Error pages

---

## 🟣 Phase 3 — Rendering Engine

Develop the components responsible for turning web content into something the user can actually see and interact with.

* [ ] HTML parsing
* [ ] DOM implementation
* [ ] CSS parsing
* [ ] CSS styling
* [ ] Layout engine
* [ ] Text rendering
* [ ] Image rendering
* [ ] SVG support
* [ ] Links and navigation
* [ ] Forms
* [ ] Input handling
* [ ] Scrolling
* [ ] Zoom
* [ ] Viewport management
* [ ] Web standards compatibility improvements

---

## 🟠 Phase 4 — JavaScript & Web APIs

Add the functionality required for modern websites.

* [ ] JavaScript execution environment
* [ ] DOM APIs
* [ ] Events
* [ ] Timers
* [ ] Fetch API
* [ ] XMLHttpRequest
* [ ] WebSockets
* [ ] Web Workers
* [ ] WebAssembly support within the internal browser
* [ ] IndexedDB
* [ ] Web Storage APIs
* [ ] Canvas
* [ ] WebGL
* [ ] Clipboard APIs
* [ ] Notifications
* [ ] Additional browser APIs

---

## 🔴 Phase 5 — Browser Features

Expand plutonium-recursion from a browser engine into a complete browser application.

* [ ] Multiple tabs
* [ ] Tab management
* [ ] New-tab page
* [ ] Address bar
* [ ] Back / forward navigation
* [ ] Reload / stop controls
* [ ] Page source viewer
* [ ] Developer tools
* [ ] Downloads page
* [ ] History page
* [ ] Bookmarks page
* [ ] Settings
* [ ] Private browsing mode
* [ ] Find in page
* [ ] Print support
* [ ] Keyboard shortcuts
* [ ] Custom browser themes

---

## 🟡 Phase 6 — Security & Isolation

Improve security while maintaining the project's ability to run inside a host browser.

* [ ] Origin isolation
* [ ] Same-origin policy
* [ ] Permission system
* [ ] Secure cookie handling
* [ ] Content security policies
* [ ] Sandboxing
* [ ] Certificate handling
* [ ] HTTPS security improvements
* [ ] Cross-origin request handling
* [ ] Storage isolation
* [ ] Internal security auditing

---

## 🟤 Phase 7 — Performance

Make plutonium-recursion fast enough to behave like a practical browser.

* [ ] Optimize WebAssembly execution
* [ ] Reduce startup time
* [ ] Improve page load performance
* [ ] Optimize rendering
* [ ] Optimize memory usage
* [ ] Improve caching
* [ ] Reduce unnecessary browser-host communication
* [ ] Improve JavaScript performance
* [ ] Improve large-page performance
* [ ] Benchmark against representative websites

---

## ⚪ Phase 8 — Recursive Browsing

One of the project's defining goals.

### Browser → Browser → Browser

* [ ] Run plutonium-recursion inside itself
* [ ] Test nested browser instances
* [ ] Improve nested-instance stability
* [ ] Optimize resource usage of nested instances
* [ ] Support multiple levels of recursion
* [ ] Investigate practical recursion limits

The ultimate experiment:

```text
Host Browser
    │
    └── plutonium-recursion
            │
            └── plutonium-recursion
                    │
                    └── plutonium-recursion
                            │
                            └── ...
```

---

## 🔵 Phase 9 — Compatibility

Increase compatibility with real-world websites.

* [ ] Establish a browser compatibility test suite
* [ ] Test popular websites
* [ ] Identify unsupported web standards
* [ ] Implement missing standards
* [ ] Improve CSS compatibility
* [ ] Improve JavaScript compatibility
* [ ] Improve API compatibility
* [ ] Improve media support
* [ ] Improve accessibility compatibility
* [ ] Track compatibility regressions

---

## 🟢 Phase 10 — Release

Prepare plutonium-recursion for stable public releases.

* [ ] Establish versioning system
* [ ] Establish release process
* [ ] Create automated builds
* [ ] Create automated tests
* [ ] Create documentation
* [ ] Create contribution guidelines
* [ ] Create issue templates
* [ ] Create security policy
* [ ] Create stable deployment
* [ ] Release first stable version

---

# Long-Term Vision

The ultimate goal of plutonium-recursion is not to create a browser-shaped webpage.

It is to create a **real, independently functioning browser environment that happens to run inside another browser.**

The ideal end state is:

```text
┌─────────────────────────────────────────────┐
│                  Host Browser               │
│                                             │
│   ┌─────────────────────────────────────┐   │
│   │          plutonium-recursion        │   │
│   │                                     │   │
│   │   ┌─────────────────────────────┐   │   │
│   │   │      Browser Engine         │   │   │
│   │   │                             │   │   │
│   │   │   HTML / CSS / JS / APIs    │   │   │
│   │   │   Networking / Storage      │   │   │
│   │   │   Rendering / Navigation    │   │   │
│   │   │                             │   │   │
│   │   └─────────────────────────────┘   │   │
│   │                                     │   │
│   └─────────────────────────────────────┘   │
│                                             │
└─────────────────────────────────────────────┘
```

**The host browser provides the environment.
plutonium-recursion provides the browser.**

---

## Roadmap Status

This roadmap is a living document.

Items may be added, removed, reorganized, or changed as the architecture and goals of plutonium-recursion evolve.

**Last updated:** 2026
