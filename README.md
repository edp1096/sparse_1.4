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
cd examples/factor1
gcc -I ../../src main.c -L ../../lib -l sparse -o ../../bin/factor1.exe
cd ../..

cd bin
.\op.exe
```

```powershell
cls

cd src
make
cd ..

cd examples/factor1
gcc -I ../../src main.c -L ../../lib -l sparse -o ../../bin/factor1.exe
cd ../..

cd bin
.\factor1.exe
cd ..

```
