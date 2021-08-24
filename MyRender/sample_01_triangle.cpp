#include "compile.h"
#ifdef SAMPLE_01

#include "renderhelp.h"

int main(void) {
    // ��ʼ����Ⱦ����֡�����С
    RenderHelp rh(800, 600);

    const int VARYING_COLOR = 0;    // ����һ�� varying �� key

    // �������ݣ��� VS ��ȡ�����ж�������Σ���ÿ�θ��� vs_input �ٻ���
    struct { Vec4f pos; Vec4f color; } vs_input[3] = {
        { {  0.0,  0.7, 0.90, 1}, {1, 0, 0, 1} },
        { { -0.6, -0.2, 0.01, 1}, {0, 1, 0, 1} },
        { { +0.6, -0.2, 0.01, 1}, {0, 0, 1, 1} },
    };

    // ������ɫ������ʼ�� varying ���������꣬
    // ���� index ����Ⱦ������Ķ�����ţ���Χ [0, 2] ���ڶ�ȡ��������
    // ���ⲿ�������ʷ�ʽ˵������������=��&����ʾ{}���õ��ġ�������{}����ı�����{}���Ƿ������ı䡣=��ʾ������&��ʾ����
    rh.setVertexShader([&](int index, ShaderContext& output) -> Vec4f {
        output.varying_vec4f[VARYING_COLOR] = vs_input[index].color;
        return vs_input[index].pos;		// ֱ�ӷ�������
        });

    // ������ɫ����������ɫ
    rh.setPixelShader([&](ShaderContext& input) -> Vec4f {
        return input.varying_vec4f[VARYING_COLOR];
        });

    // ��Ⱦ������
    rh.drawPrimitive();
    rh.saveFile("output1.bmp");

    // �û�����ʾͼƬ
#if defined(_WIN32) || defined(WIN32)
    system("mspaint.exe output1.bmp");
#endif

    return 0;
}

#endif