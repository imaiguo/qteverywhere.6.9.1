
# Qt 6


## 1 Windows:

- 依赖 

- Python3 [https://www.python.org/downloads/windows/] or from Microsoft Store

### 1.1 构建debug版本
```bash
> mkdir build & cd build
> cmd
> "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
> set OPENSSL_ROOT_DIR=D:/devtools/openssl.3.0.8/debug/
> ..\configure.bat -prefix D:\devtools\Qt.6.9.1 -debug -opensource -confirm-license -no-rpath -verbose -no-strip -accessibility -no-directfb -no-use-gold-linker -nomake examples -nomake tests -opengl -proprietary-codecs -webengine-jumbo-build 0 -webengine-kerberos -openssl-linked
> cmake --build .. --parallel
> cmake --install ..
>
```
### 1.2 构建release版本
```bash
> ..\configure.bat -prefix D:\devtools\Qt.6.9.1 -release -opensource -confirm-license -no-rpath -verbose -no-strip -accessibility -no-directfb -no-use-gold-linker -nomake examples -nomake tests -qt-zlib -qt-libpng -qt-libjpeg -opengl -proprietary-codecs -webengine-jumbo-build 0 -webengine-kerberos -openssl-linked OPENSSL_INCDIR=D:/devtools/openssl.3.0.8/include OPENSSL_LIBDIR=D:/devtools/openssl.3.0.8/lib
>
```


## 1.5 开发环境设置

set PATH=C:\Qt\Qt-major.minor.patch\bin;%PATH%

