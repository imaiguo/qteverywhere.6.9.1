

## cpp和h文件只能放在代码根目录

- QML[Qt Meta Language 或者 Qt Modeling Language]
- Qt引入了一种声明式脚本语言
- 作为C++语言的一种替代
- Qt Quick就是使用QML构建的一套类库
- QML 是一种基于 JavaScript 的声明式语言

## 配置开发运行环境

### Qt6.9.1环境

```bash
> cmd
> "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
> set Path=D:\devtools\Qt.6.9.1\bin;D:\devtools\openssl.3.0.8\bin;%Path%
> # 静态编译
> set Path=D:\devtools\Qt.6.9.1\static\bin;D:\devtools\openssl.3.0.8\bin;%Path%
>
```

## 计划

- 1. 代码集中一个目录   V
- 2. QWindow和QWidget 是否有阴影            -----------------
- QWidget 窗口抗锯齿圆角的一个实现方案        -----------------
- 3. 集成到BlueHelper中                     -----------------

- 3. 菜单栏处理
- 4. tab顶层配置
- 5. 进度条放到最下面

- 6. 列出当前所有 QUrl
- 7. 在新打开的tab中访问指定的 QUrl
- 8. 激活指定已打开QUrl的tab
