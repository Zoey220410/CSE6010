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
./bellmanford filename threads vertex-number(optional)

Example: 
1.To find the shortest path of vertex 5 in "graph10-70.txt" and use 4 threads, simply run the following command: ./bellmanford graph10-70.txt 4 5
2.To find all the shortest paths of vertexes in "graph10-70.txt" and use 4 threads, simply run the following command: ./bellmanford graph10-70.txt 4

