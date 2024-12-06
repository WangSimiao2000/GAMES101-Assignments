#include<cmath>
#include<Eigen/Core>
#include<Eigen/Dense>
#include<iostream>

#define M_PI 3.14159265358979323846

int main(){    
    /*
    // Basic Example of cpp
    std::cout << "Example of cpp \n";
    float a = 1.0, b = 2.0;
    std::cout << a << std::endl;
    std::cout << a/b << std::endl;
    std::cout << std::sqrt(b) << std::endl;
    std::cout << std::acos(-1) << std::endl;
    std::cout << std::sin(30.0/180.0*acos(-1)) << std::endl;

    // Example of vector
    std::cout << "Example of vector \n";
    // vector definition
    Eigen::Vector3f v(1.0f,2.0f,3.0f);
    Eigen::Vector3f w(1.0f,0.0f,0.0f);
    // vector output
    std::cout << "Example of output \n";
    std::cout << v << std::endl;
    // vector add
    std::cout << "Example of add \n";
    std::cout << v + w << std::endl;
    // vector scalar multiply
    std::cout << "Example of scalar multiply \n";
    std::cout << v * 3.0f << std::endl;
    std::cout << 2.0f * v << std::endl;

    // Example of matrix
    std::cout << "Example of matrix \n";
    // matrix definition
    Eigen::Matrix3f i,j;
    i << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
    j << 2.0, 3.0, 1.0, 4.0, 6.0, 5.0, 9.0, 7.0, 8.0;
    // matrix output
    std::cout << "Example of output \n";
    std::cout << i << std::endl;
    // matrix add i + j
    // matrix scalar multiply i * 2.0
    // matrix multiply i * j
    // matrix multiply vector i * v
    */
    
    
	// 向量点乘及几何意义
	Eigen::Vector3f a(1.0f, 2.0f, 3.0f);
	Eigen::Vector3f b(0.0f, 1.0f, 2.0f);
	std::cout << "a dot b = " << a.dot(b) << std::endl;
    std::cout << "|a| = " << a.norm() << std::endl;
    std::cout << "|b| = " << b.norm() << std::endl;
	std::cout << "cos(a,b) = " << a.dot(b) / (a.norm() * b.norm()) << std::endl;
    
	std::cout << "\n";

    // 矩阵加减、数乘、矩阵乘法、矩阵乘向量
    Eigen::Matrix3f m1;
    Eigen::Matrix3f m2;
    m1 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    m2 << 1, 0, 0, 0, 1, 0, 0, 0, 1;
    Eigen::Vector3f v1(1.0f, 2.0f, 3.0f);
	std::cout << "m1 = \n" << m1 << std::endl;
	std::cout << "m2 = \n" << m2 << std::endl;
	std::cout << "v1 = \n" << v1 << std::endl;
    std::cout << "m1 + m2 = \n" << m1 + m2 << std::endl;
    std::cout << "m1 - m2 = \n" << m1 - m2 << std::endl;
    std::cout << "m1 * 2 = \n" << m1 * 2 << std::endl;
    std::cout << "m1 * m2 = \n" << m1 * m2 << std::endl;
    std::cout << "m1 * v1 = \n" << m1 * v1 << std::endl;

    std::cout << "\n";

    // 点的旋转, 平移
    // 给定一个点`P=(2,1)`,将该点绕原点先逆时针旋转`45◦`，再平移`(1,2)`,计算出变换后点的坐标(要求用齐次坐标进行计算)
	// 定义点P
    Eigen::Vector3f p(2.0f, 1.0f, 1.0f);
	// 旋转矩阵
	Eigen::Matrix3f r;
	r << cos(M_PI / 4), -sin(M_PI / 4), 0, sin(M_PI / 4), cos(M_PI / 4), 0, 0, 0, 1;
	// 平移矩阵
	Eigen::Matrix3f t;
	t << 1, 0, 1, 0, 1, 2, 0, 0, 1;
	// 计算变换后的点
    std::cout << "p = \n" << p << std::endl;
    std::cout << "r = \n" << r << std::endl;
    std::cout << "t = \n" << t << std::endl;
    std::cout << "t * r * p = \n" << t * r * p << std::endl;

    return 0;
}