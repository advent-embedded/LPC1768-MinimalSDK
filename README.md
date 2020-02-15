# LPC1768-MinimalSDK
LPC1768 ARM-Cortex M3 Miminal SDK for Bootstrapping with USB-MSC Bootloader

__Author__ : Kannan P
__Updated__ : 2020-02-15
__E-mail__  : kannanetech@gmail.com

This repository hosts a minimal SDK source & utilites for LPC1786 ARM CM3 firmware development with USB Mass Storage Bootloader, which facilitates firmware updation via a simple file drag-and-droping the firmware. When Bootloader is activated upon reset via some H/W switch the Controller's flash is emulated as Flash drive in most operating systems. Howerver in GNU/Linx based OS'es firmware drag-and-drop to emulated flash dosen't go smooth. A seperate bash script ```lpcflash``` does this trick. This SDK best suits for all GNU/Linux distribution however with few minor changes can be ported to work on Windows.

__Install below Pre-requisite tools-(Toolchains/Compiler)__

### Install ARM toolchains
```
sudo apt-get install update -y
sudo apt-get install gcc-arm-none-eabi -y
sudo apt-get install binutils-arm-none-eabi -y
sudo apt-get install  -y libnewlib-arm-none-eabi
```

[ARM GCC/Binutils Toolchain](https://launchpad.net/gcc-arm-embedded)

__Get the copy of SDK by Cloning to your local machine's Home Location:__
```
cd ~
git clone https://github.com/advent-embedded/LPC1768-MinimalSDK.git
cd LPC1768-MinimalSDK
sudo cp lpcflash /usr/bin
sudo chmod a+x /usr/bin/lpcflash
```
__Set bash's alias for easy invoking our SDK's Makefile targets__
Add two aliases ```lpcbuild``` and ```lpcclean``` to .bashrc file
```
gedit ~/.bashrc 

alias lpcbuild='make -f /home/{your-home-location}/LPC1768-MinimalSDK/Makefile all'
alias lpcclean='make -f /home/{your-home-location}/LPC1768-MinimalSDK/Makefile clean' 
```
