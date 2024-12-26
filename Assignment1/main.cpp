#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1,
        -eye_pos[2], 0, 0, 0, 1;

    view = translate * view;

    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.
    
    // 将角度从度转为弧度（如果传入的是度的话）
    float angle_in_radians = rotation_angle * MY_PI / 180.0f;

    // 创建绕Z轴的旋转矩阵
	Eigen::Matrix4f rotation_matrix = Eigen::Matrix4f::Identity(); // 初始化为单位矩阵
    rotation_matrix(0, 0) = cos(angle_in_radians);  // cos(θ)
    rotation_matrix(0, 1) = -sin(angle_in_radians); // -sin(θ)
    rotation_matrix(1, 0) = sin(angle_in_radians);  // sin(θ)
    rotation_matrix(1, 1) = cos(angle_in_radians);  // cos(θ)

	model = rotation_matrix * model;

    return model;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
    // Students will implement this function

    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the projection matrix for the given parameters.
    // Then return it.

    float top, bottom, left, right;
	top = zNear * tan(eye_fov / 2.0f);
	bottom = -top;
	right = top * aspect_ratio;
	left = -right;

	// 透视投影矩阵
	// 正交投影矩阵=缩放矩阵dot平移矩阵
	// 透视投影矩阵=正交投影矩阵dot挤压操作矩阵
	Eigen::Matrix4f S_ortho = Eigen::Matrix4f::Identity(); // 缩放矩阵
	S_ortho(0, 0) = 2.0f / (right - left);
	S_ortho(1, 1) = 2.0f / (top - bottom);
	S_ortho(2, 2) = 2.0f / (zNear - zFar);

	Eigen::Matrix4f T_ortho = Eigen::Matrix4f::Identity(); // 平移矩阵
	T_ortho(0, 3) = -(right + left) / 2.0f;
	T_ortho(1, 3) = -(top + bottom) / 2.0f;
	T_ortho(2, 3) = -(zNear + zFar) / 2.0f;

	Eigen::Matrix4f orthoMatrix = Eigen::Matrix4f::Identity(); // 正交投影矩阵
	orthoMatrix = S_ortho * T_ortho;

	Eigen::Matrix4f persp2ortho = Eigen::Matrix4f::Zero(); // 将透视空间转换为正交空间的矩阵
	persp2ortho(0, 0) = zNear;
	persp2ortho(1, 1) = zNear;
	persp2ortho(2, 2) = zNear + zFar;
	persp2ortho(2, 3) = -zNear * zFar;
	persp2ortho(3, 2) = -1;

	// 透视投影矩阵
	projection = orthoMatrix * persp2ortho;

    return projection;
}

Eigen::Matrix4f get_rotation(Vector3f axis, float angle) {
	// 构建一个函数，返回绕任意轴旋转的旋转矩阵
	// axis: 旋转轴，angle: 旋转角度

	// 归一化旋转轴
	axis.normalize();
	float x = axis[0], y = axis[1], z = axis[2]; // 旋转轴的三个分量
	float radian = angle * MY_PI / 180.0f; // 角度转弧度

	Eigen::Matrix3f K = Eigen::Matrix3f::Zero(); // 构建反对称矩阵
	K(0, 1) = -z; 
    K(0, 2) = y;
	K(1, 0) = z;
	K(1, 2) = -x;
	K(2, 0) = -y;
	K(2, 1) = x;

	// 计算旋转矩阵 R = I + sin(θ)K + (1 - cos(θ))K^2
    Eigen::Matrix3f I = Eigen::Matrix3f::Identity();
	Eigen::Matrix3f R = I + sin(radian) * K + (1 - cos(radian)) * K * K;

	// 将3x3的旋转矩阵转换为4x4的旋转矩阵
	Eigen::Matrix4f rotation_matrix = Eigen::Matrix4f::Identity();
	rotation_matrix.block<3, 3>(0, 0) = R;

	return rotation_matrix;

}

int main(int argc, const char** argv)
{
    float angle = 0;
    bool command_line = false;
    std::string filename = "output.png";

    if (argc >= 3) {
        command_line = true;
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
        else
            return 0;
    }

    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0, 0, 5};

    std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);

    int key = 0;
    int frame_count = 0;

    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;
    }

    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';

        if (key == 'a') {
            angle += 10;
        }
        else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;
}
