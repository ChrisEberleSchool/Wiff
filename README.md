# Wiff
- Command line utility helper written in c++

# Building the .dev
1. Go to root dir
2. build the exe
    ```
        g++ -std=c++23 ./src/main.cpp -o ./wiff/usr/bin/wiff
    ```
3. then still in root build the deb
    ```
        dpkg-deb --build ./wiff 
    ```
4. Install the deb
    ```
        sudo dpkg -i ./wiff.deb  
    ```
5. Done!