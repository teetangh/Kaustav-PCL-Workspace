#include <iostream>
#include <pcl/io/pcd_io.h>   // PCD IO Operations
#include <pcl/point_types.h> // Point Type structures

int main(int argc, char const *argv[])
{
    pcl::PointCloud<pcl::PointXYZ> cloud;

    // Fill the cloud points
    cloud.width = 5;
    cloud.height = 1;
    cloud.is_dense = false;
    cloud.resize(cloud.width * cloud.height);

    // fill in the PointCloud structure with random point values, and set the appropriate parameters (width, height, is_dense).
    for (auto &point : cloud)
    {
        point.x = 1024 * rand() / (RAND_MAX + 1.0f);
        point.y = 1024 * rand() / (RAND_MAX + 1.0f);
        point.z = 1024 * rand() / (RAND_MAX + 1.0f);
    }

    // saves the PointCloud data to disk into a file called test_pcd.pcd
    pcl::io::savePCDFileASCII("test_pcd.pcd", cloud);
    std::cerr << "Saved" << cloud.size() << "data points to test_pcd.pcd..." << std::endl;

    for (const auto &point : cloud)
        std::cerr << " " << point.x << " " << point.y << " " << point.z << std::endl;

    return 0;
}
