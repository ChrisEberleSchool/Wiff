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
    wget https://github.com/ChrisEberleSchool/Wiff/releases/download/v0.2/wiff.deb
    ```
2. Install it
    ```
    sudo dpkg -i wiff.deb
    ```
3. Test using the currently only working command
    ```
    wiff grab <extension>
    ```
### **Uninstalling Wiff**
    sudo apt purge wiff
    

# Building Wiff (DEVELOPER)
1. Clone the source code:
    ```
    https://github.com/ChrisEberleSchool/Wiff.git
    ```
2. Go to root directory in terminal:
3. Enter the build command:
    ```
    ./build.sh
    ```
5. To run Wiff locally enter:
    ```
    ./wiff/usr/bin/wiff 
    ```

# Uninstall Wiff (USER)
    ```
    sudo apt purge wiff
    ```