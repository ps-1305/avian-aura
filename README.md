<img width="685" alt="Screenshot 2024-03-20 at 22 09 34" src="https://github.com/ps-1305/avian-aura/assets/147681761/12f020f9-f9f6-4953-bf77-730b9ef34375">

# Introduction
One stop solution to your travel management!

# Dependencies
### The software requires the header file ```dependencies.h``` in the working directory.
### Four external modules/libraries have been utilised : Ncurses, Sqlite3, cURL and jansson
## For MacOS
- Install homebrew
```zsh
% /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
- We install all the libraries using it
```zsh
% brew install ncurses && brew install sqlite3 && brew install curl && brew install jansson
```
- We find out the default includePath of our compiler
```zsh
gcc -x c -v -E /dev/null
```
- Finally we copy the files from homebrew to includePath
```zsh
cp -R <origin:headerFile> <destination:includePath>
```

# Running the program
### We run it using the following command in terminal
```zsh
% gcc -o main main.c -lncurses -lsqlite3 -lcurl -ljansson && ./main
```
