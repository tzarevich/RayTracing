#ifndef NOTION_H
#define NOTION_H
#pragma once

/* Add a sphere
在光源追踪器中人们经常会用一个球因为计算一个光线和球相交是很容易的
球体的公式为：x*x + y*y + z*z = R*R
而如果球体的圆心为(cx, cy, cz)，那么该公式变为：(x - cx)*(x - cx) + (y - cy)*(y - cy) + (z - cz)*(z - cz) = R*R
如果以向量表示圆心C(cx, cy, cz)到点p(x, y, z)，就是(p-C)
而dot(p-C, p-C) = (x - cx)*(x - cx) + (y - cy)*(y - cy) + (z - cz)*(z - cz)
那么球体公式用向量表示就是 dot(p-C, p-C) = R*R
对于某一光线 p(t) = A + t*B,它是否与球体相交就是看有没有t满足上述等式
即 dot( (p(t)-C), (p(t)-C) ) = R*R,展开为 dot( (A + t*B - C), (A + t*B - C) ) = R*R
全部移项到左边得到：t*t*dot(B, B) + 2*t*dot(B, A-C) + dot(A-C, A-C) - R*R = 0
这是一元二次方程，可以解出t的值，没有实根则说明不相交，有一个实根说明相切，有两个实根说明相割
*/

#endif