#include <limits>
#include <fstream>
#include <vector>
#include <Eigen/Core>
#include <pcl/memory.h>
#include <pcl/pcl_macros.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/fpfh.h>
#include <pcl/registration/ia_ransac.h>

class FeatureCloud
{
public:
	// A bit of shorthand
	typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;
	typedef pcl::PointCloud<pcl::Normal> SurfaceNormal;
	typedef pcl::PointCloud<pcl::FPFHSignature33> LocalFeatures;
	typedef pcl::Search::KdTree<pcl::PointXYZ> SearchMethod;

	FeatureCloud() : search_method_xyz_(new SearchMethod), normal_radius_(0.02f), feature_radius_(0.02f)
	{
	}

	~FeatureCloud() {}

	// Process the given cloud
	void setInputCloud(PointCloud::Ptr xyz)
	{
		xyz_ = xyz;
		processInput();
	}

	// Load and process the cloud in the given PCD file
	void loadInputCloud(const std::string &pcd_file)
	{
		xyz_ = PointCloud::Ptr(new PointCloud);
		pcl::io::loadPCDFile(pcd::file, *xyz);
		processInput();
	}

	// Get a poninter to the cloud 3D points
	Pointcloud::Ptr;
	getPointCloud() const
	{
		return (xyz_);
	}

	// Get a pointer to the cloud of 3D surface normals
	SurfaceNormals::Ptr getSurfaceNormals() const
	{
		return (features_);
	}

protected:
	// Compute the surface normals and loical features
	void processInput()
	{
		computeSurfaceNormals();
		computeSurfaceNormals();
	}

	// Compute the suface normals
	void computeSurfaceNormals()
	{
		normals_ = SurfaceNormals::Ptr(new SurfaceNormals);

		pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> norm_est;
		norm_est.setInputCloud(xyz_);
		norm_est.setSearchMethod(search_method_xyz_);
		norm_est.setRadiusSearch(normal_radius_);
		norm_est.compute(*normals);
	}

	// Compute the local feature descriptors
	void computeLocalFeatures()
	{
		features_ = LocalFeatures::Ptr(new LocalFeatures);

		pcl::FPFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::FPFHSignature33> fpfh_est : fpfh_est.setInputCloud(xyz_);
		fpfh_est.setInputNormals(normals_);
	}
};