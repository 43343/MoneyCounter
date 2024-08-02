cmake_minimum_required(VERSION 3.16)

project(MoneyCounter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
if(WIN32)
    set(Qt6_DIR "C://Qt//6.8.0//msvc2022_64//lib//cmake//Qt6")
    set(APP_ICON_RESOURCE_WINDOWS "res/app_icon.rc")
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts Sql)
qt_standard_project_setup()
qt6_add_resources(QRCS res/resources.qrc)

set(Sources
    src/Main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
    src/AddExpenses.h
    src/AddExpenses.cpp
    src/PasswordEntry.h
    src/PasswordEntry.cpp
    src/RegistrationWindow.h
    src/RegistrationWindow.cpp
    src/DatabaseManager.h
    src/DatabaseManager.cpp
    src/CategoryData.h
    src/CategoryData.cpp
    src/Square.h
    src/Square.cpp
    src/ChangeTypeDate.h
    src/ChangeTypeDate.cpp
    ${QRCS}
)

if(WIN32)
    list(APPEND Sources ${APP_ICON_RESOURCE_WINDOWS})
endif()

qt_add_executable(MoneyCounter ${Sources})

target_link_libraries(MoneyCounter PRIVATE Qt6::Core Qt6::Widgets Qt6::Charts Qt6::Sql)
set_target_properties(MoneyCounter PROPERTIES
    WIN32_EXECUTABLE ON
    LINUX_EXECUTABLE ON
)
install(TARGETS MoneyCounter)