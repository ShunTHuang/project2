# Project 2 – DRR and SPQ Queue in ns-3

This project implements two Quality of Service (QoS) scheduling mechanisms in ns-3:

- **Deficit Round Robin (DRR)**
- **Strict Priority Queueing (SPQ)**

---

## 👨‍💻 Developer

Developed by Koichi Nakata, Shing-Han Huang, Shun-Ting Huang

## 🔹 Operating System
This project has been tested on:

    Ubuntu 22.04.4 LTS (Jammy Jellyfish)

To check your OS version, run:

    cat /etc/os-release

## 🔹 Required Software
Ensure the following software is installed:

------------------------------------------------------------------------------------
| Software     | Version    | Installation Command           | Check Command       |
|--------------|------------|--------------------------------|---------------------|
| GCC          | 11.4.0     | sudo apt install gcc           | gcc --version       |
| Make         | Latest     | sudo apt install make          | make --version      |
------------------------------------------------------------------------------------

## 🛠 Install

- Follow the [ns-3 guide](https://www.nsnam.org/docs/installation/html/quick-start.html#download) to install ns-3.
  Make sure to run:
    ```bash
    ./ns3 configure --enable-examples --enable-tests
    ./ns3 build
    ```

- Install nlohmann-json
    ```bash
    sudo apt update
    sudo apt install nlohmann-json-dev
    ```

## 📁 Setup

1. **Place the project directory**

   Copy the `project2` folder into your ns-3 source tree under `src/`:

    ```bash
    mv project2 /ns-3-dev/src/
    ```

2. **Navigate to the ns-3 root directory**

    ```bash
    cd /ns-3-dev
    ```

---

## ▶️ Run the simulation

- To run the **DRR simulation**:

    ```bash
    ./ns3 run DrrSimulation -- src/project2/DrrConfig.json
    ```

- To run the **SPQ simulation**:

    ```bash
    ./ns3 run SpqSimulation -- src/project2/SpqConfig.json
    ```

> ⚠️ Make sure the config files exist and are valid JSON format.  
> The `--` is required to pass arguments to the simulation's `main(argc, argv)`.

---

## 📂 Config Files

The config files define the queue behavior and classification rules:

- `DrrConfig.json` – DRR class definitions, filters, and quantum values.
- `SpqConfig.json` – SPQ class definitions, filters, and priority mapping.


---

## 🧪 Output

- `.pcap` trace files are generated in the `ns-3-dev/` directory.
- Files are prefixed with `Pre_` and `Post_`.
  For example: `Pre_DRR`, `Post_DRR`, `Pre_SPQ`, `Post_SPQ`.
- You can analyze them using tools like Wireshark.