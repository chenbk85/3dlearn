//
// Generated by Microsoft (R) HLSL Shader Compiler 9.22.949.2248
//
//
//   fxc c:\3DGraphicsProgramming\Projects\shaders\vertex_lighting_dx10.shader
//    /Tps_4_0 /EPS /Zi /Fcvertex_lighting_dx10.ps.asm
//
//
//
// Input signature:
//
// Name             Index   Mask Register SysValue Format   Used
// ---------------- ----- ------ -------- -------- ------ ------
// SV_POSITION          0   xyzw        0      POS  float       
// COLOR                0   xyzw        1     NONE  float   xyzw
//
//
// Output signature:
//
// Name             Index   Mask Register SysValue Format   Used
// ---------------- ----- ------ -------- -------- ------ ------
// SV_Target            0   xyzw        0   TARGET  float   xyzw
//
ps_4_0
dcl_input_ps linear v1.xyzw
dcl_output o0.xyzw
mov o0.xyzw, v1.xyzw
ret 
// Approximately 2 instruction slots used
