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
    sudo apt install nvidia-396
    sudo apt install nvidia-cuda-toolkit
    ````

  - install Boost 1.62+
	````
	wget -O boost_1_60_0.tar.gz https://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz/download
	tar xvfz boost_1_60_0.tar.gz
	cd boost_1_60_0
	./bootstrap.sh --prefix=/usr/
	./b2 --show-libraries
	sudo ./b2 --with-system --with-log --with-date_time --with-filesystem --with-thread install
	sudo ./b2 install
	````
  - After that open the terminal and run the following commands in your home folder:
	````
	sudo apt-get update 
	sudo apt-get install libsodium-dev
	sudo apt-get install cmake3
	sudo apt-get install gcc-5 g++-5
	sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 60 --slave /usr/bin/g++ g++ /usr/bin/g++-5
	git clone https://bitbucket.org/kfginternational/nheqminer.git
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

CPU settings
	-t [num_thrds]	Number of CPU threads
	-e [ext]	Force CPU ext (0 = SSE2, 1 = AVX, 2 = AVX2)

NVIDIA CUDA settings
	-ci		CUDA info
	-cd [devices]	Enable CUDA mining on spec. devices
	-cb [blocks]	Number of blocks
	-ct [tpb]	Number of threads per block
Example: -cd 0 2 -cb 12 16 -ct 64 128
  
Example to mine on your CPU with your own BPQ address and worker1 on BPQ TESTNET server:
- testnet:
        `nheqminer -l pool.testnet.bitcoinpq.org:3857 -u BPQ_TESTNET_ADDRESS_HERE.worker1`
- mainnet:
        `nheqminer -l pool.bitcoinpq.org:3857 -u BPQ_MAINNET_ADDRESS_HERE.worker1`        

Example to mine on your CPU with your own BPQ address and worker1 on BPQ server, using 6 threads:
- testnet:
        `nheqminer -l pool.testnet.bitcoinpq.org:3857 -u BPQ_TESTNET_ADDRESS_HERE.worker1 -t 6`
- mainnet:
        `nheqminer -l pool.bitcoinpq.org:3857 -u BPQ_MAINNET_ADDRESS_HERE.worker1 -t 6`

<i>Note: if you have a 4-core CPU with hyper threading enabled (total 8 threads) it is best to run with only 6 threads (experimental benchmarks shows that best results are achieved with 75% threads utilized)</i>

Example to mine on your CPU as well on your CUDA GPUs with your own BPQ address and worker1, using 6 CPU threads and 2 CUDA GPUs:
- testnet:
        `nheqminer -l pool.testnet.bitcoinpq.org:3857 -u BPQ_TESTNET_ADDRESS_HERE.worker1 -t 6 -cd 0 1`
- mainnet:
        `nheqminer -l pool.bitcoinpq.org:3857 -u BPQ_MAINNET_ADDRESS_HERE.worker1 -t 6 -cd 0 1`

