This is my first project, i have done it by myself.

EXPLAIN:
	OS: ubuntu
	
	This project doesn't like others 802.1x program, it don't need pcap library and libinet library, other 802.1x program often need that library. After you make Makefile int dialdir/ directory, you can run it directly.
	
Usage:
	If it's the first time to use it, you need do the next step:
		cd ./ctrldir
		sudo ./house_dial -cfg
	this step will initialize and config the enviroment before you run this program.
	
	Run the dialer:
		cd ./dialdir
		make clean; make
		sudo ./house_dial
		
	After run the dialer, you can use a script to control the dialer:
		cd ./ctrldir
		make clean;make
		./logon.sh
	
	In particular, the . directory means the project's root director, in here, is "House_8021X_Client".
	
Contact:
	kidult1107@126.com
	Thank you for watching this, and if you find any question, please contact me.
