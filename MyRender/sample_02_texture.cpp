#include "compile.h"
#ifdef SAMPLE_02

#include "renderhelp.h"

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
    Mat4x4f mat_model = matrixSetIdentity();	// ģ�ͱ任
    Mat4x4f mat_view = matrixSetLookat({ -0.7, 0, 1.5 }, { 0,0,0 }, { 0,0,1 });	// �������λ
    Mat4x4f mat_proj = matrixSetPerspective(3.1415926f * 0.5f, 800 / 600.0, 1.0, 500.0f);
    Mat4x4f mat_mvp = mat_model * mat_view * mat_proj;	// �ۺϱ任����

   // ���嶥������
    struct VertexAttrib { Vec4f pos; Vec2f texuv; } vs_input[3];

    // �������Ժ� varying �е��������� key
    const int VARYING_TEXUV = 0;

    // ������ɫ��
    rh.setVertexShader([&](int index, ShaderContext & output)->Vec4f {
        Vec4f pos = vs_input[index].pos * mat_mvp; // ����任�������
        output.varying_vec2f[VARYING_TEXUV] = vs_input[index].texuv;
        return pos;
        });

    // ������ɫ��
    rh.setPixelShader([&](ShaderContext& input) -> Vec4f {
        Vec2f coord = input.varying_vec2f[VARYING_TEXUV];	// ȡ����������
        return texture.sample2D(coord);		// �������������������ɫ
        });

    // 0 1
    // 3 2  �������������Σ����һ������
    VertexAttrib vertex[] = {
        { { 1, -1, -1, 1}, {0, 0} },
        { { 1,  1, -1, 1}, {1, 0} },
        { {-1,  1, -1, 1}, {1, 1} },
        { {-1, -1, -1, 1}, {0, 1} },
    };

    vs_input[0] = vertex[0];
    vs_input[1] = vertex[1];
    vs_input[2] = vertex[2];
    rh.drawPrimitive();

    vs_input[0] = vertex[2];
    vs_input[1] = vertex[3];
    vs_input[2] = vertex[0];
    rh.drawPrimitive();

    // �����ļ�
    rh.saveFile("output2.bmp");

    // �û�����ʾͼƬ
#if defined(_WIN32) || defined(WIN32)
    system("mspaint.exe output2.bmp");
#endif

    return 0;
}


#endif