cmake_minimum_required(VERSION 3.16)
project(PhoneBookManagementSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    main.cpp
    src/Account.cpp
    src/AccountService.cpp
    src/Contact.cpp
    src/ContactService.cpp
    src/DBManager.cpp
    src/Group.cpp
    src/GroupService.cpp
    src/MenuUI.cpp
    src/Utils.cpp
)

add_executable(PhoneBookManagementSystem WIN32 ${SOURCES})

if(WIN32)
    target_link_libraries(PhoneBookManagementSystem PRIVATE user32 gdi32)
endif()

