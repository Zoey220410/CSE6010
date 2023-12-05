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
./connected filename 1 or 2

Example: To calculate the number of connected components in "connections_test.txt", and exclude all edges representing occasional contacts, simply run the following command:
./connected connections_test.txt 1