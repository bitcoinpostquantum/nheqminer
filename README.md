# Build instructions:

### Dependencies:
  - Nvidia Cuda
  - Boost 1.62+
  - gcc/g++ 5

## Linux
### General instructions:
  - Install CUDA
    ````
    sudo apt-get purge nvidia-*
    sudo add-apt-repository ppa:graphics-drivers/ppa
    sudo apt-get update
    sudo apt install nvidia-cuda-toolkit
    sudo ubuntu-drivers autoinstall
    ````

  - install Boost 1.62
	````
	wget https://sourceforge.net/projects/boost/files/boost/1.62.0/boost_1_62_0.tar.gz
	tar xvfz boost_1_62_0.tar.gz
	cd boost_1_62_0
	./bootstrap.sh --prefix=/usr/
	./b2 --show-libraries
	sudo ./b2 --with-system --with-log --with-date_time --with-filesystem --with-thread install
	sudo ./b2 install
	````
  - After that open the terminal and run the following commands in your home folder:
	````
	sudo apt-get update 
	sudo apt-get install libsodium-dev
	sudo apt-get install cmake
	sudo apt-get install gcc-5 g++-5
	sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 60 --slave /usr/bin/g++ g++ /usr/bin/g++-5
	git clone https://github.com/bitcoinpostquantum/nheqminer
	cd nheqminer
	mkdir build && cd build
	cmake ..
	make -j $(nproc)
	````
	  
# Run instructions:

Parameters: 
	-h		Print this help and quit
	-l [location]	Stratum server:port
	-u [username]	Username (bpqaddress)
	-a [port]	Local API port (default: 0 = do not bind)
	-d [level]	Debug print level (0 = print all, 5 = fatal only, default: 2)
	-b [hashes] Run in benchmark mode (default: 200 iterations)

NVIDIA CUDA settings
	-ci		CUDA info
	-cd [devices]	Enable CUDA mining on spec. devices
	-cb [blocks]	Number of blocks
	-ct [tpb]	Number of threads per block
  
Example to mine on your CUDA GPUs with your own BPQ address, using 2 CUDA GPUs:
- mainnet:
        `nheqminer -l pool.mainnet.bitcoinpq.org:3857 -u BPQ_MAINNET_ADDRESS_HERE -cd 0 1`
- testnet:
        `nheqminer -l pool.testnet.bitcoinpq.org:3858 -u BPQ_TESTNET_ADDRESS_HERE -cd 0 1`

