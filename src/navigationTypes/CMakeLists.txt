add_library(NavigationTypes INTERFACE)
add_library(Vision::NavigationTypes ALIAS NavigationTypes)

target_include_directories(NavigationTypes INTERFACE include)
target_link_libraries(NavigationTypes INTERFACE opencv::opencv Eigen3::Eigen)
