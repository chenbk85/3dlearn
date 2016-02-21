# Direct3D Cartoon Outline Shader #

_keywords:Outlines,silhouette edge_

实现卡通剪影效果大概的原理是，先构造一个用退化的四边形表示原始网格所有边的退化网格。然后在着色脚本里将轮廓顶点计算出来，并进行反退化处理。由此得出的顶点可以构成原始网格的轮廓顶点。

_完整源码下载:
http://code.google.com/p/3dlearn/source/browse/trunk/DirectX/DragonBook1Code/Chapter+17/VS+Toon+2+With+Outlines/_

### 重描边 ###
对面片的三条边分别进行重描，重描的方式是用退化的四边形表示一条边。退化的四边形就是2个退化的三角形。

![http://3dlearn.googlecode.com/files/edge.png](http://3dlearn.googlecode.com/files/edge.png)
```
EdgeVertex A0, B0, C0, D0;

A0.position    = v0.position;
A0.normal      = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
A0.faceNormal1 = currentFaceNormal;
A0.faceNormal2 = adjFaceNormals[0];

B0.position    = v1.position;
B0.normal      = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
B0.faceNormal1 = currentFaceNormal;
B0.faceNormal2 = adjFaceNormals[0];

C0 = A0;
C0.normal = v0.normal;

D0 = B0;
D0.normal = v1.normal;

*edgeVertices = A0; ++edgeVertices;
*edgeVertices = B0; ++edgeVertices;
*edgeVertices = C0; ++edgeVertices;
*edgeVertices = D0; ++edgeVertices;	

```

### 重构网格顶点 ###
前面提到重秒边的方式是用蜕化的四边形表示一条边，这个四边形的顶点创建方法如下,4个顶点的坐标和原始顶点一致.这里可以看到 A0\C0\V0坐标一致，A0\C0只是区别在C0有完整的法线数据。

![http://3dlearn.googlecode.com/files/edgevertex.png](http://3dlearn.googlecode.com/files/edgevertex.png)

### 重构网格 ###
顶点格式
```
struct EdgeVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR3 faceNormal1;
	D3DXVECTOR3 faceNormal2;
};
```
声明此顶点格式
```
	D3DVERTEXELEMENT9 decl[] = 
	{
		// offsets in bytes
		{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
		{0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   1},
		{0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   2},
		D3DDECL_END()
	};

	HRESULT hr  = _device->CreateVertexDeclaration(decl, &_decl);

```

_source code_
http://code.google.com/p/3dlearn/source/browse/trunk/DirectX/DragonBook1Code/Chapter+17/VS+Toon+2+With+Outlines/silhouetteEdges.cpp

### 计算轮廓 ###
顶点着色脚本
http://code.google.com/p/3dlearn/source/browse/trunk/DirectX/DragonBook1Code/Chapter+17/VS+Toon+2+With+Outlines/toon.txt
```
float dot0 = dot(eyeToVertex, input.faceNormal1);
float dot1 = dot(eyeToVertex, input.faceNormal2);

// if cosines are different signs (positive/negative)
// than we are on a silhouette edge.  Do the signs
// differ?
if( (dot0 * dot1) < 0.0f )
{
	 // yes, then this vertex is on a silhouette edge, 
	 // offset the vertex position by some scalar in the
	 // direction of the vertex normal.
	 input.position += 0.1f * input.normal;
}

// transform to homogeneous clip space
output.position = mul(input.position, ProjMatrix);

// set outline color
output.diffuse = Black;
```

### 轮廓顶点算法 ###
算法思想:判断一条边是不是轮廓边，只需要用视线方向分别与轮廓的2个相邻2个面的法线点积，只要2个点积的结果正负相反，则此边是轮廓边。

### 顶点计算 ###
使用轮廓顶点算法即可找出所有轮廓顶点。考察对A0、C0如何进行脱化(un-degenerate)处理。
脱化处理很简单，就一步操作:
```
input.position += 0.1f * input.normal;
```
A0的法线是0，坐标是不会改变的，而C0的法线是原始顶点法线，则沿法线方向向外“发胖”一丁点。如此这般，原来被退化的四边形的4个顶点A0\B0\C0\D0 现在脱化了，变成了一个窄边。对于轮廓描边来说，这种处理很生动、很精准！
![http://3dlearn.googlecode.com/svn/trunk/DirectX/DragonBook1Code/Chapter%2017/VS%20Toon%202%20With%20Outlines/outlines.png](http://3dlearn.googlecode.com/svn/trunk/DirectX/DragonBook1Code/Chapter%2017/VS%20Toon%202%20With%20Outlines/outlines.png)

### 非轮廓点 ###
没有通过轮廓顶点算法的顶点，三角形均是退化三角形，结局大家都知道，Disappeared！

### 三个法线 ###
顶点又三个法线:normal、facenormal1、facenormal2，分别表示顶点的法线，顶点2个相邻面的法线。facenormal1、facenormal2 仅用于计算顶点是否是轮廓边的顶点；normal仅用将退化三角形脱化(un-degenerate)。

### 顶点的邻接面 ###
几何上顶点当然不只一个邻接面，但是在表示网格模型的时候，同一个几何意义上的顶点会有多份数据，计算机图像学领域的顶点都是归属于某个三角面的，将顶点与一个边绑定到一起。顶点的邻接面其实就是顶点边的邻接面。

### 画出轮廓 ###

|![http://3dlearn.googlecode.com/files/CartoonOutlineSolid.png](http://3dlearn.googlecode.com/files/CartoonOutlineSolid.png)|Solid|
|:--------------------------------------------------------------------------------------------------------------------------|:----|
|![http://3dlearn.googlecode.com/files/CartoonOutlinePoint.png](http://3dlearn.googlecode.com/files/CartoonOutlinePoint.png)|Point|