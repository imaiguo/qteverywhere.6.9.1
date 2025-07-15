
# Qt 6

- C++20 compiler support
- CMake version at least 3.19 or higher.
- 64-bit Nodejs 14.9 version or later.
- Python 3.8 version or later.
- Python3 html5lib module.
- GNU gperf binary.
- GNU bison binary.
- GNU flex binary.
- QtWebEngine Build requires Windows 11 SDK at least version 10.0.26100.0

## 1 Windows:

- 依赖
- Python3 [https://www.python.org/downloads/windows/] or from Microsoft Store

- 安装python依赖
```bash
> pip install spdx-tools html5lib -i https://pypi.tuna.tsinghua.edu.cn/simple
>
```

- 设置系统[区域设置] 使用UnionCode UTF-8提供全球语言支持 解决脚本中 [decode('utf8')]报错问题 qtwebengine/src/3rdparty/chromium/build/toolchain/win/tool_wrapper.py

- 避免源码路径超过256个字符 代码设置路径为[D:\qt6]

### 1.1 构建动态库
```bash
> mkdir buildqt & cd buildqt
> cmd
> "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
> set Path=D:\devtools\Strawberry\perl\bin;D:\qt6\gnuwin32\bin;D:\qt6\qtwebengine\tools\nodejs;D:\devtools\openssl.3.0.8\bin;%Path%
> set OPENSSL_ROOT_DIR=D:/devtools/openssl.3.0.8/
>
> ..\configure.bat -prefix D:\devtools\Qt.6.9.1 -shared -debug-and-release -opensource -confirm-license -no-rpath -verbose -accessibility -no-directfb -no-use-gold-linker -nomake examples -nomake tests -opengl -openssl-linked -webengine-proprietary-codecs -webengine-jumbo-build 0
>
> cmake --build . --parallel
> ninja -j 24
>
> cmake --install .
> ninja install
```

### 1.2 构建静态库
```bash
> ..\configure.bat -prefix D:\devtools\Qt.6.9.1\static -static -debug-and-release -opensource -confirm-license -no-rpath -verbose -accessibility -no-directfb -no-use-gold-linker -nomake examples -nomake tests -opengl -skip qtwebengine -openssl-linked
```

### 1.3 开发环境设置

```bash
> set PATH=D:\devtools\Qt.6.9.1\bin;%PATH%
```

## 参考
- Qt WebEngine Platform Notes https://doc.qt.io/qt-6/qtwebengine-platform-notes.html

## 源码下载 [https://download.qt.io/]

## 合并补丁
```bash
>
> git apply .\cve\CVE-2025-6338-qtbase-6.9.patch --directory=qtbase
> git apply .\cve\CVE-2025-6338-qtbase-6.9.patch --directory=qtbase --reject
```