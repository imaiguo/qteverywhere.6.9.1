
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
> set Path=D:\devtools\Strawberry\perl\bin;%Path%
> set OPENSSL_ROOT_DIR=D:/devtools/openssl.3.0.8/debug/
> ..\configure.bat -prefix D:\devtools\Qt.6.9.1 -debug -opensource -confirm-license -no-rpath -verbose -no-strip -accessibility -no-directfb -no-use-gold-linker -nomake examples -nomake tests -opengl -openssl-linked -DFEATURE_webengine_proprietary_codecs=ON -webengine-jumbo-build 0 -DFEATURE_webengine-kerberos
> cmake --build .. --parallel
> cmake --install ..
>
```

### 1.2 构建release版本
```bash
> set OPENSSL_ROOT_DIR=D:/devtools/openssl.3.0.8/
> ..\configure.bat -prefix D:\devtools\Qt.6.9.1 -release
>
```

### 1.3 构建静态debug版本

### 1.4 构建静态release版本

## 1.5 开发环境设置

set PATH=C:\Qt\Qt-major.minor.patch\bin;%PATH%



WARNING: The Clang-based lupdate parser will not be available. Suitable LLVM and Clang C++ libraries have not been found. You will need to set the FEATURE_clangcpp CMake variable to ON to re-evaluate this check.
WARNING: Qt WebEngine And Qt Pdf SBOM generation will be skipped due to missing dependencies. Required Python dependencies not found:  spdx_tools.spdx.clitools.pyspdxtools

WARNING: QtWebEngine won't be built. The following configure errors were found:
 * Tool flex is required.
 * Tool bison is required.
 * Tool gperf is required.
 * Python3 html5lib is missing (C:/Program Files/WindowsApps/PythonSoftwareFoundation.Python.3.11_3.11.2544.0_x64__qbz5n2kfra8p0/python3.11.exe).

To configure and build other Qt modules, you can use the following convenience script:
        D:/devtools/Qt.6.9.1/bin/qt-configure-module.bat

If reconfiguration fails for some reason, try removing 'CMakeCache.txt' from the build directory
Alternatively, you can add the --fresh flag to your CMake flags.

-- Configuring done (362.4s)
-- Generating done (28.3s)
CMake Warning:
  Manually-specified variables were not used by the project:

    INPUT_strip


-- Build files have been written to: D:/workspace/qteverywhere.6.9.1/build



## 参考
- Qt WebEngine Platform Notes https://doc.qt.io/qt-6/qtwebengine-platform-notes.html