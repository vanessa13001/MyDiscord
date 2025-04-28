cmake_minimum_required(VERSION 3.10)
project(MyDiscord C)

# Устанавливаем стандарт C
set(CMAKE_C_STANDARD 99)

# Устанавливаем PKG_CONFIG_PATH (если используете GTK4)
set(ENV{PKG_CONFIG_PATH} "/ucrt64/lib/pkgconfig:/mingw64/lib/pkgconfig")

# Найти пакеты, используемые в проекте (GTK4)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# Путь к PostgreSQL (убедитесь, что он верный)
set(POSTGRESQL_ROOT "C:/msys64/ucrt64")

# Поиск библиотеки PostgreSQL для MinGW
find_library(PostgreSQL_LIBRARY
    NAMES pq libpq
    PATHS "${POSTGRESQL_ROOT}/lib"
    NO_DEFAULT_PATH
)

# Поиск заголовочных файлов PostgreSQL
find_path(PostgreSQL_INCLUDE_DIR
    NAMES libpq-fe.h
    PATHS "${POSTGRESQL_ROOT}/include"
    NO_DEFAULT_PATH
)

if(EXISTS ${POSTGRESQL_LIBRARY_STATIC})
    set(PostgreSQL_LIBRARY ${POSTGRESQL_LIBRARY_STATIC})
endif()

# Проверка наличия PostgreSQL
if(NOT PostgreSQL_LIBRARY OR NOT PostgreSQL_INCLUDE_DIR)
    message(FATAL_ERROR "PostgreSQL not found. Please set POSTGRESQL_ROOT to the correct path.")
endif()

# Общие include директории
include_directories(server client)

# Источники для сервера и клиента
set(SERVER_SRC
    server/server.c
    server/auth.c
    server/database.c
)

set(CLIENT_SRC
    client/client.c
)

# --- Сервер ---
add_executable(server ${SERVER_SRC})
# Добавляем include директории для сервера
target_include_directories(server PRIVATE ${GTK4_INCLUDE_DIRS} ${PostgreSQL_INCLUDE_DIR})
# Линковка с библиотеками для сервера
target_link_libraries(server PRIVATE ${GTK4_LIBRARIES} ${PostgreSQL_LIBRARY} ws2_32)
# Определения для компилятора
target_compile_definitions(server PRIVATE _WINSOCK_DEPRECATED_NO_WARNINGS)

# --- Клиент ---
add_executable(client ${CLIENT_SRC})
# Добавляем include директории для клиента
target_include_directories(client PRIVATE ${GTK4_INCLUDE_DIRS})
# Линковка с библиотеками для клиента
target_link_libraries(client PRIVATE ${GTK4_LIBRARIES} ws2_32)
# Определения для компилятора
target_compile_definitions(client PRIVATE _WINSOCK_DEPRECATED_NO_WARNINGS)

# Вывод информации о найденных библиотеках
message(STATUS "PostgreSQL lib: ${PostgreSQL_LIBRARY}")
message(STATUS "PostgreSQL include: ${PostgreSQL_INCLUDE_DIR}")
message(STATUS "GTK4 libs: ${GTK4_LIBRARIES}")
