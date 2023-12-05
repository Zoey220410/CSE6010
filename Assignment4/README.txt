> gcc --version
gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
Target: x86_64-linux-gnu
Thread model: posix


> Operating System: GNU/Linux
> Chip: AMD Ryzen 7 5800H with Radeon Graphics
> Memory: 7G
 
> Distributor ID: Ubuntu
Description:    Ubuntu 22.04.3 LTS
Release:        22.04
Codename:       jammy


To compile the code, simply run the following command:
make


To run the code, simply run the following command:
./particles filename targetTime

Example: To simulate the collisions of particles in "particles1.txt" within 15 seconds, simply run the following command: ./particles particles1.txt 15