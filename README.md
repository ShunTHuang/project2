# NS-3 Project: DiffServ Queueing Implementation

This project implements a custom DiffServ (Differentiated Services) queuing model for the ns-3 network simulator, including SPQ and DRR scheduling.

---

## 🔧 Install ns-3

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

## 🧑‍💻 Contributing

### ✅ Create a new branch
```bash
git checkout -b feature/your-feature-name
```

### ✅ Commit and push your changes
```bash
git add .
git commit -m "Add: your message"
git push origin feature/your-feature
```

### ✅ Open a Pull Request (PR) to main or dev branch
Open GitHub web → You will see
👉 “Compare & pull request”

### 📌 Guidelines

- **Do not commit directly to `main`**  
  Use feature branches and open a Pull Request (PR) instead.

- **Keep PRs small and focused**  
  One feature or bugfix per PR is preferred.

- **Follow naming conventions and file structure**  
  Use consistent file casing and module placement.