cmake_minimum_required(VERSION 3.10)
project(Lab1_Sorting)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим все .cpp файлы в папке lab1/
file(GLOB SOURCES "lab1/*.cpp")

# Создаём исполняемый файл
add_executable(sort_test ${SOURCES})

# Включаем папку с заголовочными файлами
target_include_directories(sort_test PRIVATE lab1)

# Для macOS: включаем возможность работы с filesystem
if(APPLE)
    target_link_libraries(sort_test -framework CoreFoundation)
endif()