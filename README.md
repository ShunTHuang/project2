# NS-3 Project: DiffServ Queueing Implementation

This project implements a custom DiffServ (Differentiated Services) queuing model for the ns-3 network simulator, including SPQ and DRR scheduling.

---

## 🔧 Step 1: Install ns-3

### ✅ Install Dependencies

```bash
sudo apt update
```

```bash
sudo apt install -y \
  gcc g++ python3 python3-pip \
  git mercurial cmake \
  qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools \
  pkg-config sqlite3 \
  python3-setuptools \
  gdb valgrind \
  curl
```

### ✅ Clone the ns-3 Repository

```bash
cd ~
```

```bash
git clone https://gitlab.com/nsnam/ns-3-dev.git
```

### ✅ Clone the Project2 Repository

```bash
cd ns-3-dev/src             # Move into ns-3 source directory
mkdir project2              # Create a new folder for your module
cd project2                 # Enter the project2 folder
git clone git@github.com:ShunTHuang/project2.git .
```