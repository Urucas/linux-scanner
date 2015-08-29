# linux-scanner
Scanning in linux from command-line

#Build dependencies
[sane](http://www.sane-project.org/)
```bash
sudo apt-get install libsane-dev
```
[libpng](http://www.libpng.org/pub/png/libpng.html)
```bash
sudo apt-get install libpng12-dev
```

#Build

```bash
./build.sh
```

#Run
x86_64
```bash
./linux-scanner
```
i386
```bash
./linux-scanner32
```
