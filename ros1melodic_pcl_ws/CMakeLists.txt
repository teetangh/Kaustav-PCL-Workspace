cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(kaustav_pcl_practice)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (pcd_write src/part001_writing_pcd_files/pcd_write.cpp)
target_link_libraries (pcd_write ${PCL_LIBRARIES})

add_executable (matrix_transform src/part002_matrix_transform/matrix_transform.cpp)
target_link_libraries (matrix_transform ${PCL_LIBRARIES})

# add_executable (custom_point src/part003_custom_point_data_types/custom_point.cpp)
# target_link_libraries (custom_point ${PCL_LIBRARIES})

add_executable (normal_estimation_all_points src/part004_feature_estimation/normal_estimation_all_points.cpp)
target_link_libraries (normal_estimation_all_points ${PCL_LIBRARIES})

# add_executable (normal_estimation_subset_points src/part004_feature_estimation/normal_estimation_subset_points.cpp)
# target_link_libraries (normal_estimation_subset_points ${PCL_LIBRARIES})

add_executable (normal_estimation_using_integral_image src/part004_feature_estimation/normal_estimation_using_integral_image.cpp)
target_link_libraries (normal_estimation_using_integral_image ${PCL_LIBRARIES})