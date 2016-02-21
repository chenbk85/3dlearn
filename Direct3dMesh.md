

<a href='Hidden comment: 
This text will be removed from the rendered page.
'></a>


# Direct3d网格模型 #

## Why does rendering of an ID3DXMesh object slow down significantly after I define subsets? ##

Source:Direct3d sdk DirectX Frequently Asked Questions
You probably have not optimized the mesh after defining the face attributes. If you specify attributes and then call ID3DXMesh::DrawSubset(), this method must perform a search of the mesh for all faces containing the requested attributes. In addition, the rendered faces are likely in a random access pattern, thus not utilizing vertex cache. After defining the face attributes for your subsets, call the ID3DXMesh::Optimize or ID3DXMesh::OptimizeInPlace methods and specifying an optimization method of D3DXMESHOPT\_ATTRSORT or stronger. Note that for optimum performance you should optimize with the D3DXMESHOPT\_VERTEXCACHE flag, which will also reorder vertices for optimum vertex cache utilization. The adjacency array generated for a D3DX Mesh has three entries per face, but some faces may not have adjacent faces on all three edges. How is this encoded? Entries where there are no adjacent faces are encoded as 0xffffffff.

## 创建mesh ##

  * D3DXCreateMesh
  * D3DXCreateMeshFVF

## 格式 ##
Source: Direct3D sdk Performance Optimizations (Direct3D 9).
DirectX9\\windows\_graphics.chm::Performance\_Optimizations.htm\#Using\_Meshe

| **Vertices**|
|:------------|
| **Indices** |
| **Attribute Table** |
| **Attribute Buffer** |
| **Adjacency Buffer** |

### Vertices ###
顶点集

### Indices ###
索引集合

### Attribute Table ###
如果网格未优化，则不会有属性表。如果没有优化，
```
typedef struct _D3DXATTRIBUTERANGE
{
    DWORD AttribId;//! 子集ID
    DWORD FaceStart;
    DWORD FaceCount;
    DWORD VertexStart;
    DWORD VertexCount;
} D3DXATTRIBUTERANGE;
```

### Attribute Buffer ###
{三角形0所在的子集, 三角形1所在的子集,… }

### Adjacency Buffer ###
{三角形0的邻接三角形, 三角形1的邻接三角形,…}

### OptimizedMesh ###
Source:Direct3d sdk OptimizedMesh Sample


顶点声明
Source:
http://code.google.com/p/3dlearn/source/browse/trunk/DirectX/DragonBook1Code/Chapter%2017/VS%20Toon%202%20With%20Outlines/silhouetteEdges.cpp

按自己的格式格式创建顶点
```
struct EdgeVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR3 faceNormal1;
	D3DXVECTOR3 faceNormal2;
};

	_device->CreateVertexBuffer(
		_numVerts * sizeof(EdgeVertex),
		D3DUSAGE_WRITEONLY,
		0, // using vertex declaration
		D3DPOOL_MANAGED,
		&_vb,
		0);
```

创建一个顶点声明
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
hr = _device->CreateVertexDeclaration(decl, &_decl);

```

渲染的时候告诉Direct3D你的顶点声明
```
void SilhouetteEdges::render()
{
	_device->SetVertexDeclaration(_decl);
	_device->SetStreamSource(0, _vb, 0, sizeof(EdgeVertex));
	_device->SetIndices(_ib);

	_device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST, 0, 0, _numVerts, 0, _numFaces);
}
```