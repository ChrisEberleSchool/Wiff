# Wiff

**Wiff** is a fast, versatile command-line utility suite written in C++ that goes beyond standard CLI tools. It starts with powerful bulk file search capabilities and aims to grow into a full toolkit of commands that provide functionality typical command-line utilities don’t offer — like advanced file discovery, disk usage insights, identifying oversized or redundant files, and other productivity-boosting operations — all designed to save time and streamline file management.

[![Release](https://img.shields.io/github/v/release/ChrisEberleSchool/Wiff?color=blue&label=latest)](https://github.com/ChrisEberleSchool/Wiff/releases)
[![License](https://img.shields.io/github/license/ChrisEberleSchool/Wiff)](LICENSE)

---

## Table of Contents

- [Requirements](#requirements)
- [Downloading & Installing](#downloading--installing)
  - [User Installation (.deb)](#user-installation-prebuilt-packages)
  - [Building from Source](#building-from-source)
- [Usage Guide](#wiff-guide)
- [Contributing](#contributing)
- [AI Disclaimer](#ai-disclaimer)
- [License](#license)

---

## Requirements

### For Users

- **Operating System:** Linux, macOS
- **Privileges:** `sudo` access for installing `.deb` packages (Linux)

### For Developers / Building from Source

#### Linux

- **g++ compiler** (supports C++23)
- **dpkg-deb** (for building `.deb` packages)
- **CMake** (for building from source)

#### macOS

- **Apple clang++** (version 15+ for C++20/23 features, including `std::jthread`)
- **CMake** (for building from source)
- **Homebrew** (optional, for installing dependencies)

#### Windows

- **MSVC / Visual Studio 2022+** (with C++20/23 support)
- **CMake** (for cross-platform builds)
- **Git** (for cloning repository)

---

## Downloading & Installing Wiff

### User Installation (Prebuilt Packages)

<details>
  <summary>Linux (64-bit `amd64`) or ARM64</summary>

1. Download the `.deb` release for your architecture from releases.


2. Install it like this putting in the deb filename you downloaded:

```bash
sudo apt install ~/Downloads/<DOWNLOADED_DEB_FILE_GOES_HERE>
```

3. Test a basic command:

```bash
wiff grab -e txt --size ~/Documents
```

**Uninstalling Wiff**

```bash
sudo apt purge wiff
```

</details>

<details>
  <summary>macOS</summary>

- **N/A** (No prebuilt package available yet)
- You can build from source using the instructions below.

</details>

<details>
  <summary>Windows</summary>

- **N/A** (No prebuilt package available yet)
- Build from source using Visual Studio + CMake.

</details>

---

### Building from Source

This works on **Linux, macOS, and Windows**

<details>
  <summary>Build Instructions</summary>

1. Clone the repository:

```bash
git clone https://github.com/ChrisEberleSchool/Wiff.git
cd Wiff
```

2. (Optional) On Linux, check your architecture matches CPack build:

```bash
uname -m   # x86_64 or aarch64
```

3. Run the build script:

```bash
./build.sh
```

- On Linux, this will create a `.deb` in the `build/` folder.
- On macOS, this will build the `wiff` binary only.

4. Run the binary:

```bash
./build/wiff
# or if installed via .deb
wiff grab -e txt --size ~/Documents
```

</details>


## Wiff Guide

### Commands

**grab**  
Searches for files in bulk by name or extension. Defaults to filename search if no flag is provided.

**Usage:**

```bash
wiff grab [search-flag] [target] [sort-flag] [directory]
```

**help**  
Shows help information for commands:

```bash
wiff help [command]
```

---

### Search Flags

| Flag             | Description                                 |
| ---------------- | ------------------------------------------- |
| `-e <extension>` | Find files by extension                     |
| `-n <file-body>` | Find files by name body (without extension) |

### Sort Flags

| Flag      | Description                                    |
| --------- | ---------------------------------------------- |
| `--size`  | Sort results by file size descending           |
| `--date`  | Sort results by date descending (newest first) |
| `--alpha` | Sort results alphabetically (default)          |

### Examples

- Find all `.txt` files in the current directory and sort by size:

```bash
wiff grab -e txt --size
```

- Find all files named `README` in the `Documents` directory and sort by date:

```bash
wiff grab -n README --date ~/Documents
```

---

## Contributing

We welcome contributions! To keep the project organized and maintain semantic versioning, please follow these guidelines:

---

### Issues

We use **GitHub Issues** to track all work, including features, bug fixes, and chores:

1. **Create an issue first** before starting work.  
   - Use the appropriate template:  
     - **Bug Report** → problems or unexpected behavior  
     - **Feature Request** → new functionality  
     - **Chore / Maintenance** → CI, tests, tooling, documentation  
2. Reference the issue in commits and PRs:  
   ```
   chore(ci): add GitHub Actions workflow

   Closes #12
   ```

3. **Branch from the issue**:  
   - Using GitHub CLI:
     ```
     gh issue checkout <issue-number>
     ```
   - Or manually:
     ```
     git checkout dev
     git pull origin dev
     git checkout -b chore/12-add-gtest
     ```

---

### Branching

- Branch **off `dev`**, never `main`.  
- Name branches according to semantic-release type and issue:

| Type                | Example                        |
| ------------------- | ------------------------------ |
| Feature             | `feat/15-add-login-command`     |
| Bugfix              | `fix/23-handle-empty-results`   |
| Chore / Maintenance | `chore/12-update-ci-pipeline`   |

---

### Commit Messages

We follow **Semantic Release conventions**:

```
<type>(<scope>): <short description>
```

| Type       | Description                       |
| ---------- | --------------------------------- |
| `feat`     | New feature                       |
| `fix`      | Bug fix                           |
| `chore`    | Maintenance / build / CI          |
| `docs`     | Documentation only                |
| `refactor` | Code change, no new feature / fix |
| `test`     | Adding/updating tests             |

**Reference the issue in commits:**
```
git commit -m "chore(ci): add GitHub Actions workflow

Closes #12"
```

---

### Contributing Workflow

<details>
<summary>Write Access Contributors</summary>

If you **have write access** to this repository:

1. Branch directly from `dev`:
   ```
   git checkout dev
   git pull origin dev
   git checkout -b feat/add-login-command
   ```
2. Make your changes, commit using semantic-release conventions, and reference the issue:
   ```
   git commit -m "feat(parser): add regex support

   Closes #15"
   ```
3. Push your branch to the main repo:
   ```
   git push origin feat/add-login-command
   ```
4. Open a pull request targeting the `dev` branch.

</details>

<details>
<summary>Fork Contributors</summary>

If you **don’t have write access**, you need to fork the repo first:

1. Click **Fork** on GitHub to create your personal copy.  
2. Clone your fork locally:
   ```
   git clone https://github.com/your-username/your-repo.git
   cd your-repo
   ```
3. Add the original repository as an upstream remote:
   ```
   git remote add upstream https://github.com/original-owner/your-repo.git
   git fetch upstream
   ```
4. Branch off `dev` from the upstream repo:
   ```
   git checkout dev
   git pull upstream dev
   git checkout -b feat/add-login-command
   ```
5. Make your changes and commit using semantic-release conventions:
   ```
   git commit -m "feat(parser): add regex support

   Closes #15"
   ```
6. Push your branch to **your fork**:
   ```
   git push origin feat/add-login-command
   ```
7. Open a pull request from your fork targeting the `dev` branch of the main repository.

</details>

---

### Pull Requests

- Always target the **`dev` branch**.  
- Include tests for new features or fixes if possible.  
- Reference the related issue (`Closes #<issue-number>`) to automatically close it when merged.  
- Provide a clear description of what the PR does and why.


## AI Disclaimer

> ⚠️ **AI Disclaimer:** AI was used solely to assist in generating this README and other project documentation. All code, commands, and project logic were created and reviewed by the project maintainers.
