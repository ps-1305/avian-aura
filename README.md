<img width="685" alt="Screenshot 2024-03-20 at 22 09 34" src="https://github.com/ps-1305/avian-aura/assets/147681761/12f020f9-f9f6-4953-bf77-730b9ef34375">

# Introduction
Features: 
- Flight booking
- Train booking
- Railway booking

# Dependencies
### The software requires the header files ```dependencies.h``` , ```secondary.h``` and ```graphs.h``` in the working directory.
### Four external modules/libraries have been utilised : GTK, cURL and jansson
## For MacOS
- Install homebrew
```zsh
% /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
- We install all the libraries using it
```zsh
% brew install gtk+3 && brew install jansson && brew install pkg-config
```
- We find out the default includePath of our compiler
```zsh
% gcc -x c -v -E /dev/null
```
- Finally we copy the files from homebrew to includePath
```zsh
% cp -R <origin:headerFile> <destination:includePath>
```
- Our program uses ```gtk+-3.24.6``` for its graphics rendering

# Running the program
### We run it using the shell file provided with the code 
```zsh
% sh make.sh
```
### We can also run it using the gcc command
```zsh
% gcc -o login login.c `pkg-config --cflags --libs gtk+-3.0` && ./login
```
