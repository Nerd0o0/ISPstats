cmake_minimum_required(VERSION 3.10)
project(ISPstats)
set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(include handlers/include ${CONAN_INCLUDE_DIRS})
include_directories(include unities/include ${CONAN_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp src/Server.cpp include/Server.h src/DBConnector.cpp include/DBConnector.h
        handlers/scr/Factory.cpp handlers/include/Factory.h handlers/scr/Error.cpp handlers/include/Error.h
        unities/src/SprintsAndProjects.cpp unities/include/SprintsAndProjects.h
        unities/src/JobsForPerson.cpp unities/include/JobsForPerson.h
        unities/src/JobsForSprint.cpp unities/include/JobsForSprint.h
        handlers/scr/handlers.cpp handlers/include/handlers.h include/Logger.h src/Logger.cpp
        unities/src/LeaderPerson.cpp unities/include/LeaderPerson.h unities/src/Base.cpp unities/include/Base.h)


target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME}  mariadbclient)
target_link_libraries(${PROJECT_NAME}  mariadb)


enable_testing()
add_executable(ISPtest	unittest/to_json.cpp
        unities/src/Base.cpp unities/include/Base.h
        unities/src/JobsForPerson.cpp unities/include/JobsForPerson.h
        unities/src/JobsForSprint.cpp unities/include/JobsForSprint.h
        unities/src/LeaderPerson.cpp unities/include/LeaderPerson.h
        unities/src/SprintsAndProjects.cpp unities/include/SprintsAndProjects.h)
target_link_libraries(ISPtest ${CONAN_LIBS})
add_test(NAME ISPtest COMMAND ISPtest)



