# VINS-Mono代码注释
部分注释内容参考<a href="https://github.com/castiel520/VINS-Mono" target="_blank">https://github.com/castiel520/VINS-Mono</a>
  
[VINS-Mono详解及公式推导](https://github.com/QingSimon/VINS-Mono-code-annotation/blob/master/VINS-Mono%E8%AF%A6%E8%A7%A3.pdf)

# 系统启动命令
    $ roslaunch vins_estimator euroc.launch
    $ roslaunch vins_estimator vins_rviz.launch 
    $ rosbag play YOUR_PATH_TO_DATASET/MH_03_medium.bag 
    $ roslaunch benchmark_publisher publish.launch  sequence_name:=MH_03_medium

# 文件目录概述
    ar_demo
    benchmark_publisher 发布数据集中参考值
    config 硬件、系统配置文件
    camera_model
      calib
      camera_models 各类相机模型
      chessboard 用于检测棋盘格特征点
      gpl
      sparse_graph
      intrinsic_calib.cc 相机矫正模块主函数
    feature_trackers
      feature_tracker_node(main()函数,ROS接受图像的回调函数)
      feature_tracker.c 特征点跟踪的具体实现
    support_files
    vins_estimator
      src
        factor 实现IMU、camera等残差模型，涉及了ceres优化库，Jacobian矩阵。
        initial 系统初始化，外参标定，SFM
        loop_closure 闭环检测，这里主要是利用DBOW2作者的一个demo程序
        utility 相机显示，四元数等数据转换
        estimator_node(main()函数)
          多线程 measurement_process、loop_detection、 pose_graph
        feature_manager.cpp 特征点管理，三角化，关键帧操作
        parameters.cpp 外部系统设置参数输入

# 特征点跟踪过程
    feature_tracker_node.cpp main()

      1. readParameters() 通过ROS来读取参数
      2. FeatureTracker::readIntrinsicParameter() 读取相机内参
      3. 读取mask图片（鱼眼相机）
      4. img_callback() ROS回调函数
         4.1 FeatureTracker::readImage()
            cv::createCLAHE() 直方图均衡化（可选）
            cv::calcOpticalFlowPyrLK() LK金字塔光流法(同时会去除那些无法追踪到的特征点)
            FeatureTracker::rejectWithF() 通过F矩阵去除外点
            FeatureTracker::setMask() 设置遮挡部分（鱼眼相机）
              对检测到的特征点按追踪到的次数排序
              在mask图像中将追踪到点的地方设置为0，否则为255，
              目的是为了下面做特征点检测的时候可以选择没有特征点的区域进行检测。
              在同一区域内，追踪到次数最多的点会被保留，其他的点会被删除。
            cv::goodFeaturesToTrack() 添加角点(第一帧初始化特征点检测也是通过这里完成的)
            FeatureTracker::addPoints() 添加新检测到的特征点
         4.2 FeatureTracker::undistortedPoints() 将所有特征点转换到一个归一化平面并且进行畸变
         4.3 发送图像特征点

# 估计节点 estimator_node
    1. readParameters() 通过ROS来读取参数
    2. Estimator::setParameter() 设置参数
    3. registerPub()    用于RVIZ显示的Topic (visualization.cpp)
    4. 订阅IMU、特征点 和 camera原始图像Topic消息
      4.1 imu_callback() 订阅 IMU 消息
         将新得到的IMU数据放入到 imu_buf 缓冲区中
         pubLatestOdometry() 将最新的里程计数据发送的Rviz中 显示 tmp_P、tmp_Q和tmp_V
      4.2 feature_callback() 订阅 特征点 消息
          将最新的特征点数据放入缓冲区feature_buf
      4.3 raw_image_callback()  订阅 camera原始图像Topic消息 
          如果进行闭环检测的话，才会有后续对原始图像处理，
          将原始图像放入到缓冲区中image_buf
    多线程处理 process()、loop_detection()、 pose_graph()
    闭环处理（可选）

## process线程



## loop_detection线程




## pose_graph线程




