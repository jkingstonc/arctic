# ❄️ arctic
Arctic is a POSIX compliant micro-kernel currently targeting the x86 architecture
</br></br>
## 🔨 Building
---
### Requirements
- Make
- Qemu
- Cross-Compiler toolchain

### Commands

Arctic uses Make as it's build system, the following commands can be used to build/run Arctic

| Action                            | Command                 |
| --------------------------------- | ----------------------- |
| Build                             | ```make all```          |
| Build & Run in VGA text mode      | ```make run-text```     |
| Build & Run in VBE graphics mode  | ```make run-graphics``` |

You are also required to specify the path to the various tools to get Arctic up and running!

| Paramater                         | Command                            |
| --------------------------------- | ---------------------------------- |
| Qemu path (required)              | ```make QEMU='path/to/qemu'```     |
| C++ compiler (required)           | ```make CC='path/to/c++'```        |
| Linker (required)                 | ```make LD='path/to/linker'```     |
| Linker (required)                 | ```make ASM='path/to/assembler'``` |

</br></br>
## 🤝 Contributing
---
Contributing is most welcome! We currently accept pull-requests