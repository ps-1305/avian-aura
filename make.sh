clear
gcc -o main login.c `pkg-config --cflags --libs gtk+-3.0`
./main