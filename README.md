# renderhelp.h

## 测试结果

三角形测试：

![](https://files.catbox.moe/f7rrzk.bmp)

纹理测试：

![](https://files.catbox.moe/rmn24x.bmp)

正方体测试：

![](https://files.catbox.moe/ovifcw.bmp)

## 数学库

**数学库：矢量定义**

矢量定义。

int_t 为一个结构的标注，可以理解为type/typedef的缩写，表示它是通过typedef定义的，而不是一种新的数据类型。因为跨平台，不同的平台会有不同的字长，所以利用预编译和typedef可以最有效的维护代码。

- int8_t      : typedef signed char;
- uint8_t    : typedef unsigned char;
- int16_t    : typedef signed short ;
- uint16_t  : typedef unsigned short ;
- int32_t    : typedef signed int;
- uint32_t  : typedef unsigned int;
- int64_t    : typedef signed  long long;
- uint64_t  : typedef unsigned long long;

size_t主要用于计数（例如数组下标），如sizeof函数返回值类型即为size_t。在不同位的机器中所占的位数也不同，size_t是无符号数，ssize_t是有符号数。

- 在32位机器中定义为：typedef  unsigned int size_t; （4个字节）
- 在64位机器中定义为：typedef  unsigned long size_t;（8个字节）

由于size_t是无符号数，因此，当变量有可能为负数时，必须使用ssize_t。

**数学库：矢量运算**

对向量计算的运算符进行重载。

**数学库：矢量函数**

向量特有的一些运算的函数。

**数学库：矩阵**

矩阵定义。

**数学库：矩阵运算**

对矩阵计算的运算符进行重载。

**数学库：矩阵函数**

矩阵特有的一些运算的函数，例如行列式求值和逆矩阵等等。

**工具函数**

abs、max、min、nearEqual、between等等。

类型别名也在这里定义，例如typedef Vector<2, float>  Vec2f;

## 3D 数学运算

**矢量转整数颜色**

(r << 16) | (g << 8) | b | (a << 24)

**平移变换**

我们选择左手坐标系，使用行向量，那么矩阵需要右乘这个行向量。这和opengl里的左乘不同，所以我们的矩阵相比opengl中学到的mvp矩阵进行了一个转置操作。

LearnOpenGL的变换一节中提到了”列主序“这个概念，让我困扰了很久，然后在 [Confusion between C++ and OpenGL matrix order (row-major vs column-major)](https://stackoverflow.com/questions/17717600/confusion-between-c-and-opengl-matrix-order-row-major-vs-column-major) 里解决了疑惑。一句话解释就是：你只需要考虑矩阵是左乘列向量还是右乘行向量，然后输入的矩阵也要正确，内存布局的问题没有任何担心的必要。

扯远了。总之，平移变换代码如下：

```
inline static Mat4x4f matrixSetTranslate(float x, float y, float z) {
    Mat4x4f m = matrixSetIdentity();
    m.m[3][0] = x;
    m.m[3][1] = y;
    m.m[3][2] = z;
    return m;
}
```

**缩放变换**

```
inline static Mat4x4f matrixSetScale(float x, float y, float z) {
    Mat4x4f m = matrixSetIdentity();
    m.m[0][0] = x;
    m.m[1][1] = y;
    m.m[2][2] = z;
    return m;
}
```

**旋转变换**

```
//具体公式见LearnOpenGL
//关于该矩阵的推导：https://zhuanlan.zhihu.com/p/56587491
inline static Mat4x4f matrixSetRotate(float x, float y, float z, float theta) {
    float qsin = (float)sin(theta * 0.5f);//还记得二倍角公式吗
    float qcos = (float)cos(theta * 0.5f);
    float w = qcos;
    Vec3f vec = vectorNormalize(Vec3f(x, y, z));
    x = vec.x * qsin;
    y = vec.y * qsin;
    z = vec.z * qsin;
    Mat4x4f m;
    m.m[0][0] = 1 - 2 * y * y - 2 * z * z;
    m.m[1][0] = 2 * x * y - 2 * w * z;
    m.m[2][0] = 2 * x * z + 2 * w * y;
    m.m[0][1] = 2 * x * y + 2 * w * z;
    m.m[1][1] = 1 - 2 * x * x - 2 * z * z;
    m.m[2][1] = 2 * y * z - 2 * w * x;
    m.m[0][2] = 2 * x * z - 2 * w * y;
    m.m[1][2] = 2 * y * z + 2 * w * x;
    m.m[2][2] = 1 - 2 * x * x - 2 * y * y;
    m.m[0][3] = m.m[1][3] = m.m[2][3] = 0.0f;
    m.m[3][0] = m.m[3][1] = m.m[3][2] = 0.0f;
    m.m[3][3] = 1.0f;
    return m;
}
```

**LookAt矩阵**

参考：[D3DXMatrixLookAtLH](https://docs.microsoft.com/zh-cn/windows/win32/direct3d10/d3d10-d3dxmatrixlookatlh)_

**透视投影矩阵**

参考：[D3DXMatrixPerspectiveFovLH](https://docs.microsoft.com/zh-cn/windows/win32/direct3d10/d3d10-d3dxmatrixperspectivefovlh)

## 位图库

**最重要的四个成员：** 

```
int32_t _w;
int32_t _h;
int32_t _pitch; // 每行字节数
uint8_t* _bits; // 字节数组
```

**画点**

```
inline void setPixel(int x, int y, uint32_t color) {
        if (x >= 0 && x < _w && y >= 0 && y < _h) {
            memcpy(_bits + y * _pitch + x * 4, &color, sizeof(uint32_t));
        }
    }
```

**画直线：DDA数值微分算法**

可以参考：[计算机图形学三：直线光栅化的数值微分算法,中点Brensenham算法和三角形的光栅化](https://zhuanlan.zhihu.com/p/144330664)

DDA算法是一个非常简单直观的算法。 首先当任何一条直线知道任意两点时都可以用 y = kx + b 来表示，其中k代表斜率，如果 |k| < 1，那么它的主要行进方向就是x轴，即x轴的变化要比y轴快，相反如果如果 |k| > 1，那么它的主要行进方向就是y轴，即y轴的变化要比x轴快。

**双线性插值**

注释比较详尽：

```
/*
    Linear interpolation(1D): lerp(x, v0, v1)= v0 + x(v1 - v0)
    Two helper lerps:
                       u0 = lerp(s, u00, u10)
                       u1 = lerp(s, u01, u11)
    Final vertical lerp, to get result:
                       f(x, y) = lerp(t, u0, u1)

    */
    // 双线性插值计算：给出四个点的颜色，以及坐标偏移，计算结果
    inline static uint32_t bilinearInterp(uint32_t tl, uint32_t tr,
        uint32_t bl, uint32_t br, int32_t distx, int32_t disty) {
        uint32_t f, r;
        int32_t distxy = distx * disty;
        int32_t distxiy = (distx << 8) - distxy;  /* distx * (256 - disty) */
        int32_t distixy = (disty << 8) - distxy;  /* disty * (256 - distx) */
        int32_t distixiy = 256 * 256 - (disty << 8) - (distx << 8) + distxy;
        // b
        r = (tl & 0x000000ff) * distixiy + (tr & 0x000000ff) * distxiy
            + (bl & 0x000000ff) * distixy + (br & 0x000000ff) * distxy;
        // g
        f = (tl & 0x0000ff00) * distixiy + (tr & 0x0000ff00) * distxiy
            + (bl & 0x0000ff00) * distixy + (br & 0x0000ff00) * distxy;
        r |= f & 0xff000000;
        // 防止溢出
        tl >>= 16; tr >>= 16; bl >>= 16; br >>= 16; r >>= 16;
        // r
        f = (tl & 0x000000ff) * distixiy + (tr & 0x000000ff) * distxiy
            + (bl & 0x000000ff) * distixy + (br & 0x000000ff) * distxy;
        r |= f & 0x00ff0000;
        // a
        f = (tl & 0x0000ff00) * distixiy + (tr & 0x0000ff00) * distxiy
            + (bl & 0x0000ff00) * distixy + (br & 0x0000ff00) * distxy;
        r |= f & 0xff000000;
        return r;
    }
```

**取纹理颜色和偏移量**

注释比较详尽：

```
inline uint32_t sampleBilinear(float x, float y) const {
        int32_t fx = (int32_t)(x * 0x10000);
        int32_t fy = (int32_t)(y * 0x10000);
        // 去小数位
        int32_t x1 = between(0, _w - 1, fx >> 16);
        int32_t y1 = between(0, _h - 1, fy >> 16);
        int32_t x2 = between(0, _w - 1, x1 + 1);
        int32_t y2 = between(0, _h - 1, y1 + 1);
        // 取少8个数量级的变化量
        int32_t dx = (fx >> 8) & 0xff;
        int32_t dy = (fy >> 8) & 0xff;
        if (_w <= 0 || _h <= 0) return 0;
        uint32_t c00 = getPixel(x1, y1);
        uint32_t c01 = getPixel(x2, y1);
        uint32_t c10 = getPixel(x1, y2);
        uint32_t c11 = getPixel(x2, y2);
        return bilinearInterp(c00, c01, c10, c11, dx, dy);
    }
```

## 软渲染

**着色器定义**

```
// 着色器上下文，由 VS 设置，再由渲染器按像素逐点插值后，供 PS 读取
struct ShaderContext {
    std::map<int, float> varying_float;    // 浮点数 varying 列表
    std::map<int, Vec2f> varying_vec2f;    // 二维矢量 varying 列表
    std::map<int, Vec3f> varying_vec3f;    // 三维矢量 varying 列表
    std::map<int, Vec4f> varying_vec4f;    // 四维矢量 varying 列表
};

// 顶点着色器：因为是 C++ 编写，无需传递 attribute，传个 0-2 的顶点序号
// 着色器函数直接在外层根据序号读取相应数据即可，最后需要返回一个坐标 pos
// 各项 varying 设置到 output 里，由渲染器插值后传递给 PS
typedef std::function<Vec4f(int index, ShaderContext& output)> VertexShader;


// 像素着色器：输入 ShaderContext，需要返回 Vec4f 类型的颜色
// 三角形内每个点的 input 具体值会根据前面三个顶点的 output 插值得到
typedef std::function<Vec4f(ShaderContext& input)> PixelShader;
```

**RenderHelp主要成员**

```
// 顶点结构体
    struct Vertex {
        ShaderContext context;    // 上下文
        float rhw;                // w 的倒数
        Vec4f pos;                // 坐标
        Vec2f spf;                // 浮点数屏幕坐标
        Vec2i spi;                // 整数屏幕坐标
    };

    Bitmap* _frame_buffer;    // 像素缓存
    float** _depth_buffer;    // 深度缓存

    int _fb_width;            // frame buffer 宽度
    int _fb_height;           // frame buffer 高度
    uint32_t _color_fg;       // 前景色：画线时候用
    uint32_t _color_bg;       // 背景色：Clear 时候用

    Vertex _vertex[3];        // 三角形的三个顶点

    int _min_x;               // 三角形外接矩形
    int _min_y;
    int _max_x;
    int _max_y;

    bool _render_frame;       // 是否绘制线框
    bool _render_pixel;       // 是否填充像素

    VertexShader _vertex_shader;
    PixelShader _pixel_shader;
```

**判断左上边**

Top-Left Fill Rule就是说当一个像素刚好压在三角形边上的时候，只有这条边在三角形的左边，或者上面的时候，才判定这个像素被三角形覆盖。

上边很好判断，如果有一条边是水平的，且边的两个顶点都高于第三个顶点，就是上边。左边则是指不水平的，且在三角形左边的边。一个三角形可以有1个或者2个左边。更具体的解释上面的链接说的很清楚。

因为三角形顶点的方向是一定的（顺时针或者逆时针），所以一条边在左边或者是右边只比较边的两个顶点的高度即可。

我们的软渲染器是左手坐标系，三角形顶点都是顺时针，因此大顶点的y值也比小顶点大，那就说明这条边是左边。

```
// 判断一条边是不是三角形的左上边 (Top-Left Edge)
    inline bool isTopLeft(const Vec2i& a, const Vec2i& b) {
        return ((a.y == b.y) && (a.x < b.x)) || (a.y > b.y);
    }
```

**软渲染管线**

对于每个顶点的初始化：清空上下文 varying 列表（map.clear()）→运行**顶点着色器**，返回顶点坐标→裁剪→将坐标**归一化**，注意保存1/w到rhw，之后会用到→计算**整数屏幕坐标**，y反向映射→更新**外接矩形**范围

↓

**绘制线框**

↓

根据叉乘**判断三角形顺逆时针**，如果是逆时针就调换顶点顺序

↓

**判断左上边**

↓

迭代三角形外接矩形的所有点：利用叉乘**计算每个点是否在三角形内部或左上边**→利用叉乘**计算出重心坐标**，并对1/w进行插值→利用1/w进行**深度测试**（注：A w-based depth buffer, on the other hand, is often more evenly distributed between the near and far clip planes than a z-buffer. The key benefit is that the ratio of distances for the far and near clipping planes is no longer an issue. This allows applications to support large maximum ranges, while still getting relatively accurate depth buffering close to the eye point. A w-based depth buffer isn't perfect, and can sometimes exhibit hidden surface artifacts for near objects. Another drawback to the w-buffered approach is related to hardware support: w-buffering isn't supported as widely in hardware as z-buffering.）→**透视矫正**重心坐标（参考：[TC130-图形学硬件拾遗(一)](https://zhuanlan.zhihu.com/p/371469482)）→**插值**→执行**像素着色器**

↓

绘制线框，**再画一次避免覆盖**

这样我们的软渲染器就大功告成了。之后的测试文件就不一一详解了。