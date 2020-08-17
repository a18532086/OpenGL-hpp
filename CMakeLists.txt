# CMakeList.txt: My_Learning_Vulkan 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

link_directories (${CMAKE_SOURCE_DIR}/Lib)
include_directories (${CMAKE_SOURCE_DIR}/Externals)
include_directories (${CMAKE_SOURCE_DIR}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -NDEBUG")

project (OpenGL-hpp)

set(EXAMPLES
	test1
	)
set(COMMON_LIBS glad glfw3dll)

# 类的实现文件
file(GLOB HEADER_IMPL_FILES
	${CMAKE_SOURCE_DIR}/include/*.cpp)
foreach(EXAMPLE ${EXAMPLES})
	add_executable(${EXAMPLE} ${HEADER_IMPL_FILES} src/${EXAMPLE}/${EXAMPLE}.cpp)
	target_link_libraries(${EXAMPLE} ${COMMON_LIBS})
	set_property(TARGET ${EXAMPLE} PROPERTY WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	set_property(TARGET ${EXAMPLE} PROPERTY DEBUG_POSTFIX _d)
endforeach(EXAMPLE)

#



# TODO: 如有需要，请添加测试并安装目标。
