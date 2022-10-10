
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

include(cmake/SparkDesktopMacros.cmake)
# 内容默认应用名称: Name=@PROJECT_NAME@ 与项目名称相同
spark_desktop_macros(
    "image-absorber" # 应用名称: Name=
    "图片吸收器" # 应用名称: Name[zh_CN]=
    "图片吸收器" # 应用说明: Comment=
    "Application" # 应用类型: Type=
    "/usr/bin/image-absorber" # 执行程序: Exec=
    "/usr/share/image-absorber/icon.png" # 图标路径: Icon=
    "" # 应用分类: Category=
)
install(FILES ${CMAKE_BINARY_DIR}/image-absorber.desktop
    DESTINATION /usr/share/applications)

install(TARGETS image-absorber
    DESTINATION /usr/bin)
install(FILES resources/icon.png
    DESTINATION /usr/share/image-absorber)

find_package(DebPackage PATHS ${CMAKE_SOURCE_DIR})
add_package_descript(cmake/package-deb.descript)
