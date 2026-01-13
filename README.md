# Wiff
- Command line utility helper written in c++

## Requirements

### For Users
- **Operating System:** Ubuntu/Debian
- **Privileges:** `sudo` access to install `.deb` packages  

### For Developers / Building from Source
- **g++ compiler** (supports C++23)  
- **dpkg-deb** (for building `.deb` packages)  

---


# Downloading & Installing Wiff (USER)(64-bit, `amd64`)  
1. Go to terminal and wget the .deb file
    ```
    wget https://github.com/ChrisEberleSchool/Wiff/releases/download/v0.2/wiff.deb
    ```
2. Install it
    ```
    sudo dpkg -i wiff.deb
    ```
3. Test a basic grab command
    ```
    wiff grab -e txt --size ~/Documents
    ```
### **Uninstalling Wiff**
    sudo apt purge wiff

# Downloading & Installing Wiff (From source)  
1. Clone the repo
    ```
    git clone https://github.com/ChrisEberleSchool/Wiff.git
    ```
2. modify wiff/DEBIAN/control to use your CPU architecture
    ```
    Architecture: amd64
    ```
3. From root build
    ```
    ./build.sh
    ```
4. Run binary
    ```
    ./wiff/usr/bin/wiff
    ```
    
# Wiff Guide

    grab 
        Searches for files in bulk by name or extension. Defaults by full filename if no flag is provided.
              Usage:   wiff grab [search-flag] [target] [sort-flag] [directory] 

    help    
        Shows help information for commands
              Usage:    wiff help [command]


    SEARCH FLAGS: Defaulted to filename
        -e <extension>   # Find files by extension
        -n <file-body>    # Find files by just the body name not extension

    SORT FLAGS:
        --size           # Sort results by file size descending
        --date           # Sort results by date descending (newest first)
        --alpha          # Sort results alphabetically (default)

    EXAMPLE (Find all files with extension txt in the current directory and sort by size):
        > wiff grab -e txt --size
    
    EXAMPLE (Find all files with name README in the Documents directory and sort by date):
        > wiff grab -n README --size ~/Documents