#ifndef NOTIONS_H
#define NOTIONS_H

/* 绝缘材料
电解质和绝缘体不仅反射光还会折射光，这里我们只会随机选中某一个条件
折射定律：n * sin(t) = n'*sin(t'); n 和 n'都是折射系数，属于常量
当光照射到某一具有很大折射系数的物体上时，上述定律不起作用，因为t'会为0，那么就没有折射，只有反射

由公式可以计算折射角：1 - cos(t')^2 = r*r*(1 - cos(t)^2),其中r = n/n', cos(t) = Dot(n, normal)/|n|*|normal| = Dot(n, normal)/1*1
所以 cos(t')^2 = 1 - r*r*(1 - Dot^2);根据折射角大小来决定是否存在折射
*/

#endif