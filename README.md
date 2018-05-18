# Build instructions:

### Dependencies:
  - Boost 1.62+
  - NVidia Cuda


## Linux

### Install Boost

```bash
  wget -O boost_1_60_0.tar.gz https://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz/download
  tar xvfz boost_1_60_0.tar.gz
  cd boost_1_60_0
  ./bootstrap.sh --prefix=/usr/
  ./b2 --show-libraries
  sudo ./b2 --with-system --with-log --with-date_time --with-filesystem --with-thread install
  sudo ./b2 install
```

### Ubuntu 14.04
- Install packages libsodium, cmake3, gcc-5
```bash
  sudo apt-get remove cmake
  sudo apt-get update
  sudo apt-get upgrade
  sudo apt-get install cmake3
  sudo apt-get install software-properties-common
  sudo add-apt-repository ppa:ubuntu-toolchain-r/test
  sudo apt-get update
  sudo apt-get install gcc-5 g++-5
  sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 60 --slave /usr/bin/g++ g++ /usr/bin/g++-5
  sudo add-apt-repository ppa:chris-lea/libsodium
  sudo nano /etc/apt/sources.list
```

- Add end of file lines
```bash
  deb http://ppa.launchpad.net/chris-lea/libsodium/ubuntu trusty main
  deb-src http://ppa.launchpad.net/chris-lea/libsodium/ubuntu trusty main
```
## Compile
```bash
  sudo apt-get update && sudo apt-get install libsodium-dev
  git clone https://bitbucket.org/kfginternational/nheqminer.git
  cd nheqminer && mkdir .build && cd .build
  cmake ..
  make
```

### NVIDIA CUDA
  First disable the Nouveau kernel driver by creating a new file:  
```bash
    sudo nano /etc/modprobe.d/blacklist-nouveau.conf
```    
  Add the following lines and then save and exit:
```bash
    blacklist nouveau
    blacklist lbm-nouveau
    options nouveau modeset=0
    alias nouveau off
    alias lbm-nouveau off
```

  Next let's update the initial RAM filesystem and reboot the machine:

```bash
  echo options nouveau modeset=0 | sudo tee -a /etc/modprobe.d/nouveau-kms.conf
  sudo update-initramfs -u
  sudo reboot
  sudo service lightdm stop
```
####  Install Nvidia CUDA
```bash
  sudo apt-get purge nvidia-*
  sudo add-apt-repository ppa:graphics-drivers/ppa
  sudo apt-get update
  sudo apt install nvidia-396
  sudo apt install nvidia-cuda-toolkit
```

## Run instructions:

Parameters: 
```
	-h		Print this help and quit
	-l [location]	Stratum server:port
	-u [username]	Username (Bitcoin Post-Quantum address)
	-a [port]	Local API port (default: 0 = do not bind)
	-d [level]	Debug print level (0 = print all, 5 = fatal only, default: 2)
	-b [hashes]	Run in benchmark mode (default: 200 iterations)
```

NVIDIA CUDA settings
```
	-ci		CUDA info
	-cd [devices]	Enable CUDA mining on spec. devices
	-cb [blocks]	Number of blocks
	-ct [tpb]	Number of threads per block
```  
Example: -cd 0 2 -cb 12 16 -ct 64 128

If run without parameters, miner will start mining with 75% of available logical CPU cores. Use parameter -h to learn about available parameters:

Example to mine on your CUDA GPUs with your own BTC address and worker1, using 2 CUDA GPUs:

```bash
  nheqminer -cd 0 1 -l pool.bitcoinpq.org:3358 -u YOUR_BTC_ADDRESS_HERE
```        

