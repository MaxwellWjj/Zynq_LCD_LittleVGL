# Zynq_LCD_LittleVGL
A wonderful graphic library(Littlevgl) in zynq-7020 with an LCD driver
## 感谢
1. 首先必须感谢白神率先在Microblaze移植了这个图形库，踩了很多坑
2. 其次感谢米联客精心设计的LCD驱动，用轮子还是舒服
## 注意
1. 显然，一个完整的FPGA工程是硕大的，无论是分开传还是压缩包都难以上传，所以这里只有zynq的sdk部分工程，底层部分的工程详见另一个Resp——"zynq_LCD_PL"
2. 然后由于lvgl文件夹太多文件，我压缩成了一个包，下载之后就在工程目录下解压lvgl.tar即可
## 环境
1. FPGA：zynq-7020 
2. 图形库：Littlevgl
2. 开发板：米联客的MZ702A
3. 显示屏：微雪的24位RGB屏幕，带触摸功能，分辨率1024×600
## 工程
1. 除了/GUI /lvgl /TASK_TIMER 这三个文件夹以外，其他的都是底层外设配置代码
2. /GUI里面画ui，然后在main里面显示即可，该版本不带FREERTOS，在main里改delay可以改变图形库的任务响应时间
3. /TASK_TIMER 是为图形库提供节拍的，其实这里用FREERTOS会更稳定，但裸机也问题不大
