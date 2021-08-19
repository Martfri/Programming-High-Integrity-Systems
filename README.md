# Docker for FPGA Tools

This repository contains tools to create Docker containers for FPGA tools. It is derived from the fpga/docker repository.

[FPGA-docker on Github](https://github.com/halfmanhalftaco/fpga-docker)



## Tools

- Mentor Questa 2020.4
  questa:2020.4

- Intel Quartus 20.1.1 HLS (contains Mentor Questa 2020.4)
  quartus:20.1.1

## Prerequisites

- Running Docker Installation as non-root
    [Getting Started with docker](https://docs.docker.com/engine/install/)
    [Post-installation steps for Linux](https://docs.docker.com/engine/install/linux-postinstall/)
- Running local X11 server for graphic applications


## Installation

1. clone the git repository

2. copy the installation files for questa in the `/mentor_questa_2020.4_ultra/install/` directory (this file can't currently not be automatically downloaded)

3. run `make` in the top-level directory

4.	Optional: you can use the the `/scripts/local/create_local_sym_links.sh` script to create symbolic links in a choosen directory for the docker start scripts.

## Usage
### Use Docker to run Makefile

**Setup**

1. Copy the the `/example/docker.mk` in the directory of your Makefile.
2. Edit the `docker.mk` file
   - `TOOL` variable for the chosen Tool
   - `BUILD_TOP_PATH` relative path if your Makefile is not in the top level directory
   - `MAKEFILE` name of your Makefile
   - `LOAD_PATH` path to the docker start scripts



**Run the makefile**

```bash
make -f ./docker.mk [TARGET]
```

