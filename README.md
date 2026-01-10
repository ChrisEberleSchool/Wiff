# Wiff
- Command line utility helper written in c++

## Requirements

### For Users
- **Operating System:** Ubuntu/Debian (64-bit, `amd64`)  
- **Privileges:** `sudo` access to install `.deb` packages  

### For Developers / Building from Source
- **g++ compiler** (supports C++23)  
- **dpkg-deb** (for building `.deb` packages)  

---


# Downloading & Installing Wiff (USER)
1. Go to terminal and wget the .deb file
    ```
        wget https://github.com/ChrisEberleSchool/Wiff/releases/download/v0.1/wiff.deb
    ```
2. Install it
    ```
        sudo dpkg -i wiff.deb
    ```
3. Test using the currently only working command
    ```
        wiff grab <extension>
    ```

# Building the .dev (DEVELOPER)
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

# Uninstall Wiff
    ```
        sudo apt purge wiff
    ```