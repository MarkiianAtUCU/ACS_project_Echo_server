cmake_minimum_required(VERSION 3.13)
project(ACS_project_Echo_server)

set(CMAKE_CXX_STANDARD 14)

set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREAD ON)

find_package(Boost REQUIRED COMPONENTS system thread)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})


add_executable(tester tester.cpp)

add_executable(async_echo_sample async_echo_sample.cpp)
target_link_libraries( async_echo_sample ${CMAKE_BOOST_LIBS_INIT} ${Boost_SYSTEM_LIBRARY}  )

add_executable(sync_echo  sync_echo.cpp)
target_link_libraries( sync_echo ${CMAKE_BOOST_LIBS_INIT} ${Boost_SYSTEM_LIBRARY}  )

add_executable(sync_echo2 sync_echo2.cpp)
target_link_libraries( sync_echo2 ${CMAKE_BOOST_LIBS_INIT} ${Boost_SYSTEM_LIBRARY}  )

add_executable(daytime daytime.cpp)
target_link_libraries( daytime  ${Boost_LIBRARIES}  )


#add_executable(async_echo  async_echo.cpp)
#target_link_libraries( async_echo ${CMAKE_BOOST_LIBS_INIT} ${Boost_SYSTEM_LIBRARY}  )

#add_executable(coroutine_echo  coroutine_echo.cpp)
#target_link_libraries( coroutine_echo ${CMAKE_BOOST_LIBS_INIT} ${Boost_SYSTEM_LIBRARY}  )

#set_target_properties(sync_echo PROPERTIES COMPILE_FLAGS  "-lboost_thread")
if(WIN32)
    target_link_libraries(async_echo_sample wsock32 ws2_32)
    target_link_libraries(sync_echo wsock32 ws2_32)
    target_link_libraries(sync_echo2 wsock32 ws2_32)
    target_link_libraries(daytime wsock32 ws2_32)

    #    target_link_libraries(async_echo wsock32 ws2_32)
#    target_link_libraries(coroutine_echo wsock32 ws2_32)
endif()