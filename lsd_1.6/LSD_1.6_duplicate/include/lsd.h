/*----------------------------------------------------------------------------

  LSD - Line Segment Detector on digital images

  This code is part of the following publication and was subject
  to peer review:

    "LSD: a Line Segment Detector" by Rafael Grompone von Gioi,
    Jeremie Jakubowicz, Jean-Michel Morel, and Gregory Randall,
    Image Processing On Line, 2012. DOI:10.5201/ipol.2012.gjmr-lsd
    http://dx.doi.org/10.5201/ipol.2012.gjmr-lsd

  Copyright (c) 2007-2011 rafael grompone von gioi <grompone@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Affero General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Affero General Public License for more details.

  You should have received a copy of the GNU Affero General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.

  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/** @file lsd.h
    LSD module header
    @author rafael grompone von gioi <grompone@gmail.com>
 */
/*----------------------------------------------------------------------------*/
#ifndef LSD_HEADER
#define LSD_HEADER

/*----------------------------------------------------------------------------*/
/** LSD Full Interface

    @param n_out       Pointer to an int where LSD will store the number of
                       line segments detected.
                       指针指向int类型的数据，存储着检测到的线段数量

    @param img         Pointer to input image data. It must be an array of
                       doubles of size X x Y, and the pixel at coordinates
                       (x,y) is obtained by img[x+y*X].
                       指向存储图像数据的指针，它一定是大小为X×Y的double类型的数组，
                       在坐标(x,y)处的像素可以通过 img[x+y*X]获取，（x，y都是从0开始计算的）

    @param X           X size of the image: the number of columns.
                        图像的列数
    @param Y           Y size of the image: the number of rows.
                        图像的行数

    @param scale       When different from 1.0, LSD will scale the input image
                       by 'scale' factor by Gaussian filtering, before detecting
                       line segments.
                       当缩放比例不是1的时候，LSD在检测到线段之前，会通过高斯滤波里的缩放因子对输入的图像进行缩放
                       Example: if scale=0.8, the input image will be subsampled
                       to 80% of its size, before the line segment detector
                       is applied.
                       Suggested value: 0.8

    @param sigma_scale When scale!=1.0, the sigma of the Gaussian filter is:
           sigma值
                       sigma = sigma_scale / scale,   if scale <  1.0
                       sigma = sigma_scale,           if scale >= 1.0
                       Suggested value: 0.6

    @param quant       Bound to the quantization error on the gradient norm.
            量化        绑定量化误差和梯度范数
                       Example: if gray levels are quantized to integer steps,
                       the gradient (computed by finite differences) error
                       due to quantization will be bounded by 2.0, as the
                       worst case is when the error are 1 and -1, that
                       gives an error of 2.0.
                       例：如果灰度被量化成整数步，由于量化产生的梯度(由有限差值计算而来)误差将被限制到2.0，
                       像最坏的情况当误差是1和-1时，这就产生了2.0的误差
                       Suggested value: 2.0

    @param ang_th      Gradient angle tolerance in the region growing
                       algorithm, in degrees.
                       在区域增长法中角度上的梯度角度公差
                       Suggested value: 22.5

    @param log_eps     Detection threshold, accept if -log10(NFA) > log_eps.
                       The larger the value, the more strict the detector is,
                       and will result in less detections.
                       检测的阈值，当-log10(NFA) > log_eps时，值越大，检测越严格，
                       能检测的就会越少。
                       (Note that the 'minus sign' makes that this
                       behavior is opposite to the one of NFA.)
                       注意“负号”使得整体与NFA的单调性相反
                       The value -log10(NFA) is equivalent but more
                       intuitive than NFA:
                       -log10(NFA)和NFA比较虽然等价但是更加直观
                       - -1.0 gives an average of 10 false detections on noise
                       -1.0允许在噪声中有10个错误检测
                       -  0.0 gives an average of 1 false detections on noise
                       -  1.0 gives an average of 0.1 false detections on nose
                       -  2.0 gives an average of 0.01 false detections on noise
                       .
                       Suggested value: 0.0

    @param density_th  Minimal proportion of 'supporting' points in a rectangle.
           密度         在矩形区域中最小化支持点的比例
                       Suggested value: 0.7

    @param n_bins      Number of bins used in the pseudo-ordering of gradient
                       modulus.
                       梯度模块中用于伪序的 bins 的数量
                       Suggested value: 1024

    @param reg_img     Optional output: if desired, LSD will return an
                       int image where each pixel indicates the line segment
                       to which it belongs. Unused pixels have the value '0',
                       while the used ones have the number of the line segment,
                       numbered 1,2,3,..., in the same order as in the
                       output list. If desired, a non NULL int** pointer must
                       be assigned, and LSD will make that the pointer point
                       to an int array of size reg_x x reg_y, where the pixel
                       value at (x,y) is obtained with (*reg_img)[x+y*reg_x].
                       Note that the resulting image has the size of the image
                       used for the processing, that is, the size of the input
                       image scaled by the given factor 'scale'. If scale!=1
                       this size differs from XxY and that is the reason why
                       its value is given by reg_x and reg_y.
                       可选输出：如果需要的话，LSD将会返回一个int图像，其中每个像素表明他是属于哪一个线段。
                       未使用的像素的值标记为0，使用的像素拥有所属的线段的数字，1,2,3...，和输出列表的具有相同的顺序。
                       如果需要的话，会分配一个非空指针int**，LSD将会让这个指针指向一个大小为reg_x × reg_y的int数组，
                       其中在(x,y)点处的像素值可以通过(*reg_img)[x+y*reg_x]取得。
                       注意最终处理完的图像拥有和用来处理的图像相同大小的尺寸，既输入图像的尺寸会通过缩放因子"scale"进行缩放，
                       如果scale不等于1，那么这个尺寸就和 XxY 不同了，这就是它的值要通过reg_x和reg_y给出的原因。
                       Suggested value: NULL

    @param reg_x       Pointer to an int where LSD will put the X size
                       'reg_img' image, when asked for.
                       指向一个整型的指针，其中LSD会存放'reg_img'图像的X的大小
                       Suggested value: NULL

    @param reg_y       Pointer to an int where LSD will put the Y size
                       'reg_img' image, when asked for.
                       指向一个整型的指针，其中LSD会存放'reg_img'图像的Y的大小
                       Suggested value: NULL

    @return            A double array of size 7 x n_out, containing the list
                       of line segments detected. The array contains first
                       7 values of line segment number 1, then the 7 values
                       of line segment number 2, and so on, and it finish
                       by the 7 values of line segment number n_out.
                       The seven values are:
                       - x1,y1,x2,y2,width,p,-log10(NFA)
                       .
                       一个大小为 7 x n_out 的double类型的数组，包含着检测到的线段的列表，
                       这个数组从开头包含着线段1的7个值，线段2的七个值，以此类推...到线段"n_out"
                       的七个值结尾，这七个值分别是：
                        - x1,y1,x2,y2,width,p,-log10(NFA)。

                       for a line segment from coordinates (x1,y1) to (x2,y2),
                       a width 'width', an angle precision of p in (0,1) given
                       by angle_tolerance/180 degree, and NFA value 'NFA'.
                       If 'out' is the returned pointer, the 7 values of
                       line segment number 'n+1' are obtained with
                       'out[7*n+0]' to 'out[7*n+6]'.

                       对于一个线段从坐标系 (x1,y1) 到 (x2,y2),宽度"width",区间在(0,1)角度精度p由
                       angle_tolerance/180给出，NFA的值"NFA".如果"out"是一个返回指针，线段"n+1"
                       的7个值可以通过 'out[7*n+0]' 到 'out[7*n+6]'取得。
 */
double * LineSegmentDetection( int * n_out,
                               double * img, int X, int Y,
                               double scale, double sigma_scale, double quant,
                               double ang_th, double log_eps, double density_th,
                               int n_bins,
                               int ** reg_img, int * reg_x, int * reg_y );

/*----------------------------------------------------------------------------*/
/** LSD Simple Interface with Scale and Region output.

    @param n_out       Pointer to an int where LSD will store the number of
                       line segments detected.

    @param img         Pointer to input image data. It must be an array of
                       doubles of size X x Y, and the pixel at coordinates
                       (x,y) is obtained by img[x+y*X].

    @param X           X size of the image: the number of columns.

    @param Y           Y size of the image: the number of rows.

    @param scale       When different from 1.0, LSD will scale the input image
                       by 'scale' factor by Gaussian filtering, before detecting
                       line segments.
                       Example: if scale=0.8, the input image will be subsampled
                       to 80% of its size, before the line segment detector
                       is applied.
                       Suggested value: 0.8

    @param reg_img     Optional output: if desired, LSD will return an
                       int image where each pixel indicates the line segment
                       to which it belongs. Unused pixels have the value '0',
                       while the used ones have the number of the line segment,
                       numbered 1,2,3,..., in the same order as in the
                       output list. If desired, a non NULL int** pointer must
                       be assigned, and LSD will make that the pointer point
                       to an int array of size reg_x x reg_y, where the pixel
                       value at (x,y) is obtained with (*reg_img)[x+y*reg_x].
                       Note that the resulting image has the size of the image
                       used for the processing, that is, the size of the input
                       image scaled by the given factor 'scale'. If scale!=1
                       this size differs from XxY and that is the reason why
                       its value is given by reg_x and reg_y.
                       Suggested value: NULL

    @param reg_x       Pointer to an int where LSD will put the X size
                       'reg_img' image, when asked for.
                       Suggested value: NULL

    @param reg_y       Pointer to an int where LSD will put the Y size
                       'reg_img' image, when asked for.
                       Suggested value: NULL

    @return            A double array of size 7 x n_out, containing the list
                       of line segments detected. The array contains first
                       7 values of line segment number 1, then the 7 values
                       of line segment number 2, and so on, and it finish
                       by the 7 values of line segment number n_out.
                       The seven values are:
                       - x1,y1,x2,y2,width,p,-log10(NFA)
                       .
                       for a line segment from coordinates (x1,y1) to (x2,y2),
                       a width 'width', an angle precision of p in (0,1) given
                       by angle_tolerance/180 degree, and NFA value 'NFA'.
                       If 'out' is the returned pointer, the 7 values of
                       line segment number 'n+1' are obtained with
                       'out[7*n+0]' to 'out[7*n+6]'.
 */
double * lsd_scale_region( int * n_out,
                           double * img, int X, int Y, double scale,
                           int ** reg_img, int * reg_x, int * reg_y );

/*----------------------------------------------------------------------------*/
/** LSD Simple Interface with Scale

    @param n_out       Pointer to an int where LSD will store the number of
                       line segments detected.

    @param img         Pointer to input image data. It must be an array of
                       doubles of size X x Y, and the pixel at coordinates
                       (x,y) is obtained by img[x+y*X].

    @param X           X size of the image: the number of columns.

    @param Y           Y size of the image: the number of rows.

    @param scale       When different from 1.0, LSD will scale the input image
                       by 'scale' factor by Gaussian filtering, before detecting
                       line segments.
                       Example: if scale=0.8, the input image will be subsampled
                       to 80% of its size, before the line segment detector
                       is applied.
                       Suggested value: 0.8

    @return            A double array of size 7 x n_out, containing the list
                       of line segments detected. The array contains first
                       7 values of line segment number 1, then the 7 values
                       of line segment number 2, and so on, and it finish
                       by the 7 values of line segment number n_out.
                       The seven values are:
                       - x1,y1,x2,y2,width,p,-log10(NFA)
                       .
                       for a line segment from coordinates (x1,y1) to (x2,y2),
                       a width 'width', an angle precision of p in (0,1) given
                       by angle_tolerance/180 degree, and NFA value 'NFA'.
                       If 'out' is the returned pointer, the 7 values of
                       line segment number 'n+1' are obtained with
                       'out[7*n+0]' to 'out[7*n+6]'.
 */
double * lsd_scale(int * n_out, double * img, int X, int Y, double scale);

/*----------------------------------------------------------------------------*/
/** LSD Simple Interface

    @param n_out       Pointer to an int where LSD will store the number of
                       line segments detected.

    @param img         Pointer to input image data. It must be an array of
                       doubles of size X x Y, and the pixel at coordinates
                       (x,y) is obtained by img[x+y*X].

    @param X           X size of the image: the number of columns.

    @param Y           Y size of the image: the number of rows.

    @return            A double array of size 7 x n_out, containing the list
                       of line segments detected. The array contains first
                       7 values of line segment number 1, then the 7 values
                       of line segment number 2, and so on, and it finish
                       by the 7 values of line segment number n_out.
                       The seven values are:
                       - x1,y1,x2,y2,width,p,-log10(NFA)
                       .
                       for a line segment from coordinates (x1,y1) to (x2,y2),
                       a width 'width', an angle precision of p in (0,1) given
                       by angle_tolerance/180 degree, and NFA value 'NFA'.
                       If 'out' is the returned pointer, the 7 values of
                       line segment number 'n+1' are obtained with
                       'out[7*n+0]' to 'out[7*n+6]'.
 */
double * lsd(int * n_out, double * img, int X, int Y);

#endif /* !LSD_HEADER */
/*----------------------------------------------------------------------------*/
