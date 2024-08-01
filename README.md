### 这是一个说明
* 程序根据输入读取图像文件，每读入一个图像输出4个文件：atc.dds/etc.dds/atc.dds.z/etc.dds.z 。
* 本程序使用[OpenCV](https://github.com/opencv/opencv/tree/4.6.0)处理图像读取部分，使用[CompressnaotrSDK](https://github.com/GPUOpen-Tools/compressonator/releases/tag/V4.2.5185)进行atc和etc图像数据编码，使用[Zlib](https://zlib.net/)进行.z压缩。
* 支持的输入图像格式：JPG、PNG等。更多格式参见[OpenCV文档-cv::imread()](https://docs.opencv.org/4.6.0/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56)
### 本程序使用方法：
* 方法1：拖拽一个/一系列文件到本程序的图标上。适用于批量转换。等效于批处理 **文件名.exe 图像1 图像2 图像3... **
* 方法2：打开程序，在出现 Hello World! 后输入1个文件的名称（建议使用绝对路径）
### About
* input 1/more imgs, output 4 files for each img: atc.dds/etc.dds/atc.dds.z/etc.dds.z 
* lib [CompressnaotrSDK](https://github.com/GPUOpen-Tools/compressonator/releases/tag/V4.2.5185) [OpenCV](https://github.com/opencv/opencv/tree/4.6.0) [Zlib](https://zlib.net/) is used in this program.
* support input img format: jpg/png/bmp... See also[OpenCV-cv::imread()](https://docs.opencv.org/4.6.0/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56)
### Use
* Method 1: Select 1 or more image file, and drag them to the icon of this exe. Then all selected files will be converted one by one. This way is same as using cmd: **filename.exe imgfile1 imgfile2 imgfile3 ...**
* Method 2: Run this exe. You'll see "Hello World!". Then input the full path of an image file. Only 1 file can be convert in each run.
