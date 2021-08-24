#include "compile.h"

#ifdef SAMPLE_03

#include <iostream>

#include "renderhelp.h"

// ���嶥��ṹ
struct VertexAttrib { Vec3f pos; Vec2f uv; Vec3f color; };

// ������ɫ������
VertexAttrib vs_input[3];

// ģ��
VertexAttrib mesh[] = {
	{ {  1, -1,  1, }, { 0, 0 }, { 1.0f, 0.2f, 0.2f }, },
	{ { -1, -1,  1, }, { 0, 1 }, { 0.2f, 1.0f, 0.2f }, },
	{ { -1,  1,  1, }, { 1, 1 }, { 0.2f, 0.2f, 1.0f }, },
	{ {  1,  1,  1, }, { 1, 0 }, { 1.0f, 0.2f, 1.0f }, },
	{ {  1, -1, -1, }, { 0, 0 }, { 1.0f, 1.0f, 0.2f }, },
	{ { -1, -1, -1, }, { 0, 1 }, { 0.2f, 1.0f, 1.0f }, },
	{ { -1,  1, -1, }, { 1, 1 }, { 1.0f, 0.3f, 0.3f }, },
	{ {  1,  1, -1, }, { 1, 0 }, { 0.2f, 1.0f, 0.3f }, },
};

// �������Ժ� varying �е��������� key
const int VARYING_TEXUV = 0;
const int VARYING_COLOR = 1;

void draw_plane(RenderHelp& rh, int a, int b, int c, int d)
{
	mesh[a].uv.x = 0, mesh[a].uv.y = 0, mesh[b].uv.x = 0, mesh[b].uv.y = 1;
	mesh[c].uv.x = 1, mesh[c].uv.y = 1, mesh[d].uv.x = 1, mesh[d].uv.y = 0;

	vs_input[0] = mesh[a];
	vs_input[1] = mesh[b];
	vs_input[2] = mesh[c];
	rh.drawPrimitive();

	vs_input[0] = mesh[c];
	vs_input[1] = mesh[d];
	vs_input[2] = mesh[a];
	rh.drawPrimitive();
}

int main(void)
{
	RenderHelp rh(800, 600);

	// ����һ����������������ͼ��
	Bitmap texture(256, 256);
	for (int y = 0; y < 256; y++) {
		for (int x = 0; x < 256; x++) {
			int k = (x / 32 + y / 32) & 1;
			texture.setPixel(x, y, k ? 0xffffffff : 0xff3fbcef);
		}
	}

	// ����任����ģ�ͱ任��������任��͸�ӱ任
	Mat4x4f mat_model = matrixSetRotate(-1, -0.5, 1, 1);
	Mat4x4f mat_view = matrixSetLookat({ 3.5, 0, 0 }, { 0,0,0 }, { 0,0,1 });
	Mat4x4f mat_proj = matrixSetPerspective(3.1415926f * 0.5f, 800 / 600.0, 1.0, 500.0f);
	Mat4x4f mat_mvp = mat_model * mat_view * mat_proj;	// �ۺϱ任����

	// ������ɫ��
	rh.setVertexShader([&](int index, ShaderContext& output)->Vec4f {
		Vec4f pos = vs_input[index].pos.xyz1() * mat_mvp;
		output.varying_vec2f[VARYING_TEXUV] = vs_input[index].uv;
		output.varying_vec4f[VARYING_COLOR] = vs_input[index].color.xyz1();
		return pos;
		});

	// ������ɫ��
	rh.setPixelShader([&](ShaderContext& input) -> Vec4f {
		Vec2f coord = input.varying_vec2f[VARYING_TEXUV];	// ȡ����������
		Vec4f tc = texture.sample2D(coord);		// �������������������ɫ
		return tc;		// ��������
		});

	// ���ƺ���
	draw_plane(rh, 0, 1, 2, 3);
	draw_plane(rh, 7, 6, 5, 4);
	draw_plane(rh, 0, 4, 5, 1);
	draw_plane(rh, 1, 5, 6, 2);
	draw_plane(rh, 2, 6, 7, 3);
	draw_plane(rh, 3, 7, 4, 0);

	// ������
	rh.saveFile("output3.bmp");

	// �û�����ʾͼƬ
#if defined(_WIN32) || defined(WIN32)
	system("mspaint.exe output3.bmp");
#endif

	return 0;
}

#endif
