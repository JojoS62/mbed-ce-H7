#include "display_ltdc.h"
#include "sdram.h"

#define LCD_NUM_LAYERS  1

#define	ColorMode_0   LTDC_PIXEL_FORMAT_RGB565
//#define	ColorMode_0   LTDC_PIXEL_FORMAT_ARGB1555
//#define	ColorMode_0    LTDC_PIXEL_FORMAT_ARGB4444
//#define	ColorMode_0   LTDC_PIXEL_FORMAT_RGB888
//#define	ColorMode_0   LTDC_PIXEL_FORMAT_ARGB8888

#define LTDC_R0_PIN						GPIO_PIN_15
#define	LTDC_R0_PORT					GPIOI

#define LTDC_R1_PIN						GPIO_PIN_0
#define	LTDC_R1_PORT					GPIOJ

#define LTDC_G0_PIN						GPIO_PIN_7
#define	LTDC_G0_PORT					GPIOJ

#define LTDC_G1_PIN						GPIO_PIN_8
#define	LTDC_G1_PORT					GPIOJ

#define LTDC_B0_PIN						GPIO_PIN_12
#define	LTDC_B0_PORT					GPIOJ

#define LTDC_B1_PIN						GPIO_PIN_13
#define	LTDC_B1_PORT					GPIOJ

#define LCD_Backlight_PIN				GPIO_PIN_6
#define	LCD_Backlight_PORT				GPIOH
#define GPIO_LDC_Backlight_CLK_ENABLE   __HAL_RCC_GPIOH_CLK_ENABLE()

#define	LCD_Backlight_OFF		        HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_RESET);	// 关闭背光
#define LCD_Backlight_ON		        HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_SET);		// 开启背光

#define HBP  80	// 根据屏幕的手册进行设置
#define VBP  40
#define HSW  1
#define VSW  1
#define HFP  200
#define VFP  22

// FK750M5-XBH6 核心板 使用的是外部SDRAM作为显存，起始地址0xC0000000
// 显存所需空间 = 分辨率 * 每个像素所占字节数，例如 800*480的屏，使用16位色（RGB565或者AEGB1555），需要显存 800*480*2 = 768000 字节

#define LCD_Width     		800						//	LCD的像素长度
#define LCD_Height    		480						//	LCD的像素宽度
#define LCD_MemoryAdd   	SDRAM_BANK_ADDR 		//	显存的起始地址  

// 显示方向参数
// 使用示例：LCD_DisplayDirection(Direction_H) ，设置屏幕横屏显示
// 使用示例：LCD_DisplayDirection(Direction_V) ，设置屏幕竖直显示

#define	Direction_H	0		//LCD横屏显示
#define	Direction_V	1		//LCD竖屏显示

/*---------------------------------------- 常用颜色 ------------------------------------------------------

 1. 这里为了方便用户使用，定义的是32位颜色，然后再通过代码自动转换成对应颜色格式所需要的的颜色
 2. 32位的颜色中，从高位到低位分别对应 A、R、G、B  4个颜色通道，其中A表示透明通道
 3. 最多可设置255级透明色，ff表示不透明，0表示完全透明
 4. 除非使用ARGB1555和ARGB8888等支持透明色的颜色格式，不然透明色不起作用，其中ARGB1555仅支持一位
	 透明色，即仅有透明和不透明两种状态，ARGB4444有16级透明度，ARGB8888支持255级透明度
 5. 用户可以在电脑用调色板获取24位RGB颜色，然后再补充透明通道得到32位的颜色，再将此32位颜色输入
	 LCD_SetColor()或LCD_SetBackColor()就可以显示出相应的颜色。 
 6. 使用示例：纯蓝色的RGB值为0x0000FF，如果不需要透明色，则对应的32位颜色值为 0xff0000FF
 7. 以下定义的颜色都设置为不透明，用户可根据需求自行定义对应的颜色								*/



// 设置变量显示时多余位补0还是补空格
// 只有 LCD_DisplayNumber() 显示整数 和 LCD_DisplayDecimals()显示小数 这两个函数用到
// 使用示例： LCD_ShowNumMode(Fill_Zero) 设置多余位填充0，例如 123 可以显示为 000123
//
#define  Fill_Zero  0		//填充0
#define  Fill_Space 1		//填充空格


#if ( ColorMode_0 == LTDC_PIXEL_FORMAT_RGB565 || ColorMode_0 == LTDC_PIXEL_FORMAT_ARGB1555 || ColorMode_0 ==LTDC_PIXEL_FORMAT_ARGB4444 )
#define BytesPerPixel_0		2		//16位色模式每个像素占2字节
#elif ColorMode_0 == LTDC_PIXEL_FORMAT_RGB888
#define BytesPerPixel_0		3		//24位色模式每个像素占3字节
#else
#define BytesPerPixel_0		4		//32位色模式每个像素占4字节
#endif

#if LCD_NUM_LAYERS == 2

#if ( ColorMode_1 == LTDC_PIXEL_FORMAT_RGB565 || ColorMode_1 == LTDC_PIXEL_FORMAT_ARGB1555 || ColorMode_1 == LTDC_PIXEL_FORMAT_ARGB4444 )
#define BytesPerPixel_1		2	//16位色模式每个像素占2字节
#elif ColorMode_1 == LTDC_PIXEL_FORMAT_RGB888
#define BytesPerPixel_1		3	//24位色模式每个像素占3字节
#else
#define BytesPerPixel_1		4	//32位色模式每个像素占4字节
#endif

#define LCD_MemoryAdd_OFFSET   LCD_Width * LCD_Height * BytesPerPixel_0 	 //第二层的显存的偏移地址 

#endif

DisplayLTDC::DisplayLTDC()
{
}

void DisplayLTDC::LCD_Init()
{
    LTDC_LayerCfgTypeDef pLayerCfg = {0};		    // layer0 相关参数
    __HAL_RCC_DMA2D_CLK_ENABLE();					// 使能DMA2D时钟

    hltdc.Instance 	        = LTDC;
    hltdc.Init.HSPolarity   = LTDC_HSPOLARITY_AL;	// 低电平有效
    hltdc.Init.VSPolarity   = LTDC_VSPOLARITY_AL;   // 低电平有效
    hltdc.Init.DEPolarity   = LTDC_DEPOLARITY_AL;   // 低电平有效，要注意的是，很多面板都是高电平有效，但是750需要设置成低电平才能正常显示
    hltdc.Init.PCPolarity   = LTDC_PCPOLARITY_IPC;  // 正常时钟信号

    hltdc.Init.HorizontalSync 		= HSW - 1;									// 根据屏幕设置参数即可
    hltdc.Init.VerticalSync 		= VSW	-1 ;
    hltdc.Init.AccumulatedHBP		= HBP + HSW -1;
    hltdc.Init.AccumulatedVBP 		= VBP + VSW -1;
    hltdc.Init.AccumulatedActiveW = LCD_Width  + HSW + HBP -1;
    hltdc.Init.AccumulatedActiveH = LCD_Height + VSW + VBP -1;
    hltdc.Init.TotalWidth 			= LCD_Width  + HSW + HBP + HFP - 1;
    hltdc.Init.TotalHeigh 			= LCD_Height + VSW + VBP + VFP - 1;

    hltdc.Init.Backcolor.Red 		= 0;	// 初始背景色，R
    hltdc.Init.Backcolor.Green 	= 0;  // 初始背景色，G
    hltdc.Init.Backcolor.Blue 		= 0;	// 初始背景色，B

    HAL_LTDC_Init(&hltdc);	// 初始化LTDC参数

    /*---------------------------------- layer0 显示配置 --------------------------------*/

    pLayerCfg.WindowX0 			= 0;										// 水平起点
    pLayerCfg.WindowX1 			= LCD_Width;							// 水平终点
    pLayerCfg.WindowY0 			= 0;										// 垂直起点
    pLayerCfg.WindowY1 			= LCD_Height;							// 垂直终点
    pLayerCfg.ImageWidth 		= LCD_Width;                     // 显示区域宽度
    pLayerCfg.ImageHeight 		= LCD_Height;                    // 显示区域高度
    pLayerCfg.PixelFormat 		= ColorMode_0;							// 颜色格式

    // 配置 layer0 的恒定透明度，最终写入 LTDC_LxCACR 寄存器
    //	需要注意的是，这个参数是直接配置整个 layer0 的透明度，这里设置为255即不透明
    pLayerCfg.Alpha 				= 255;									// 取值范围0~255，255表示不透明，0表示完全透明

    // 设置 layer0 的层混合系数，最终写入 LTDC_LxBFCR 寄存器
    // 该参数用于设置 layer0 和 底层背景 之间的颜色混合系数，计算公式为 ：
    // 混合后的颜色 =  BF1 * layer0的颜色 + BF2 * 底层背景的颜色
    // 如果 layer0 使用了透明色，则必须配置成 LTDC_BLENDING_FACTOR1_PAxCA 和 LTDC_BLENDING_FACTOR2_PAxCA，否则ARGB中的A通道不起作用
    //	更多的介绍可以查阅 参考手册关于 LTDC_LxBFCR 寄存器的介绍
    pLayerCfg.BlendingFactor1 	= LTDC_BLENDING_FACTOR1_CA;		// 混合系数1
    pLayerCfg.BlendingFactor2 	= LTDC_BLENDING_FACTOR2_CA;      // 混合系数2

    pLayerCfg.FBStartAdress 	= LCD_MemoryAdd;                 // 显存地址

    // 配置 layer0 的初始默认颜色，包括A,R,G,B 的值 ，最终写入 LTDC_LxDCCR 寄存器
    pLayerCfg.Alpha0 				= 0;			// 初始颜色，A
    pLayerCfg.Backcolor.Blue 	= 0;        //	初始颜色，R
    pLayerCfg.Backcolor.Green 	= 0;        //	初始颜色，G
    pLayerCfg.Backcolor.Red 	= 0;			//	初始颜色，B

    HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0);		// 配置layer0

#if ( ( ColorMode_0 == LTDC_PIXEL_FORMAT_RGB888 )||( ColorMode_0 == LTDC_PIXEL_FORMAT_ARGB8888 ) ) // 判断是否使用24位或者32位色

// 因为750每个通道的低位都是采用伪随机抖动输出，如果不开启颜色抖动，则无法正常显示24位或者32位色

    HAL_LTDC_EnableDither(&hltdc); // 开启颜色抖动

#endif


    /*---------------------------------- layer1 显示配置 --------------------------------*/

#if ( LCD_NUM_LAYERS == 2 )	//如果定义了双层

    LTDC_LayerCfgTypeDef pLayerCfg1 = {0};

    pLayerCfg1.WindowX0 				= 0;							// 水平起点
    pLayerCfg1.WindowX1 				= LCD_Width;				// 水平终点
    pLayerCfg1.WindowY0 				= 0;							// 垂直起点
    pLayerCfg1.WindowY1 				= LCD_Height;				// 垂直终点
    pLayerCfg1.ImageWidth 			= LCD_Width;         	// 显示区域宽度
    pLayerCfg1.ImageHeight 			= LCD_Height;        	// 显示区域高度
    pLayerCfg1.PixelFormat 			= ColorMode_1;				// 颜色格式，layer1 应配置为带有透明色的格式，例如ARGB8888或ARGB1555

// 配置 layer1 的恒定透明度，最终写入 LTDC_LxCACR 寄存器
//	需要注意的是，这个参数是直接配置整个 layer1 的透明度，这里设置为255即不透明
    pLayerCfg1.Alpha 					= 255;			// 取值范围0~255，255表示不透明，0表示完全透明

// 设置 layer1 的层混合系数，最终写入 LTDC_LxBFCR 寄存器
// 该参数用于设置 layer1 和 (layer0+背景）之间的颜色混合系数，计算公式为 ：
// 混合后的颜色 =  BF1 * layer1的颜色 + BF2 * (layer0+背景混合后的颜色）
// 如果 layer1 使用了透明色，则必须配置成 LTDC_BLENDING_FACTOR1_PAxCA 和 LTDC_BLENDING_FACTOR2_PAxCA，否则ARGB中的A通道不起作用
//	更多的介绍可以查阅 参考手册关于 LTDC_LxBFCR 寄存器的介绍
    pLayerCfg1.BlendingFactor1 	= LTDC_BLENDING_FACTOR1_PAxCA;			// 混合系数1
    pLayerCfg1.BlendingFactor2 	= LTDC_BLENDING_FACTOR2_PAxCA;      	// 混合系数2

    pLayerCfg1.FBStartAdress 		= LCD_MemoryAdd + LCD_MemoryAdd_OFFSET; // 显存地址


// 配置layer1 的初始默认颜色，包括A,R,G,B 的值 ，最终写入 LTDC_LxDCCR 寄存器
    pLayerCfg1.Alpha0 				= 0;				// 初始颜色，A
    pLayerCfg1.Backcolor.Red 		= 0;				//	初始颜色，R
    pLayerCfg1.Backcolor.Green 	= 0;           //	初始颜色，G
    pLayerCfg1.Backcolor.Blue 		= 0;           //	初始颜色，B

    HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1);	// 初始化 layer1 的配置

#if ( ( ColorMode_1 == LTDC_PIXEL_FORMAT_RGB888 )||( ColorMode_1 == LTDC_PIXEL_FORMAT_ARGB8888 ) ) // 判断是否使用24位或者32位色

    // 因为750每个通道的低位都是采用伪随机抖动输出，如果不开启颜色抖动，则无法正常显示24位或者32位色

    HAL_LTDC_EnableDither(&hltdc); // 开启颜色抖动

#endif

#endif

    /*---------------------------------- 初始化一些默认配置 --------------------------------*/

    LCD_DisplayDirection(Direction_H); 	//	设置横屏显示
    LCD_SetFont(&Font24); 				 	//	设置默认字体
    LCD_ShowNumMode(Fill_Space);			//	设置数字显示默认填充空格

    LCD_SetLayer(0);  						// 切换到 layer0
    LCD_SetBackColor(LCD_BLACK); 			//	设置背景色
    LCD_SetColor(LCD_WHITE);				//	设置画笔颜色
    LCD_Clear(); 								//	清屏，刷背景色

    /*---------------------------------- 如果开启了两层显示 --------------------------------*/

#if LCD_NUM_LAYERS == 2

    LCD_SetLayer(1); 							// 切换到前景层 layer1，layer1始终在layer0之上
    LCD_SetBackColor(LCD_BLACK); 			//	设置背景色
    LCD_SetColor(LCD_WHITE);				//	设置画笔颜色
    LCD_Clear(); 								//	清屏，刷背景色

#endif

// LTDC在初始化之后，上电的瞬间会有一个短暂的白屏，
//	即使一开始就将背光引脚拉低并且屏幕背光引脚用电阻下拉还是会有这个现象，
//	如果需要消除这个现象，可以在初始化完毕之后，进行一个短暂的延时再打开背光
//
//	HAL_Delay(200);	// 延时200ms

    LCD_Backlight_ON;							// 开启背光
}

void DisplayLTDC::LCD_SetLayer(uint8_t layer)
{
#if LCD_NUM_LAYERS == 2		// 如果开了双层
	
	if (layer == 0)			// 如果设置的是 layer0
	{
		LayerMemoryAdd = LCD_MemoryAdd; 	// 获取 layer0 的显存地址
		ColorMode      = ColorMode_0;		// 获取 layer0 的颜色格式
		BytesPerPixel  = BytesPerPixel_0;	// 获取 layer0 的每个像素所需字节数的大小
	}
	else if(layer == 1)	 // 如果设置的是 layer1
	{
		LayerMemoryAdd = LCD_MemoryAdd + LCD_MemoryAdd_OFFSET;	// 获取 layer1 的显存地址
		ColorMode      = ColorMode_1;                           // 获取 layer1 的颜色格式
		BytesPerPixel  = BytesPerPixel_1;		                  // 获取 layer1 的每个像素所需字节数的大小
	}
	Layer = layer;	//记录当前所在的层
	
#else		// 如果只开启单层，默认操作 layer0
	
	LayerMemoryAdd = LCD_MemoryAdd;		// 获取 layer0 的显存地址
	ColorMode      = ColorMode_0;      // 获取 layer0 的颜色格式
	BytesPerPixel  = BytesPerPixel_0;	// 获取 layer0 的每个像素所需字节数的大小
	Layer = 0;		// 层标记设置为 layer0
	
#endif
}

void LCD_PanelModify()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;				//	输出模式
    GPIO_InitStruct.Pull 	= GPIO_NOPULL;							//	无上下拉
    GPIO_InitStruct.Speed 	= GPIO_SPEED_FREQ_LOW;				// 速度等级2M

    GPIO_InitStruct.Pin 		= LTDC_R0_PIN; 			//	R0
    HAL_GPIO_Init(LTDC_R0_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin 		= LTDC_R1_PIN; 			//	R1
    HAL_GPIO_Init(LTDC_R1_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin 		= LTDC_G0_PIN; 			//	G0
    HAL_GPIO_Init(LTDC_G0_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin 		= LTDC_G1_PIN; 			//	G1
    HAL_GPIO_Init(LTDC_G1_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin 		= LTDC_B0_PIN; 			//	B0
    HAL_GPIO_Init(LTDC_B0_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin 		= LTDC_B1_PIN; 			//	B1
    HAL_GPIO_Init(LTDC_B1_PORT, &GPIO_InitStruct);

    // The old 5-inch screen only leads to the 18-bit interface, and the remaining data pins are grounded
    // Therefore, it is necessary to output the low 2-bit data pin corresponding to LTDC to a low level

    HAL_GPIO_WritePin(LTDC_R0_PORT, LTDC_R0_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LTDC_R1_PORT, LTDC_R1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LTDC_G0_PORT, LTDC_G0_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LTDC_G1_PORT, LTDC_G1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LTDC_B0_PORT, LTDC_B0_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LTDC_B1_PORT, LTDC_B1_PIN, GPIO_PIN_RESET);
}

extern "C" void HAL_LTDC_MspInit(LTDC_HandleTypeDef *hltdc)
{
    /* 设置LTDC时钟，这里设置为33MHz，即刷新率在60帧左右，过高或者过低都会造成闪烁 */
    /* LCD clock configuration */
    /* PLL3_VCO Input = HSE_VALUE/PLL3M = 1 Mhz */
    /* PLL3_VCO Output = PLL3_VCO Input * PLL3N = 330 Mhz */
    /* PLLLCDCLK = PLL3_VCO Output/PLL3R = 330/10 = 33 Mhz */
    /* LTDC clock frequency = PLLLCDCLK = 33 Mhz */  
    
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
        
    PeriphClkInitStruct.PLL3.PLL3M = 25;
    PeriphClkInitStruct.PLL3.PLL3N = 330;
    PeriphClkInitStruct.PLL3.PLL3P = 2;
    PeriphClkInitStruct.PLL3.PLL3Q = 2;
    PeriphClkInitStruct.PLL3.PLL3R = 10;
    PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_0;
    PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOMEDIUM;
    PeriphClkInitStruct.PLL3.PLL3FRACN = 0;

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;               
    PeriphClkInitStruct.FmcClockSelection = RCC_FMCCLKSOURCE_D1HCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        MBED_ERROR(MBED_MAKE_CUSTOM_ERROR(MBED_MODULE_HAL, -1), "HAL_LTDC_MspInit failed");
    }

    uint8_t Modify_Flag = 0;	// 旧面板识别标志位

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(hltdc->Instance==LTDC)
    {

        __HAL_RCC_LTDC_CLK_ENABLE();		// 使能LTDC时钟

        __HAL_RCC_GPIOK_CLK_ENABLE();	// 使能IO口时钟
        __HAL_RCC_GPIOG_CLK_ENABLE();
        __HAL_RCC_GPIOJ_CLK_ENABLE();
        __HAL_RCC_GPIOH_CLK_ENABLE();
        __HAL_RCC_GPIOI_CLK_ENABLE();

        GPIO_LDC_Backlight_CLK_ENABLE;	// 使能背光引脚IO口时钟

        /*------------------------------LTDC GPIO Configuration--------------------------

            PI15    ------> LTDC_R0		PJ7     ------> LTDC_G0			 PJ12    ------> LTDC_B0
            PJ0     ------> LTDC_R1	   PJ8     ------> LTDC_G1        PJ13    ------> LTDC_B1
            PJ1     ------> LTDC_R2      PJ9     ------> LTDC_G2	       PJ14    ------> LTDC_B2
            PJ2     ------> LTDC_R3      PG10    ------> LTDC_G3	       PJ15    ------> LTDC_B3
            PJ3     ------> LTDC_R4      PH15    ------> LTDC_G4	       PK3     ------> LTDC_B4
            PJ4     ------> LTDC_R5      PH4     ------> LTDC_G5        PK4     ------> LTDC_B5
            PJ5     ------> LTDC_R6	   PK1     ------> LTDC_G6	       PK5     ------> LTDC_B6
            PJ6     ------> LTDC_R7	   PK2     ------> LTDC_G7	       PK6     ------> LTDC_B7

            PI12     ------> LTDC_HSYNC
            PI13     ------> LTDC_VSYNC
            PK7      ------> LTDC_DE
            PI14     ------> LTDC_CLK
        */

        /*----------------------------旧面板识别---------------------------------*/


        GPIO_InitStruct.Mode 	= GPIO_MODE_INPUT;		//	输入模式
        GPIO_InitStruct.Pull 	= GPIO_NOPULL;				//	不上下拉

        GPIO_InitStruct.Pin 		= LTDC_R0_PIN; 			//	R0
        HAL_GPIO_Init(LTDC_R0_PORT, &GPIO_InitStruct);

        GPIO_InitStruct.Pin 		= LTDC_G0_PIN; 			//	G0
        HAL_GPIO_Init(LTDC_G0_PORT, &GPIO_InitStruct);

        GPIO_InitStruct.Pin 		= LTDC_B0_PIN; 			//	B0
        HAL_GPIO_Init(LTDC_B0_PORT, &GPIO_InitStruct);


        // 旧面板识别修改，此处只对旧款5寸屏有用，也就是 RGB050M1  V1.0的版本
        // 旧款5寸屏只引出了18位的接口，低2位数据脚直接接地，如果对应的引脚为低电平则可以确定接入的是旧款5寸屏
        // 其它面板无需理会此处，用户移植的时候可以直接删掉
        if(   (HAL_GPIO_ReadPin(LTDC_R0_PORT,LTDC_R0_PIN) == 0) \
                && (HAL_GPIO_ReadPin(LTDC_G0_PORT,LTDC_G0_PIN) == 0) \
                && (HAL_GPIO_ReadPin(LTDC_B0_PORT,LTDC_B0_PIN) == 0) )
        {

            Modify_Flag	= 1;	// 如果检测到了旧款5寸屏，则置位标志位
        }

        /*-----------------------------------------------------------------------*/


        GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_3
                              |GPIO_PIN_7|GPIO_PIN_2|GPIO_PIN_1;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
        HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
        HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_12|GPIO_PIN_13
                              |GPIO_PIN_9|GPIO_PIN_0|GPIO_PIN_8|GPIO_PIN_7
                              |GPIO_PIN_6|GPIO_PIN_1|GPIO_PIN_5|GPIO_PIN_3|GPIO_PIN_2
                              |GPIO_PIN_4;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
        HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
        HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
        HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_4;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
        HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

        // 初始化背光引脚

        GPIO_InitStruct.Pin 		= LCD_Backlight_PIN;				// 背光引脚
        GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;			// 推挽输出模式
        GPIO_InitStruct.Pull 	= GPIO_NOPULL;						// 无上下拉
        GPIO_InitStruct.Speed 	= GPIO_SPEED_FREQ_LOW;			// 速度等级低
        HAL_GPIO_Init(LCD_Backlight_PORT, &GPIO_InitStruct);	// 初始化

        LCD_Backlight_ON;	// 先关闭背光引脚，初始化LTDC之后再开启

        // 旧面板识别修改，此处只对旧款5寸屏有用，也就是 RGB050M1  V1.0的版本
        // 旧款5寸屏只引出了18位的接口，低2位数据脚直接接地，如果对应的引脚为低电平则可以确定接入的是旧款5寸屏
        // 其它面板无需理会此处，用户移植的时候可以直接删掉

        if (Modify_Flag == 1 )
        {
            LCD_PanelModify();	// 将对应的低2位引脚输出低电平，否则单片机功耗会很高
        }

    }
}

void DisplayLTDC::LCD_SetColor(uint32_t color)
{
    uint16_t Alpha_Value = 0, Red_Value = 0, Green_Value = 0, Blue_Value = 0; //各个颜色通道的值

    if (ColorMode == LTDC_PIXEL_FORMAT_RGB565	)	//将32位色转换为16位色
    {
        Red_Value   = (uint16_t)((color&0x00F80000)>>8);
        Green_Value = (uint16_t)((color&0x0000FC00)>>5);
        Blue_Value  = (uint16_t)((color&0x000000F8)>>3);
        Color = (uint16_t)(Red_Value | Green_Value | Blue_Value);
    }
    else if (ColorMode == LTDC_PIXEL_FORMAT_ARGB1555 )	//将32位色转换为ARGB1555颜色
    {
        if( (Color & 0xFF000000) == 0 )	//判断是否使用透明色
            Alpha_Value = 0x0000;
        else
            Alpha_Value = 0x8000;

        Red_Value   = (uint16_t)((color&0x00F80000)>>9);
        Green_Value = (uint16_t)((color&0x0000F800)>>6);
        Blue_Value  = (uint16_t)((color&0x000000F8)>>3);
        Color = (uint16_t)(Alpha_Value | Red_Value | Green_Value | Blue_Value);
    }
    else if (ColorMode == LTDC_PIXEL_FORMAT_ARGB4444 )	//将32位色转换为ARGB4444颜色
    {

        Alpha_Value = (uint16_t)((Color&0xf0000000)>>16);
        Red_Value   = (uint16_t)((Color&0x00F00000)>>12);
        Green_Value = (uint16_t)((Color&0x0000F000)>>8);
        Blue_Value  = (uint16_t)((Color&0x000000F8)>>4);
        Color = (uint16_t)(Alpha_Value | Red_Value | Green_Value | Blue_Value);
    }
    else
        Color = color;	//24位色或32位色不需要转换
}

void DisplayLTDC::LCD_SetBackColor(uint32_t color)
{
    uint16_t Alpha_Value = 0, Red_Value = 0, Green_Value = 0, Blue_Value = 0;  //各个颜色通道的值

    if( ColorMode == LTDC_PIXEL_FORMAT_RGB565	)	//将32位色转换为16位色
    {
        Red_Value   	= (uint16_t)((color&0x00F80000)>>8);
        Green_Value 	= (uint16_t)((color&0x0000FC00)>>5);
        Blue_Value  	= (uint16_t)((color&0x000000F8)>>3);
        BackColor	= (uint16_t)(Red_Value | Green_Value | Blue_Value);
    }
    else if( ColorMode == LTDC_PIXEL_FORMAT_ARGB1555 )	//将32位色转换为ARGB1555颜色
    {
        if( (Color & 0xFF000000) == 0 )	//判断是否使用透明色
            Alpha_Value = 0x0000;
        else
            Alpha_Value = 0x8000;

        Red_Value   	= (uint16_t)((color&0x00F80000)>>9);
        Green_Value 	= (uint16_t)((color&0x0000F800)>>6);
        Blue_Value  	= (uint16_t)((color&0x000000F8)>>3);
        BackColor 	= (uint16_t)(Alpha_Value | Red_Value | Green_Value | Blue_Value);
    }
    else if( ColorMode == LTDC_PIXEL_FORMAT_ARGB4444 )	//将32位色转换为ARGB4444颜色
    {

        Alpha_Value 	= (uint16_t)((color&0xf0000000)>>16);
        Red_Value   	= (uint16_t)((color&0x00F00000)>>12);
        Green_Value 	= (uint16_t)((color&0x0000F000)>>8);
        Blue_Value  	= (uint16_t)((color&0x000000F8)>>4);
        BackColor 	= (uint16_t)(Alpha_Value | Red_Value | Green_Value | Blue_Value);
    }

    else
        BackColor = color;	// No conversion required for 24-bit or 32-bit color
}

void DisplayLTDC::LCD_SetFont(pFONT *fonts)
{
    Fonts = fonts;
}

void DisplayLTDC::LCD_DisplayDirection(uint8_t direction)
{
    Direction = direction;
}

void DisplayLTDC::LCD_Clear()
{

    DMA2D->CR	    &=	~(DMA2D_CR_START);				//	stop DMA2D
    DMA2D->CR		=	DMA2D_R2M;						//	register to SDRAM
    DMA2D->OPFCCR	=	ColorMode;						//	format colors
    DMA2D->OOR		=	0;								//	set row offset
    DMA2D->OMAR		=	LayerMemoryAdd ;				//  address
    DMA2D->NLR		=	(LCD_Width<<16)|(LCD_Height);	//	set length and width
    DMA2D->OCOLR	=	BackColor;						//	set backcolor

    /******
    Waiting for the vertical data to enable display status, that is, when the LTDC is about to finish brushing a whole screen of data
    Because the screen is refreshed before a frame is refreshed, there will be tearing
    Users can also use the register reload interrupt to make judgments, but in order to ensure the simplicity of the routine and the convenience of transplantation, the method of judging the register is directly used here
    If no judgment is made, the DMA2D screen refresh speed is as follows
    Color format RGB565 RGB888 ARGB888
    Time consumption 4.3ms 7.5ms 11.9ms
    After adding, no matter which format, it takes 17.6ms to refresh a screen, but the refresh rate of the screen itself is only about 60 frames (LTDC clock 33MHz),
    The speed of 17.6ms is enough. Unless the speed requirement is particularly high, it is recommended to add a statement to judge the vertical wait to avoid the tearing effect.
    ******/

    while( LTDC->CDSR != 0X00000001);	    //  determine the display status register LTDC_CDSR bit 0 VDES: vertical data enable display status

    DMA2D->CR	  |=	DMA2D_CR_START;		//  start DMA2D

    while (DMA2D->CR & DMA2D_CR_START) ;	//	wait for the transfer to complete
}

void DisplayLTDC::LCD_ClearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    DMA2D->CR	  &=	~(DMA2D_CR_START);				//	停止DMA2D
    DMA2D->CR		=	DMA2D_R2M;							//	寄存器到SDRAM
    DMA2D->OPFCCR	=	ColorMode;						//	设置颜色格式
    DMA2D->OCOLR	=	BackColor ;					//	颜色

    if(Direction == Direction_H)  //横屏填充
    {
        DMA2D->OOR		=	LCD_Width - width;				//	设置行偏移
        DMA2D->OMAR		=	LayerMemoryAdd + BytesPerPixel*(LCD_Width * y + x);	// 地址;
        DMA2D->NLR		=	(width<<16)|(height);			//	设定长度和宽度
    }
    else	//竖屏填充
    {
        DMA2D->OOR		=	LCD_Width - height;		//	设置行偏移
        DMA2D->OMAR		=	LayerMemoryAdd + BytesPerPixel*((LCD_Height - x - 1 - width)*LCD_Width + y);	// 地址
        DMA2D->NLR		=	(width)|(height<<16);	//	设定长度和宽度
    }

    DMA2D->CR	  |=	DMA2D_CR_START;					//	启动DMA2D

    while (DMA2D->CR & DMA2D_CR_START) ;			//	等待传输完成
}

void DisplayLTDC::LCD_DrawPoint(uint16_t x, uint16_t y, uint32_t color)
{

    /*----------------------- 32位色 ARGB8888 模式 ----------------------*/

    if( ColorMode == LTDC_PIXEL_FORMAT_ARGB8888 )
    {
        if (Direction == Direction_H) //水平方向
        {
            *(__IO uint32_t*)( LayerMemoryAdd + 4*(x + y*LCD_Width) ) = color ;
        }
        else if(Direction == Direction_V)	//垂直方向
        {
            *(__IO uint32_t*)( LayerMemoryAdd + 4*((LCD_Height - x - 1)*LCD_Width + y) ) = color ;
        }
    }
    /*----------------------------- 24位色 RGB888 模式 -------------------------*/

    else if ( ColorMode == LTDC_PIXEL_FORMAT_RGB888 )
    {
        if (Direction == Direction_H) //水平方向
        {
            *(__IO uint16_t*)( LayerMemoryAdd + 3*(x + y*LCD_Width) ) = color ;
            *(__IO uint8_t*)( LayerMemoryAdd + 3*(x + y*LCD_Width) + 2 ) = color>>16 ;
        }
        else if(Direction == Direction_V)	//垂直方向
        {
            *(__IO uint16_t*)( LayerMemoryAdd + 3*((LCD_Height - x - 1)*LCD_Width + y) ) = color ;
            *(__IO uint8_t*)( LayerMemoryAdd + 3*((LCD_Height - x - 1)*LCD_Width + y) +2) = color>>16 ;
        }
    }

    /*----------------------- 16位色 ARGB1555、RGB565或者ARGB4444 模式 ----------------------*/
    else
    {
        if (Direction == Direction_H) //水平方向
        {
            *(__IO uint16_t*)( LayerMemoryAdd + 2*(x + y*LCD_Width) ) = color ;
        }
        else if(Direction == Direction_V)	//垂直方向
        {
            *(__IO uint16_t*)( LayerMemoryAdd + 2*((LCD_Height - x - 1)*LCD_Width + y) ) = color ;
        }
    }
}

uint32_t DisplayLTDC::LCD_ReadPoint(uint16_t x, uint16_t y)
{
    uint32_t color = 0;

    /*----------------------- 32位色 ARGB8888 模式 ----------------------*/
    if( ColorMode == LTDC_PIXEL_FORMAT_ARGB8888 )
    {
        if (Direction == Direction_H) //水平方向
        {
            color = *(__IO uint32_t*)( LayerMemoryAdd + 4*(x + y*LCD_Width) );
        }
        else if(Direction == Direction_V)	//垂直方向
        {
            color = *(__IO uint32_t*)( LayerMemoryAdd + 4*((LCD_Height - x - 1)*LCD_Width + y) );
        }
    }

    /*----------------------------- 24位色 RGB888 模式 -------------------------*/
    else if ( ColorMode == LTDC_PIXEL_FORMAT_RGB888 )
    {
        if (Direction == Direction_H) //水平方向
        {
            color = *(__IO uint32_t*)( LayerMemoryAdd + 3*(x + y*LCD_Width) ) &0x00ffffff;
        }
        else if(Direction == Direction_V)	//垂直方向
        {
            color = *(__IO uint32_t*)( LayerMemoryAdd + 3*((LCD_Height - x - 1)*LCD_Width + y) ) &0x00ffffff;
        }
    }

    /*----------------------- 16位色 ARGB1555、RGB565或者ARGB4444 模式 ----------------------*/
    else
    {
        if (Direction == Direction_H) //水平方向
        {
            color = *(__IO uint16_t*)( LayerMemoryAdd + 2*(x + y*LCD_Width) );
        }
        else if(Direction == Direction_V)	//垂直方向
        {
            color = *(__IO uint16_t*)( LayerMemoryAdd + 2*((LCD_Height - x - 1)*LCD_Width + y) );
        }
    }
    return color;
}

void DisplayLTDC::LCD_DisplayChar(uint16_t x, uint16_t y, uint8_t c)
{
    uint16_t  index = 0, counter = 0;		// 计数变量
    uint8_t   disChar;		//存储字符的地址
    uint16_t  Xaddress = x; //水平坐标

    c = c - 32; 	// 计算ASCII字符的偏移

    for(index = 0; index < Fonts->Sizes; index++)
    {
        disChar = Fonts->pTable[c*Fonts->Sizes + index]; //获取字符的模值
        for(counter = 0; counter < 8; counter++)
        {
            if(disChar & 0x01)
            {
                LCD_DrawPoint(Xaddress,y,Color);		//当前模值不为0时，使用画笔色绘点
            }
            else
            {
                LCD_DrawPoint(Xaddress,y,BackColor);	//否则使用背景色绘制点
            }
            disChar >>= 1;
            Xaddress++;  //水平坐标自加

            if( (Xaddress - x)==Fonts->Width ) //如果水平坐标达到了字符宽度，则退出当前循环
            {   //进入下一行的绘制
                Xaddress = x;
                y++;
                break;
            }
        }
    }
}

void DisplayLTDC::LCD_DisplayString(uint16_t x, uint16_t y, char *p)
{
    while ((x < LCD_Width) && (*p != 0))	//判断显示坐标是否超出显示区域并且字符是否为空字符
    {
        LCD_DisplayChar( x,y,*p);
        x += Fonts->Width; //显示下一个字符
        p++;	//取下一个字符地址
    }
}

void DisplayLTDC::LCD_SetTextFont(pFONT *fonts)
{
    CHFonts = fonts;		// 设置中文字体
    switch(fonts->Width )
    {
    case 12:
        Fonts = &Font12;
        break;	// 设置ASCII字符的字体为 1206
    case 16:
        Fonts = &Font16;
        break;	// 设置ASCII字符的字体为 1608
    case 20:
        Fonts = &Font20;
        break;	// 设置ASCII字符的字体为 2010
    case 24:
        Fonts = &Font24;
        break;	// 设置ASCII字符的字体为 2412
    case 32:
        Fonts = &Font32;
        break;	// 设置ASCII字符的字体为 3216
    default:
        break;
    }
}

void DisplayLTDC::LCD_DrawImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *pImage)
{
    uint8_t   disChar;	//字模的值
    uint16_t  Xaddress = x; //水平坐标
    uint16_t  i=0,j=0,m=0;

    for(i = 0; i <height; i++)
    {
        for(j = 0; j <(float)width/8; j++)
        {
            disChar = *pImage;

            for(m = 0; m < 8; m++)
            {
                if(disChar & 0x01)
                {
                    LCD_DrawPoint(Xaddress,y,Color);	//当前模值不为0时，使用画笔色绘点
                }
                else
                {
                    LCD_DrawPoint(Xaddress,y,BackColor);	//否则使用背景色绘制点
                }
                disChar >>= 1;
                Xaddress++;  //水平坐标自加

                if( (Xaddress - x)==width ) //如果水平坐标达到了字符宽度，则退出当前循环
                {   //进入下一行的绘制
                    Xaddress = x;
                    y++;
                    break;
                }
            }
            pImage++;
        }
    }
}

#define ABS(X)  ((X) > 0 ? (X) : -(X))

void DisplayLTDC::LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
            yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
            curpixel = 0;

    deltax = ABS(x2 - x1);        /* The difference between the x's */
    deltay = ABS(y2 - y1);        /* The difference between the y's */
    x = x1;                       /* Start x off at the first pixel */
    y = y1;                       /* Start y off at the first pixel */

    if (x2 >= x1)                 /* The x-values are increasing */
    {
        xinc1 = 1;
        xinc2 = 1;
    }
    else                          /* The x-values are decreasing */
    {
        xinc1 = -1;
        xinc2 = -1;
    }

    if (y2 >= y1)                 /* The y-values are increasing */
    {
        yinc1 = 1;
        yinc2 = 1;
    }
    else                          /* The y-values are decreasing */
    {
        yinc1 = -1;
        yinc2 = -1;
    }

    if (deltax >= deltay)         /* There is at least one x-value for every y-value */
    {
        xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
        yinc2 = 0;                  /* Don't change the y for every iteration */
        den = deltax;
        num = deltax / 2;
        numadd = deltay;
        numpixels = deltax;         /* There are more x-values than y-values */
    }
    else                          /* There is at least one y-value for every x-value */
    {
        xinc2 = 0;                  /* Don't change the x for every iteration */
        yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
        den = deltay;
        num = deltay / 2;
        numadd = deltax;
        numpixels = deltay;         /* There are more y-values than x-values */
    }
    for (curpixel = 0; curpixel <= numpixels; curpixel++)
    {
        LCD_DrawPoint(x,y,Color);             /* Draw the current pixel */
        num += numadd;              /* Increase the numerator by the top of the fraction */
        if (num >= den)             /* Check if numerator >= denominator */
        {
            num -= den;               /* Calculate the new numerator value */
            x += xinc1;               /* Change the x as appropriate */
            y += yinc1;               /* Change the y as appropriate */
        }
        x += xinc2;                 /* Change the x as appropriate */
        y += yinc2;                 /* Change the y as appropriate */
    }
}

void DisplayLTDC::LCD_DrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    /* draw horizontal lines */
    LCD_DrawLine(x, y, x+width, y);
    LCD_DrawLine(x, y+height, x+width, y+height);

    /* draw vertical lines */
    LCD_DrawLine(x, y, x, y+height);
    LCD_DrawLine(x+width, y, x+width, y+height);
}

void DisplayLTDC::LCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r)
{
    int Xadd = -r, Yadd = 0, err = 2-2*r, e2;
    do {

        LCD_DrawPoint(x-Xadd,y+Yadd,Color);
        LCD_DrawPoint(x+Xadd,y+Yadd,Color);
        LCD_DrawPoint(x+Xadd,y-Yadd,Color);
        LCD_DrawPoint(x-Xadd,y-Yadd,Color);

        e2 = err;
        if (e2 <= Yadd) {
            err += ++Yadd*2+1;
            if (-Xadd == Yadd && e2 <= Xadd) e2 = 0;
        }
        if (e2 > Xadd) err += ++Xadd*2+1;
    }
    while (Xadd <= 0);
}

void DisplayLTDC::LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    DMA2D->CR	  &=	~(DMA2D_CR_START);				//	停止DMA2D
    DMA2D->CR		=	DMA2D_R2M;							//	寄存器到SDRAM
    DMA2D->OPFCCR	=	ColorMode;						//	设置颜色格式
    DMA2D->OCOLR	=	Color;							//	颜色

    if(Direction == Direction_H)  //横屏填充
    {
        DMA2D->OOR		=	LCD_Width - width;				//	设置行偏移
        DMA2D->OMAR		=	LayerMemoryAdd + BytesPerPixel*(LCD_Width * y + x);	// 地址;
        DMA2D->NLR		=	(width<<16)|(height);			//	设定长度和宽度
    }
    else	//竖屏填充
    {
        DMA2D->OOR		=	LCD_Width - height;		//	设置行偏移
        DMA2D->OMAR		=	LayerMemoryAdd + BytesPerPixel*((LCD_Height - x - 1 - width)*LCD_Width + y);	// 地址
        DMA2D->NLR		=	(width)|(height<<16);	//	设定长度和宽度
    }

    DMA2D->CR	  |=	DMA2D_CR_START;					//	启动DMA2D

    while (DMA2D->CR & DMA2D_CR_START) ;			//	等待传输完成
}

void DisplayLTDC::LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r)
{
    int32_t  D;    /* Decision Variable */
    uint32_t  CurX;/* Current X Value */
    uint32_t  CurY;/* Current Y Value */

    D = 3 - (r << 1);

    CurX = 0;
    CurY = r;

    while (CurX <= CurY)
    {
        if(CurY > 0)
        {
            LCD_DrawLine(x - CurX, y - CurY,x - CurX,y - CurY + 2*CurY);
            LCD_DrawLine(x + CurX, y - CurY,x + CurX,y - CurY + 2*CurY);
        }

        if(CurX > 0)
        {
            LCD_DrawLine(x - CurY, y - CurX,x - CurY,y - CurX + 2*CurX);
            LCD_DrawLine(x + CurY, y - CurX,x + CurY,y - CurX + 2*CurX);
        }
        if (D < 0)
        {
            D += (CurX << 2) + 6;
        }
        else
        {
            D += ((CurX - CurY) << 2) + 10;
            CurY--;
        }
        CurX++;
    }

    LCD_DrawCircle(x, y, r);
}

void DisplayLTDC::LCD_ShowNumMode(uint8_t mode)
{
    ShowNum_Mode = mode;
}
