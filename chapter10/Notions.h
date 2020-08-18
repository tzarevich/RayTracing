#ifndef NOTIONS_H
#define NOTIONS_H
#pragma once

/* 可移动相机
为了获得任意视角，定义几个位置，把相机的位置定义为 lookfrom，视点定义为lookat
还有一点相机是可以旋转的，绕着相机到视点这条线旋转，所以为相机定义一个垂直向量，当作相机的中心轴
这个向量转动，那么相机也就跟着转动
将相机视作一个平面，那么这个平面一定垂直于视线方向，这个垂直向量可以任意取，然后投影到这个平面上
根据计算可以得出相机的方向
通过fov可以改变视域，即所能看到东西的多少，远近等
*/

#endif