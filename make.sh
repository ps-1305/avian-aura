clear
gcc -o login login.c `pkg-config --cflags --libs gtk+-3.0` 
./login