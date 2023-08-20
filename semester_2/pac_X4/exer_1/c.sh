gcc integerset.c -shared -fPIC -o integerset.so
gcc sample.c integerset.so -o sample