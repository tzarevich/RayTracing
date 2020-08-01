#ifndef NOTION_H
#define NOTION_H
#pragma once

/* Rays, a simple camera, and background 
所有的光线追踪都有一个光线类，以及一个计算式用来计算沿光线看某个点应该是什么颜色
将ray视为一个函数 : p(t) = A + t*B
这里：p是三维空间中的某条线上的一个点：A是光线的起始点；B是光线的方向；t是一个常量参数
根据t的取值，p在给定光线上移动

光线追踪器的核心就是从图像的像素点上发出光线并计算沿这些光线的方向看过去应该看到的颜色
其实就是计算人眼到像素点形成的这条光线，以及这条光线与图像的相交点和看到的相交点的颜色

线性混和一般式：blendedValue = (1 - t) * startValue + t * endValue; 0 < t < 1;
*/

#endif