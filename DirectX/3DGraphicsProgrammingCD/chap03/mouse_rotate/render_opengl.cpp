﻿#include <windows.h>
// Standard OpenGL header
#include <GL/gl.h>

#include "Gut.h"
#include "render_data.h"

static Matrix4x4 g_view_matrix;

bool InitResourceOpenGL(void)
{
	// 計算出一個可以轉換到鏡頭座標系的矩陣
	g_view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// 投影矩陣
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(90.0f, 1.0f, 1.0f, 100.0f);
	// 設定視角轉換矩陣
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);
	//glShadeModel(GL_FLAT);

	return true;
}

bool ReleaseResourceOpenGL(void)
{
	// 沒事做
	return true;
}

// 使用OpenGL來繪圖
void RenderFrameOpenGL(void)
{
	// 清除畫面
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// 設定好GPU要去哪讀取頂點座標資料
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex_VC), &g_vertices[0].m_Position);
	// 設定好GPU要去哪讀取頂點顏色資料
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex_VC), &g_vertices[0].m_RGBA);
	// 設定要變更GL_MODELVIEW矩陣
	glMatrixMode(GL_MODELVIEW);	

	// 設定轉換矩陣
	Matrix4x4 world_view_matrix = g_object_matrix * g_view_matrix;
	glLoadMatrixf( (float *) &world_view_matrix);
	// 畫出金字塔的8條邊線
	glDrawElements(
		GL_TRIANGLES, // 指定所要畫的基本圖形種類
		18, // 有幾個索引值
		GL_UNSIGNED_SHORT, // 索引值的型態
		g_indices // 索引值陣列
		);

	// 把背景backbuffer的畫面呈現出來
	GutSwapBuffersOpenGL();
}
