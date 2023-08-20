gcc core.c -shared -fPIC -o core.so
gcc main.c core.so -o main -Wl,-rpath=.