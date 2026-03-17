cmake_minimum_required(VERSION 3.16)
project(SymbolPicker VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(symbol_picker
    main.cpp
    flowlayout.h
    flowlayout.cpp
    mainwindow.h
    mainwindow.cpp
)

target_link_libraries(symbol_picker PRIVATE Qt6::Widgets)

# Abilita high-DPI scaling automatico
target_compile_definitions(symbol_picker PRIVATE QT_USE_QSTRINGBUILDER)

install(TARGETS symbol_picker
    RUNTIME DESTINATION bin
)
