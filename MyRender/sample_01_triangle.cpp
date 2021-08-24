#include "compile.h"
#ifdef SAMPLE_01

#include "renderhelp.h"

int main(void) {
    // 初始化渲染器和帧缓存大小
    RenderHelp rh(800, 600);

    const int VARYING_COLOR = 0;    // 定义一个 varying 的 key

    // 顶点数据，由 VS 读取，如有多个三角形，可每次更新 vs_input 再绘制
    struct { Vec4f pos; Vec4f color; } vs_input[3] = {
        { {  0.0,  0.7, 0.90, 1}, {1, 0, 0, 1} },
        { { -0.6, -0.2, 0.01, 1}, {0, 1, 0, 1} },
        { { +0.6, -0.2, 0.01, 1}, {0, 0, 1, 1} },
    };

    // 顶点着色器，初始化 varying 并返回坐标，
    // 参数 index 是渲染器传入的顶点序号，范围 [0, 2] 用于读取顶点数据
    // “外部变量访问方式说明符”可以是=或&，表示{}中用到的、定义在{}外面的变量在{}中是否允许被改变。=表示不允许，&表示允许。
    rh.setVertexShader([&](int index, ShaderContext& output) -> Vec4f {
        output.varying_vec4f[VARYING_COLOR] = vs_input[index].color;
        return vs_input[index].pos;		// 直接返回坐标
        });

    // 像素着色器，返回颜色
    rh.setPixelShader([&](ShaderContext& input) -> Vec4f {
        return input.varying_vec4f[VARYING_COLOR];
        });

    // 渲染并保存
    rh.drawPrimitive();
    rh.saveFile("output1.bmp");

    // 用画板显示图片
#if defined(_WIN32) || defined(WIN32)
    system("mspaint.exe output1.bmp");
#endif

    return 0;
}

#endif