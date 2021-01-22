#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>

int main(int argc, char const *argv[])
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    //  ... read, pass in or create a point cloud ...

    if (pcl::io::loadPCDFile<pcl::PointXYZ>("../resources/test_pcd.pcd", *cloud) == -1)
    {
        PCL_ERROR("Couldn't read the file test_pcd.pcd \n");
        return (-1);
    }

    std::cout << "Loaded "
              << cloud->width * cloud->height
              << "data points from test_pcd.pcd with the following fields: "
              << std::endl;

    for (const auto &point : *cloud)
    {
        std::cout << " " << point.x
                  << " " << point.y
                  << " " << point.z << std::endl;
    }

    // Create the normal estimation class, and pass the input dataset to it
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
    ne.setInputCloud(cloud);

    // Create an empty kdtree representation, and pass it to the normal estimation object.
    // Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
    ne.setSearchMethod(tree);

    // Output dataset
    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(new pcl::PointCloud<pcl::Normal>);

    // Use all neighbours in a sphere of radius 3cm
    ne.setRadiusSearch(0.03);

    // Compute the features
    // cloud_normals->size () should have the same size as the input cloud->size ()
    ne.compute(*cloud_normals);

    // Visualize the normals
    pcl::visualization::PCLVisualizer viewer("PCL Viewer");
    viewer.setBackgroundColor(0.0, 0.0, 0.5);
    viewer.addPointCloudNormals<pcl::PointXYZ, pcl::Normal>(cloud, cloud_normals);

    while (!viewer.wasStopped())
        viewer.spinOnce();

    return 0;
}
