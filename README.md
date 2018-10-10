# CbersUI
QT Ribbon 插件系统

特别感谢 一去丶二三里 http://blog.csdn.net/liang19890820， 博主文章中关于QT的讲解非常清楚

x3py - C++ Plugin Framework
https://github.com/rhcad/x3py

使用说明：
1. 将插件模板中的qtcreator\share内容，拷贝到qtcreator下替换, 使用QtCreator进行编程时，添加了插件工程和类的向导
2. 新建项目， 选Library中的CbersPlugin Project，将创建一个插件工程
3. 添加新文件时，选C++中的CbersPlugin Class，将创建不同类型的插件（一个插件工程中，可以包含多个插件）
4. 打开项目中的module.cpp文件，添加插件的头文件，并在XBEGIN_DEFINE_MODULE下，增加XDEFINE_CLASSMAP_ENTRY(插件类名)