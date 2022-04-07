gcc -g -Wall -fopenmp -std=c99  -o genprime genprimes.c  -lm

echo 1; ./genprime 1000 1
echo 2; ./genprime 1000 2
echo 5; ./genprime 1000 5
echo 10; ./genprime 1000 10
echo 25; ./genprime 1000 25
echo 50; ./genprime 1000 50
echo 100; ./genprime 1000 100

echo "\\n------------------------\\n\\n"

echo 1; ./genprime 1000000 1
echo 2; ./genprime 1000000 2
echo 5; ./genprime 1000000 5
echo 10; ./genprime 1000000 10
echo 25; ./genprime 1000000 25
echo 50; ./genprime 1000000 50
echo 100; ./genprime 1000000 100
