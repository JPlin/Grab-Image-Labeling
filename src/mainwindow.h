#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define _CRT_SECURE_NO_WARNINGS

#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTextStream>
#include <QPaintEvent>
#include <QTime>
#include <QDir>

#include <vector>
#include <cv.h>
#include <highgui.h>
#include "setparameterdialog.h"


using std::vector;
using namespace cv;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_setPushButton_clicked();
    void on_openPushButton_clicked();
    void on_autoPushButton_clicked();
    void on_savePushButton_clicked();
    void on_redoPushButton_clicked();
    void on_undoPushButton_clicked();
    void on_contourModelPushButton_clicked();

    void on_pushLBrowButton_clicked();

    void on_pushRBrowButton_clicked();

    void on_pushLEyeButton_clicked();

    void on_pushREyeButton_clicked();

    void on_pushNoseButton_clicked();

    void on_pushMouthButton_clicked();

    void on_pushLEarButton_clicked();

    void on_pushREarButton_clicked();

    void on_pushShowMaskButton_clicked();

    void on_pushShowOriginButton_clicked();

    void on_pushSkinButton_clicked();

    void on_pushMixButton_clicked();

    void on_horizontalSlider_rangeChanged(int min, int max);

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalScrollBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    SetParameterDialog * prSetDlg;

    QString inputPath;
    QString outputPath;
    QString imgInputPath;
    QString imgOutputPath;
    QString imgOutputDir;

    unsigned int startIdx,frameIdx;

    Mat img_cur,img_pre;

    vector<Point> contour;
    Rect validRegion;

    QFile file,hisfile;

    QDateTime startTime,curTime;
    int timerId;

    bool drawMouseMove;
    bool useHull;

    bool autoModel;
    enum{NOT_SET=0,IN_PROCESS=1,SET=2};
    Mat mask;
    Mat img_cur_copy;
    Mat bgdModel,fgdModel;

    Rect rect;
    uchar rectState,lblsState,prLblsState;
    vector<Point> fgdPxls,bgdPxls,prFgdPxls,prBgdPxls;
    bool isInitialized;
    bool isf;
    int iterCount; // grab cut 的迭代次数
    int paint_width ; // 画刷的宽度

    //不同的层有不同的MAt
    Mat img_lbrow;
    Mat img_rbrow;
    Mat img_leye;
    Mat img_reye;
    Mat img_mouth;
    Mat img_nose;
    Mat img_lear;
    Mat img_rear;
    Mat mix;
    Mat alpha_channel;


    const cv::Scalar LBROW_COLOR;
    const cv::Scalar RBROW_COLOR;
    const cv::Scalar LEYE_COLOR;
    const cv::Scalar REYE_COLOR;
    const cv::Scalar NOSE_COLOR;
    const cv::Scalar MOUTH_COLOR;
    const cv::Scalar LEAR_COLOR;
    const cv::Scalar REAR_COLOR;

    enum{LBROW = 0,RBROW = 1,LEYE = 2, REYE = 3,NOSE = 4,MOUTH = 5,LEAR = 6,REAR = 7};
    int STEP; //当前到第几步
    int no_index; // 标记是第几张图
    QString prefix; // 图片文件名的前缀
    QString real_prefix; // 真正的文件前缀
    int hair_thresh;
    int face_thresh;

    int WIDTH;
    int HEIGHT;

private:
    void displayMat(Mat mat);
    bool readImage();
    void drawConnects();
    void contourFill();
    void getBinMask(const Mat& comMask, Mat& binMask);
    void resetAMParameters();
    void restrictPoint(Point& _point);
    void nextImage();

    int heightForWidth(const int w);
    void turn_to_mask(const Mat&, Mat&, double x);
    void cut_pure_color(Scalar rgb,Mat & src,Mat & mask);
    void cut_the_glass(const Mat &Face,Mat & src);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
