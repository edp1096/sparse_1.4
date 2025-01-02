https://sparse.sourceforge.net

not https://www.netlib.org/sparse

MinGW compilation

```powershell
cd src
make clean
make

cd ..
cd bin

.\sparse.exe .\mat0
```

```powershell
cd examples/ac
gcc -I ../../src main.c -L ../../lib -l sparse -l m -o ../../bin/ac.exe
cd ../..

cd bin
.\ac.exe
```

```powershell
cd examples/op
gcc -I ../../src main.c -L ../../lib -l sparse -o ../../bin/op.exe
cd ../..

cd bin
.\op.exe
```

```powershell
cls

cd src
make
cd ..

cd examples/factor0
gcc -I ../../src main.c -L ../../lib -l sparse -o ../../bin/factor0.exe
cd ../..

cd bin
.\factor0.exe
cd ..

```

```powershell
cls

cd src
make
cd ..

cd examples/solve1
gcc -I ../../src main.c -L ../../lib -l sparse -o ../../bin/solve1.exe
cd ../..

cd bin
.\solve1.exe
cd ..

```

```powershell
cls

cd src
make
cd ..

cd examples/solve2
gcc -I ../../src main.c -L ../../lib -l sparse -o ../../bin/solve2.exe
cd ../..

cd bin
.\solve2.exe
cd ..

```

```powershell
cls

cd src
make
cd ..

cd examples/op
gcc -I ../../src main.c -L ../../lib -l sparse -o ../../bin/op.exe
cd ../..

cd bin
.\op.exe
cd ..

```

```powershell
cls

cd src
make
cd ..

cd examples/ac
gcc -I ../../src main.c -L ../../lib -l sparse -o ../../bin/ac.exe
cd ../..

cd bin
.\ac.exe
cd ..

```
