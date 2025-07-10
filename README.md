
# Qt 6

- C++20 compiler support
- CMake version at least 3.19 or higher.
- 64-bit Nodejs 14.9 version or later.
- Python 3.8 version or later.
- Python3 html5lib module.
- GNU gperf binary.
- GNU bison binary.
- GNU flex binary.

## 1 Windows:

- 依赖
- Python3 [https://www.python.org/downloads/windows/] or from Microsoft Store

安装python依赖
```bash
> pip install spdx-tools html5lib -i https://pypi.tuna.tsinghua.edu.cn/simple
>
```

### 1.1 构建debug版本
```bash
> mkdir build & cd build
> cmd
> "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
> set Path=D:\devtools\Strawberry\perl\bin;D:\workspace\qteverywhere.6.9.1\gnuwin32\bin;%Path%
> set OPENSSL_ROOT_DIR=D:/devtools/openssl.3.0.8/debug/
>
> ..\configure.bat -prefix D:\devtools\Qt.6.9.1 -debug-and-release -opensource -confirm-license -no-rpath -verbose -accessibility -no-directfb -no-use-gold-linker -nomake examples -nomake tests -opengl -openssl-linked -webengine-proprietary-codecs -webengine-jumbo-build 0
> -webengine-jumbo-build 0
> -webengine-kerberos
> cmake --build .. --parallel
> cmake --install ..
>
```

### 1.2 构建静态版本
> ..\configure.bat -prefix D:\devtools\Qt.6.9.1 -debug-and-release -static -opensource -confirm-license -no-rpath -verbose -accessibility -no-directfb -no-use-gold-linker -nomake examples -nomake tests -opengl -openssl-linked -webengine-proprietary-codecs -webengine-jumbo-build 0

### 1.3 开发环境设置

set PATH=C:\Qt\Qt-major.minor.patch\bin;%PATH%


### 1.6 报错
 * Tool flex is required.
 * Tool bison is required.
 * Tool gperf is required.
 * Python3 html5lib is missing (C:/Program Files/WindowsApps/PythonSoftwareFoundation.Python.3.11_3.11.2544.0_x64__qbz5n2kfra8p0/python3.11.exe).


## 参考
- Qt WebEngine Platform Notes https://doc.qt.io/qt-6/qtwebengine-platform-notes.html
