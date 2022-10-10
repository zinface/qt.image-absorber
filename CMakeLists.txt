
cmake_minimum_required(VERSION 3.5.1)

project(image-absorber LANGUAGES CXX VERSION 0.0.1)

include(cmake/SparkEnvConfig.cmake)
include(cmake/SparkMacrosConfig.cmake)
include(cmake/SparkFindLibraries.cmake)
include(cmake/SparkFindQt5Config.cmake)
include(cmake/SparkFindQt6Config.cmake)

# 资源文件路径
set(QRC_SOURCES "sources.qrc")

spark_add_executable_path(${PROJECT_NAME} src
    ${QRC_SOURCES}
)
target_link_qt5(${PROJECT_NAME})

include(cmake/SparkBuildGraphviz.cmake)
