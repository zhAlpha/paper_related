#ifndef LSD_HEADER
#define LSD_HEADER

double * LineSegmentDetection( int * n_out,
                               double * img, int X, int Y,
                               double scale, double sigma_scale, double quant,
                               double ang_th, double log_eps, double density_th,
                               int n_bins,
                               int ** reg_img, int * reg_x, int * reg_y );


double * lsd_scale_region( int * n_out,
                           double * img, int X, int Y, double scale,
                           int ** reg_img, int * reg_x, int * reg_y );


double * lsd_scale(int * n_out, double * img, int X, int Y, double scale);

double * lsd(int * n_out, double * img, int X, int Y);

#endif /* !LSD_HEADER */
/*----------------------------------------------------------------------------*/
