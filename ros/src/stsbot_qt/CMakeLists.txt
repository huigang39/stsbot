cmake_minimum_required(VERSION 3.5)         #需要的CMake最低版本

project(stsbot_qt VERSION 0.1 LANGUAGES CXX)  #项目版本0.1, 编程语言是C++

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS "ui")
set(CMAKE_AUTOUIC ON)       # UIC能被自动执行
set(CMAKE_AUTOMOC ON)       # MOC能被自动执行
set(CMAKE_AUTORCC ON)       # RCC能被自动执行

set(CMAKE_CXX_STANDARD 11)  #设置编译器需要满足的C++语言标准， 设置为 C++ 11
set(CMAKE_CXX_STANDARD_REQUIRED ON)  #要求编译器满足 C++标准

find_package(ament_cmake REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)       #查找Qt6或Qt5，导入Widgets模块
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Multimedia MultimediaWidgets SerialPort REQUIRED)  #查找Qt6，导入Widgets模块

file(GLOB PRO_SOURCE_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)
file(GLOB PRO_UI_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS ui/*.ui)
file(GLOB PRO_INCLUDE_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS include/*.h *.hpp)
file(GLOB PRO_RESOURCE_DIR RELATIVE ${CMAKE_SOURCE_DIR} FOLLOW_SYMLINKS resource/*.qrc)

add_executable(${PROJECT_NAME}
    ${PRO_SOURCE_DIR}
    ${PRO_INCLUDE_DIR}
    ${PRO_RESOURCE_DIR}
    ${QT_UI_HPP} # UI的文件应该不需要添加在这里
    ${QT_MOC_HPP}
    ${QT_RESOUCE_HPP}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)    #如果是Qt6以上的版本
    qt_add_executable(${PROJECT_NAME}       #创建可执行文件 samp2_4
        MANUAL_FINALIZATION         #可选参数，手动结束创建目标的过程
        ${PROJECT_SOURCES}          #文件列表来源于前面定义的变量PROJECT_SOURCES
    )
endif()
target_include_directories(${PROJECT_NAME} PRIVATE include)

#在连接生成目标${PROJECT_NAME}时, 需要利用前面用find_package()导入的 Qt6::Widgets库
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets Qt${QT_VERSION_MAJOR}::SerialPort)

#设置目标可执行文件的属性，如MacOSX的Bundle标识符、版本号和短版本字符串，以及在Windows下作为可执行文件运行。
set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})     #结束生成可执行文件的过程
endif()

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
