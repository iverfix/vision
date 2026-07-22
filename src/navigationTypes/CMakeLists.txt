add_library(NavigationTypes INTERFACE)

target_include_directories(NavigationTypes INTERFACE include)
target_link_libraries(NavigationTypes INTERFACE opencv::opencv Eigen3::Eigen)
