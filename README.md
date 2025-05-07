# QoS Project: DRR and SPQ Queue in ns-3

This project implements two Quality of Service (QoS) mechanisms in ns-3:

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
    sudo apt install nlohmann-json3-dev
    ```

## 📁 Setup

1. **Place the project directory**

   Copy the `project2` folder into your ns-3 source tree under `src/`

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

- Or to use CLI script and then run (Extra credit):

    ```bash
    ./ns3 run SpqSimulation -- src/project2/CLIConfig.txt
    ```
  
    > ⚠️ Make sure the config files exist and are valid JSON format.  
    
    > ⚠️ The `--` is required to pass arguments to the simulation's `main(argc, argv)`.

    > ⚠️ The port numbers used in the ns-3 simulation differ from those on the Catalyst 3750 switch.

  - **In ns-3 simulation**:
      - High-priority traffic: UDP port `50000`
      - Low-priority  traffic: UDP port `50001`

  - **On the Catalyst 3750 switch**:
      - High-priority traffic: UDP port `50001`
      - Low-priority  traffic : UDP port `50002`
---

## 📂 Config Files

The config files define the queue behavior and classification rules:

- `DrrConfig.json` – DRR class definitions, filters, and quantum values.
- `SpqConfig.json` – SPQ class definitions, filters, and priority mapping.
- `CLIConfig.txt` – The same functionalities as `SpqConfig.json` but can be applied to CISCO Catalyst Switch 3750. 


---

## 🧪 Output

- `.pcap` trace files are generated in the `ns-3-dev/` directory.
- Files are prefixed with `Pre_` and `Post_`.
  For example: `Pre_DRR`, `Post_DRR`, `Pre_SPQ`, `Post_SPQ`.
- You can analyze them using Wireshark. To generate effective charts, please add the following filtering rules to the I/O chart:
  - DRR simulation:
    - udp.dstport == 50001
    - udp.dstport == 50002
    - udp.dstport == 50003

  - SPQ simulation configured by SpqConfig.json:
    - udp.dstport == 50000
    - udp.dstport == 50001

  - SPQ simulation configured by CLIConfig.txt:
    - udp.dstport == 50001
    - udp.dstport == 50002