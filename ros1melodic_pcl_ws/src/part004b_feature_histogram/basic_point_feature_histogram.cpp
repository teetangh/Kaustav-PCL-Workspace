// // Point Feature Histogram
// #include <pcl/point_types.h>
// #include <pcl/features/pfh.h>
// // Normal Estimation
// #include <pcl/visualization/cloud_viewer.h>
// #include <iostream>
// #include <pcl/io/io.h>
// #include <pcl/io/pcd_io.h>
// #include <pcl/features/integral_image_normal.h>

// int main(int argc, char const *argv[])
// {
//     // Load the point cloud
//     pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
//     pcl::io::loadPCDFile("../resources/table_scene_mug_stereo_textured.pcd", *cloud);

//     // Estimate the normals
//     pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);

//     pcl::IntegralImageNormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
//     ne.setNormalEstimationMethod(ne.AVERAGE_3D_GRADIENT);
//     ne.setMaxDepthChangeFactor(0.02f);
//     ne.setNormalSmoothingSize(10.0f);
//     ne.setInputCloud(cloud);
//     ne.compute(*normals);

//     // Create the PFH estimation class, and pass the input dataset+normals to it
//     pcl::PFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::PFHSignature125> pfh;
//     pfh.setInputCloud(cloud);
//     pfh.setInputNormals(normals);
//     // alternatively, if cloud is of tpe PointNormal, do pfh.setInputNormals (cloud);

//     // Create an empty kdtree representation, and pass it to the PFH estimation object.
//     // Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
//     pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
//     //pcl::KdTreeFLANN<pcl::PointXYZ>::Ptr tree (new pcl::KdTreeFLANN<pcl::PointXYZ> ()); -- older call for PCL 1.5-
//     pfh.setSearchMethod(tree);

//     // Output the datasets
//     pcl::PointCloud<pcl::PFHSignature125>::Ptr pfhs(new pcl::PointCloud<pcl::PFHSignature125>());

//     // Use all neighbors in a sphere of radius 5cm
//     // IMPORTANT: the radius used here has to be larger than the radius used to estimate the surface normals!!!
//     pfh.setRadiusSearch(0.05);

//     // Compute the features
//     pfh.compute(*pfhs);

//     // pfhs->size () should have the same size as the input cloud->size ()*

//     return 0;
// }
