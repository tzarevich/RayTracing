#ifndef NOTION_H
#define NOTION_H
#pragma once

/* Add a sphere
�ڹ�Դ׷���������Ǿ�������һ������Ϊ����һ�����ߺ����ཻ�Ǻ����׵�
����Ĺ�ʽΪ��x*x + y*y + z*z = R*R
����������Բ��Ϊ(cx, cy, cz)����ô�ù�ʽ��Ϊ��(x - cx)*(x - cx) + (y - cy)*(y - cy) + (z - cz)*(z - cz) = R*R
�����������ʾԲ��C(cx, cy, cz)����p(x, y, z)������(p-C)
��dot(p-C, p-C) = (x - cx)*(x - cx) + (y - cy)*(y - cy) + (z - cz)*(z - cz)
��ô���幫ʽ��������ʾ���� dot(p-C, p-C) = R*R
����ĳһ���� p(t) = A + t*B,���Ƿ��������ཻ���ǿ���û��t����������ʽ
�� dot( (p(t)-C), (p(t)-C) ) = R*R,չ��Ϊ dot( (A + t*B - C), (A + t*B - C) ) = R*R
ȫ�������ߵõ���t*t*dot(B, B) + 2*t*dot(B, A-C) + dot(A-C, A-C) - R*R = 0
����һԪ���η��̣����Խ��t��ֵ��û��ʵ����˵�����ཻ����һ��ʵ��˵�����У�������ʵ��˵�����
*/

#endif