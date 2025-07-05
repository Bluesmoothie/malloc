cc -Iinclude -Ilibft/include tests.c -L./ -lft_malloc -lft -g3
export LD_LIBRARY_PATH=./$LD_LIBRARY_PATH
./a.out