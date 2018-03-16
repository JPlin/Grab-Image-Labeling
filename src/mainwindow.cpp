#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <sstream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    /*
    img_rbrow(480,640,CV_8UC3,Scalar(0,0,0)),
    img_lbrow(480,640,CV_8UC3,Scalar(0,0,0)),
    img_leye(480,640,CV_8UC3,Scalar(0,0,0)),
    img_reye(480,640,CV_8UC3,Scalar(0,0,0)),
    img_nose(480,640,CV_8UC3,Scalar(0,0,0)),
    img_mouth(480,640,CV_8UC3,Scalar(0,0,0)),
    img_lear(480,640,CV_8UC3,Scalar(0,0,0)),
    img_rear(480,640,CV_8UC3,Scalar(0,0,0)),
    mix(480,640,CV_8UC3,Scalar(0,0,0)),
    alpha_channel(480,640,CV_8UC1,Scalar(255)),
    */
    LEYE_COLOR(255,144,30),
    REYE_COLOR(225,105,65),
    LBROW_COLOR(30,144,255),
    RBROW_COLOR(0,165,255),
    NOSE_COLOR(255,255,0),
    MOUTH_COLOR(255,0,255),
    LEAR_COLOR(255,246,143),
    REAR_COLOR(255,228,225)
{

    ui->setupUi(this);

    //ui->label->setScaledContents(true);

    ui->openPushButton->setEnabled(false);
    ui->autoPushButton->setEnabled(false);
    ui->savePushButton->setEnabled(false);
    ui->redoPushButton->setEnabled(false);
    ui->undoPushButton->setEnabled(false);
    ui->contourModelPushButton->setEnabled(false);


    ui->savePushButton->setShortcut(tr("ctrl+s"));
    ui->redoPushButton->setShortcut(tr("ctrl+r"));
    ui->undoPushButton->setShortcut(tr("ctrl+u"));

    ui->pushMixButton->setShortcut(tr("space"));

    ui->pushLBrowButton->setEnabled(false);

    validRegion.x=ui->label->frameGeometry().x();
    validRegion.y=ui->label->frameGeometry().y()+10;
    validRegion.height=ui->label->frameGeometry().height();
    validRegion.width=ui->label->frameGeometry().width();
    ui->horizontalSlider->setValue(30);


    prSetDlg=new SetParameterDialog();

    file.setFileName("set.ini");
    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(NULL, "File Read Error", file.errorString(),QMessageBox::Ok , QMessageBox::Ok);
    }

    while(!file.atEnd())
    {
        QByteArray line=file.readLine();
        QString strTmp(line);
        strTmp.trimmed();
        if(strTmp.startsWith("SequencePath="))
        {
            prSetDlg->setSeqPath(strTmp.mid(13).trimmed());
        }

        if(strTmp.startsWith("FileFormat="))
        {
           prSetDlg->setFileFormat(strTmp.mid(11).trimmed());
        }

        if(strTmp.startsWith("OutputPath="))
        {
            prSetDlg->setOutputPath(strTmp.mid(11).trimmed());
        }

        if(strTmp.startsWith("StartFrame="))
        {
            prSetDlg->setStartFrame(strTmp.mid(11).trimmed());
        }
    }

    hisfile.setFileName("history.ini");
    if(!hisfile.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        QMessageBox::information(NULL, "File Read Error", file.errorString(),QMessageBox::Ok , QMessageBox::Ok);
    }

    inputPath="";
    outputPath="";
    imgInputPath="";
    imgOutputPath="";

    frameIdx=0;

    drawMouseMove=false;

    useHull=true; //Hull Model When Start

    autoModel=true; //Auto Model When Start

    rectState=NOT_SET;
    lblsState=NOT_SET;
    prLblsState=NOT_SET;
    isInitialized=false;
    isf=true;
    iterCount = 3;
    paint_width = 2;


    STEP = LBROW;
    no_index = 1;
    prefix = "";
    hair_thresh = 30; // hair's thresh's hold defult as 30
    face_thresh = 50;
}

MainWindow::~MainWindow()
{

    QTextStream out(&file);
    QString strTmp;
    strTmp=QString("%1%2").arg("StartFrame=").arg(prSetDlg->getStartFrame());
    out<<strTmp<<endl;
    file.close();

    QTextStream hisout(&hisfile);
    qint64 elapsedSec=startTime.msecsTo(curTime)/1000;
    strTmp=QString("%1  %2  %3:%4:%5").arg(frameIdx).arg(frameIdx-startIdx).arg(elapsedSec/3600).arg((elapsedSec%3600)/60).arg(elapsedSec%60);
    hisout<<strTmp<<endl;
    hisfile.close();

    delete ui;
}


void MainWindow::displayMat(Mat mat)
{
    Mat rgb;
    QImage img;
    if(mat.channels()==3)
    {
        cvtColor(mat,rgb,CV_BGR2RGB);
        img = QImage((const uchar*)(rgb.data),rgb.cols,rgb.rows,rgb.cols*rgb.channels(),QImage::Format_RGB888);
    }
    else
    {
        img = QImage((const uchar*)(mat.data),mat.cols,mat.rows,mat.cols*mat.channels(),QImage::Format_Indexed8);
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
    //ui->label->resize(ui->label->pixmap()->size());
    ui->label->show();
}

void MainWindow::on_setPushButton_clicked()
{
    ui->openPushButton->setEnabled(false);
    ui->autoPushButton->setEnabled(false);
    ui->savePushButton->setEnabled(false);
    ui->redoPushButton->setEnabled(false);
    ui->undoPushButton->setEnabled(false);
    ui->contourModelPushButton->setEnabled(false);


    if(prSetDlg->exec()==QDialog::Accepted)
    {
       QString seqPath=prSetDlg->getSeqPath();
       QString fileFormat=prSetDlg->getFileFormat(); //have to be %3d
       QString oPath=prSetDlg->getOutputPath();
       QString startFrame=prSetDlg->getStartFrame();


       file.resize(0);
       QTextStream out(&file);
       QString strTmp;
       strTmp=QString("%1%2").arg("SequencePath=").arg(seqPath);
       out<<strTmp<<endl;
       strTmp=QString("%1%2").arg("FileFormat=").arg(fileFormat);
       out<<strTmp<<endl;
       strTmp=QString("%1%2").arg("OutputPath=").arg(oPath);
       out<<strTmp<<endl;
       strTmp=QString("%1%2").arg("StartFrame=").arg(startFrame);
       out<<strTmp<<endl;

       if(seqPath==""||fileFormat==""||oPath==""||startFrame=="")
       {
           QMessageBox::information(NULL, "Information", "Please Set The Parematers",QMessageBox::Ok , QMessageBox::Ok);
       }
       else
       {
           if(seqPath.endsWith("\\"))
           {

               // [old_v] inputPath=seqPath+fileFormat + "\\" + "%d";
                inputPath = seqPath + fileFormat;
           }
           else
           {
               // [old_v] inputPath=seqPath+"\\"+fileFormat + "\\" + "%d";
                inputPath = seqPath + "\\" + fileFormat;
           }

           if(outputPath.endsWith("\\"))
           {
               outputPath= "\\%s.png";
               // [old_v] imgOutputDir = inputPath + "\\parsing";
               imgOutputDir = inputPath;
           }
           else
           {
               //outputPath=oPath+"\\"+fileFormat;
               outputPath="\\%s.png";
               // [old_v] imgOutputDir = inputPath + "\\parsing";
               imgOutputDir = inputPath;

           }

           frameIdx=startFrame.toInt();
           ui->openPushButton->setEnabled(true);
       }
    }
    else
    {
       QMessageBox::information(NULL, "Information", "Please Set The Parematers",QMessageBox::Ok , QMessageBox::Ok);
    }

}

void MainWindow::on_openPushButton_clicked()
{
    no_index = 1;
    readImage();
    ui->openPushButton->setEnabled(false);
    ui->autoPushButton->setEnabled(true);
    ui->savePushButton->setEnabled(false);
    ui->redoPushButton->setEnabled(true);
    ui->undoPushButton->setEnabled(true);
    ui->contourModelPushButton->setEnabled(true);

    startIdx=prSetDlg->getStartFrame().toInt();
    startTime=QDateTime::currentDateTime();
    timerId=startTimer(1000);
}

void MainWindow::on_autoPushButton_clicked()
{
    if(autoModel)
    {
        autoModel=false;
        ui->autoPushButton->setText("Auto");
    }
    else
    {
        resetAMParameters();
        img_cur.copyTo(img_cur_copy);
        autoModel=true;
        ui->autoPushButton->setText("Manual");
    }
}

void MainWindow::on_savePushButton_clicked()
{
    bool flag = false;


    if(img_lbrow.empty())
    {
        img_cur.copyTo(img_lbrow);
        img_lbrow.setTo(0);
        flag = true;
    }
    if(img_rbrow.empty())
    {
        img_cur.copyTo(img_rbrow);
        img_rbrow.setTo(0);
        flag = true;
    }
    if(img_leye.empty())
    {
        img_cur.copyTo(img_leye);
        img_leye.setTo(0);
        flag = true;
    }
    if(img_reye.empty())
    {
        img_cur.copyTo(img_reye);
        img_reye.setTo(0);
        flag = true;
    }
    if(img_nose.empty())
    {
        img_cur.copyTo(img_nose);
        img_nose.setTo(0);
        flag = true;
    }
    if(img_mouth.empty())
    {
        img_cur.copyTo(img_mouth);
        img_mouth.setTo(0);
        flag =true;
    }
    if(img_lear.empty())
    {
        img_cur.copyTo(img_lear);
        img_lear.setTo(0);
        flag = true;
    }
    if(img_rear.empty())
    {
        img_cur.copyTo(img_rear);
        img_rear.setTo(0);
        flag = true;
    }

    QString path;
    // [old_v] path.sprintf(imgOutputDir.toStdString().c_str(),frameIdx,no_index);
    path.sprintf(imgOutputDir.toStdString().c_str(),frameIdx);
    QDir dir(path);
    if(!dir.exists())
        dir.mkdir(path);
    //QMessageBox::information(NULL,"Save Error",path,QMessageBox::Ok);
    QFile fi;

    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION); //PNG格式图片的压缩级别
    compression_params.push_back(9);  //这里设置保存的图像质量级别

    Mat resizemat;
    imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"lbrow");
    fi.setFileName(imgOutputPath);
    if(fi.exists())
        fi.remove();
    //cv::resize(img_lbrow , resizemat , Size(WIDTH , HEIGHT) ,  (0, 0), (0, 0), cv::INTER_NEAREST);
    if(!imwrite(imgOutputPath.toStdString(),img_lbrow,compression_params))
        flag = true;

    imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"rbrow");
    fi.setFileName(imgOutputPath);
    if(fi.exists())
        fi.remove();

    if(!imwrite(imgOutputPath.toStdString(),img_rbrow,compression_params))
        flag = true;

    imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"leye");
    fi.setFileName(imgOutputPath);
    if(fi.exists())
        fi.remove();

    if(!imwrite(imgOutputPath.toStdString(),img_leye,compression_params))
        flag = true;

    imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"reye");
    fi.setFileName(imgOutputPath);
    if(fi.exists())
        fi.remove();

    if(!imwrite(imgOutputPath.toStdString(),img_reye,compression_params))
        flag = true;

    imgOutputPath.sprintf((path+outputPath).toStdString().c_str() ,"nose");
    fi.setFileName(imgOutputPath);
    if(fi.exists())
        fi.remove();

    if(!imwrite(imgOutputPath.toStdString(),img_nose,compression_params))
        flag = true;

    imgOutputPath.sprintf((path+outputPath).toStdString().c_str() ,"mouth");
    fi.setFileName(imgOutputPath);
    if(fi.exists())
        fi.remove();

    if(!imwrite(imgOutputPath.toStdString(),img_mouth,compression_params))
        flag = true;

    imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"lear");
    fi.setFileName(imgOutputPath);
    if(fi.exists())
        fi.remove();

    if(!imwrite(imgOutputPath.toStdString(),img_lear,compression_params))
        flag = true;

    imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"rear");
    fi.setFileName(imgOutputPath);
    if(fi.exists())
        fi.remove();

    if(!imwrite(imgOutputPath.toStdString(),img_rear,compression_params))
        flag = true;


    imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"mix");
    fi.setFileName(imgOutputPath);
    if(fi.exists())
        fi.remove();

    if(!imwrite(imgOutputPath.toStdString(),mix,compression_params))
        QMessageBox::information(NULL,"Save Error","something wrong in saving mix image!",QMessageBox::Ok);

    imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"mix_alpha");
    fi.setFileName(imgOutputPath);
    if(fi.exists())
        fi.remove();
    //tha result add the alpha channel
    vector<Mat> channels;
    split(mix,channels);
    channels.push_back(alpha_channel);
    Mat alpha_channels(HEIGHT,WIDTH,CV_8UC4,Scalar(0,0,0,0));
    merge(channels,alpha_channels);

    if(!imwrite(imgOutputPath.toStdString(),alpha_channels,compression_params))
        QMessageBox::information(NULL,"Save Error","something wrong in saving mix image!",QMessageBox::Ok);

    if(flag)
    {
        QMessageBox::information(NULL,"Save Error","Something wrong in saving, lack or something!",QMessageBox::Ok);
    }

    //进行下一张图片的读取

    /* [old_v]
    if(no_index ==  1)
        no_index = 2;
    else
    {
        no_index = 1;
        frameIdx++;
    }
    */
    frameIdx ++;

    readImage();

    /*
    else
    {
        frameIdx++;
        readImage();
        if(!readImage())
        {
            frameIdx--;
        }
    }*/

}

void MainWindow::on_redoPushButton_clicked()
{
    //readImage();
    resetAMParameters();
    img_cur.copyTo(img_cur_copy);
    displayMat(img_cur_copy);
}

void MainWindow::on_undoPushButton_clicked()
{
    img_pre.copyTo(img_cur);
    img_pre.copyTo(img_cur_copy);
    displayMat(img_cur);
    contour.clear();
    resetAMParameters();
}

void MainWindow::on_contourModelPushButton_clicked()
{
    if(useHull)
    {
        useHull=false;
        ui->contourModelPushButton->setText("Hull");
    }
    else
    {
        useHull=true;
        ui->contourModelPushButton->setText("Poly");
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)              //{Left Button Be Pressed}
    {
        Point pointTmp(event->x(),event->y());
        restrictPoint(pointTmp);

        if(autoModel)                      //[Auto Model]
        {
            if(rectState==NOT_SET)                                                          // RectMask
            {
                rect.x=pointTmp.x;
                rect.y=pointTmp.y;
                rectState=IN_PROCESS;
            }
            else if(rectState==SET&&QApplication::keyboardModifiers()==Qt::ShiftModifier)   // Shift+LeftClick: GC_FG
            {
                isf=true;
                lblsState=IN_PROCESS;
            }
            else if(rectState==SET&&QApplication::keyboardModifiers()==Qt::ControlModifier) // Ctrl+LeftClick: GC_BG
            {
                isf=false;
                lblsState=IN_PROCESS;
            }
            else if(rectState==SET&&QApplication::keyboardModifiers()==Qt::AltModifier)     // Alt+LeftClick: GC_PR_FG
            {
                isf=true;
                prLblsState=IN_PROCESS;
            }
            else if(rectState==SET)                                                         // LeftClick: GC_PR_BG
            {
                isf=false;
                prLblsState=IN_PROCESS;
            }

        }
        else                               //[Manual Model]
        {
            contour.push_back(pointTmp);
            drawConnects();
        }

        drawMouseMove=true;
    }
    else if(event->button()==Qt::RightButton)        //{Right Button Be Pressed}
    {
        if(autoModel)                      //[Auto Model]
        {
            //Ctrl+RightClick One: Draw The Contour; Double: Fill The Contour
            if(rectState!=IN_PROCESS&&lblsState!=IN_PROCESS&&prLblsState!=IN_PROCESS)
            {
                if(QApplication::keyboardModifiers()==Qt::ControlModifier)
                {
                    static int rightClickCount=0;
                    if(rightClickCount==0)
                    {
                        Mat binMask;
                        getBinMask(mask, binMask);
                        vector<vector<Point>> contours;
                        findContours(binMask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

                        if(contours.size()==1)
                        {
                            contour=contours[0];
                        }
                        else
                        {
                            QMessageBox::information(NULL,"Information","Please Label One Foreground Object !",QMessageBox::Ok);
                        }

                        drawConnects();

                        resetAMParameters();
                        rightClickCount=1;
                    }
                    else if(rightClickCount==1)
                    {
                        contourFill();
                        rightClickCount=0;
                    }
               }
               else    //RightClick: Cut The Foreground Iteratively
               {
                    img_cur.copyTo(img_cur_copy);
                    if (isInitialized)
                        grabCut(img_cur_copy, mask, rect, bgdModel, fgdModel , iterCount);
                    else
                    {
                        if (lblsState == SET || prLblsState == SET)
                            grabCut(img_cur_copy, mask, rect, bgdModel, fgdModel, iterCount , GC_INIT_WITH_MASK);
                        else
                            grabCut(img_cur_copy, mask, rect, bgdModel, fgdModel, iterCount , GC_INIT_WITH_RECT);

                        isInitialized = true;
                    }
                    bgdPxls.clear(); fgdPxls.clear();
                    prBgdPxls.clear(); prFgdPxls.clear();


                    Mat binMask;
                    Mat res;

                    cv::GaussianBlur(img_cur_copy,img_cur_copy,Size(5,5),0);

                    if (!isInitialized)
                    {
                        switch(STEP){
                        case LBROW:
                            img_cur_copy.copyTo(img_lbrow);
                            break;
                        case RBROW:
                            img_cur_copy.copyTo(img_rbrow);
                            break;
                        case LEYE:
                            img_cur_copy.copyTo(img_leye);
                            break;
                        case REYE:
                            img_cur_copy.copyTo(img_reye);
                            break;
                        case NOSE:
                            img_cur_copy.copyTo(img_nose);
                            break;
                        case MOUTH:
                            img_cur_copy.copyTo(img_mouth);
                            break;
                        case LEAR:
                            img_cur_copy.copyTo(img_lear);
                            break;
                        case REAR:
                            img_cur_copy.copyTo(img_rear);
                            break;
                        }\
                    }
                    else
                    {
                        img_cur_copy.setTo(Scalar::all(0));
                        getBinMask(mask, binMask);
                        img_cur.copyTo(img_cur_copy, binMask);
                        switch(STEP){
                        case LBROW:
                            img_cur_copy.copyTo(img_lbrow);
                            break;
                        case RBROW:
                            img_cur_copy.copyTo(img_rbrow);
                            break;
                        case LEYE:
                            img_cur_copy.copyTo(img_leye);
                            break;
                        case REYE:
                            img_cur_copy.copyTo(img_reye);
                            break;
                        case NOSE:
                            img_cur_copy.copyTo(img_nose);
                            break;
                        case MOUTH:
                            img_cur_copy.copyTo(img_mouth);
                            break;
                        case LEAR:
                            img_cur_copy.copyTo(img_lear);
                            break;
                        case REAR:
                            img_cur_copy.copyTo(img_rear);
                            break;
                        }\
                    }
                    Mat temp_show;
                    addWeighted(img_cur,0.5,img_cur_copy,0.5,0,temp_show);
                    displayMat(temp_show);
              }
            }
            else
            {
                resetAMParameters();
            }
        }
        else                               //[Manual Model]
        {
            contourFill();
        }
    }
    else if(event->button()==Qt::MiddleButton)       //{Middle button be pressed}
    {
        if(!contour.empty())
        {
            contour.pop_back();
            drawConnects();
        }
        else
        {
            QMessageBox::information(NULL,"Information","Points Pool Is Empty !",QMessageBox::Ok);
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        Point pointTmp(event->x(),event->y());
        restrictPoint(pointTmp);

        if(autoModel)                      //[Auto Model]
        {
            if(rectState==IN_PROCESS)
            {
                rect.width=abs(pointTmp.x-rect.x);
                rect.height=abs(pointTmp.y-rect.y);
                rect.x=rect.x>pointTmp.x?pointTmp.x:rect.x;
                rect.y=rect.y>pointTmp.y?pointTmp.y:rect.y;

                if(rect.area()>10) //The Area Of The Rect Should Not Be Too Small
                {
                    mask.setTo(GC_BGD);
                    (mask(rect)).setTo(Scalar(GC_PR_FGD));
                    rectState=SET;
                }
                else
                {
                    resetAMParameters();
                }


            }

            vector<Point>::const_iterator it;
            if(lblsState==IN_PROCESS&&isf)
            {
                for(it=fgdPxls.begin();it!=fgdPxls.end();++it)
                    circle(mask,*it,paint_width,GC_FGD,-1);
                lblsState=SET;
            }

            if(lblsState==IN_PROCESS&&!isf)
            {
                for(it=bgdPxls.begin();it!=bgdPxls.end();++it)
                    circle(mask,*it,paint_width,GC_BGD,-1);
                lblsState=SET;
            }

            if(prLblsState==IN_PROCESS&&isf)
            {
                for(it=prFgdPxls.begin();it!=prFgdPxls.end();++it)
                    circle(mask,*it,paint_width,GC_PR_FGD,-1);
                prLblsState=SET;
            }

            if(prLblsState==IN_PROCESS&&!isf)
            {
                for(it=prBgdPxls.begin();it!=prBgdPxls.end();++it)
                    circle(mask,*it,paint_width,GC_PR_BGD,-1);
                prLblsState=SET;
            }

        }
        else                               //[Manual Model]
        {

        }

        drawMouseMove=false;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(drawMouseMove)
    {
        Point pointTmp(event->x(),event->y());
        restrictPoint(pointTmp);

        if(autoModel)                     //[Auto Model]
        {
            if(rectState==IN_PROCESS)
            {
                img_cur.copyTo(img_cur_copy);
                rectangle(img_cur_copy,Point(rect.x,rect.y),Point(pointTmp.x,pointTmp.y),Scalar(0,0,255),1);
                displayMat(img_cur_copy);
            }

            if(lblsState==IN_PROCESS&&isf)
            {

                fgdPxls.push_back(pointTmp);
                circle(img_cur_copy,pointTmp,paint_width,Scalar(0,0,255),-1);

                Mat temp_show;
                addWeighted(img_cur,0.5,img_cur_copy,0.5,0,temp_show);
                displayMat(temp_show);
                //displayMat(img_cur_copy);
            }

            if(lblsState==IN_PROCESS&&!isf)
            {
                bgdPxls.push_back(pointTmp);
                circle(img_cur_copy,pointTmp,paint_width,Scalar(255,0,0),-1);

                Mat temp_show;
                addWeighted(img_cur,0.5,img_cur_copy,0.5,0,temp_show);
                displayMat(temp_show);
                // displayMat(img_cur_copy);
            }

            if(prLblsState==IN_PROCESS&&isf)
            {
                prFgdPxls.push_back(pointTmp);
                circle(img_cur_copy,pointTmp,paint_width,Scalar(230,130,255),-1);

                Mat temp_show;
                addWeighted(img_cur,0.5,img_cur_copy,0.5,0,temp_show);
                displayMat(temp_show);
                //displayMat(img_cur_copy);
            }

            if(prLblsState==IN_PROCESS&&!isf)
            {
                prBgdPxls.push_back(pointTmp);
                circle(img_cur_copy,pointTmp,paint_width,Scalar(255,255,160),-1);

                Mat temp_show;
                addWeighted(img_cur,0.5,img_cur_copy,0.5,0,temp_show);
                displayMat(temp_show);
                //displayMat(img_cur_copy);
            }
        }
        else                              //[Manual Model]
        {
            contour.push_back(pointTmp);
            drawConnects();
        }
    }
}

bool MainWindow::readImage()
{

    contour.clear();

    /* [old_v]
    imgInputPath.sprintf(inputPath.toStdString().c_str(),frameIdx,no_index);
    QDir *tempory_dir = new QDir(imgInputPath);
    QStringList filter;
    filter<<"*MaxIntensity.jpg";
    tempory_dir->setNameFilters(filter);
    QList<QFileInfo> *fileinfo = new QList<QFileInfo>(tempory_dir->entryInfoList(filter));
    prefix = fileinfo->at(0).absoluteFilePath();


    //get the real prefix,why real?dont ask me
    string filename = fileinfo->at(0).baseName().toStdString();
    size_t start =0,index =filename.find_first_of("M*",0);
    if(start!=index)
        real_prefix = QString::fromStdString(filename.substr(start,index-start));
    */


    prefix = imgInputPath.sprintf(inputPath.toStdString().c_str(),frameIdx).append(".jpg");
    //read  the origin image
    this->setWindowTitle(prefix);
    img_cur = imread(prefix.toStdString());
    WIDTH = img_cur.cols;
    HEIGHT = img_cur.rows;

    ui->label->setFixedHeight(HEIGHT);
    ui->label->setFixedWidth(WIDTH);
    img_cur.copyTo(img_rbrow);
    img_cur.copyTo(img_lbrow);
    img_cur.copyTo(img_reye);
    img_cur.copyTo(img_leye);
    img_cur.copyTo(img_nose);
    img_cur.copyTo(img_mouth);
    img_cur.copyTo(img_lear);
    img_cur.copyTo(img_rear);
    img_cur.copyTo(mix);
    img_cur.copyTo(alpha_channel);
    img_lbrow.setTo(0);
    img_leye.setTo(0);
    img_reye.setTo(0);
    img_nose.setTo(0);
    img_mouth.setTo(0);
    img_lear.setTo(0);
    img_rear.setTo(0);
    mix.setTo(0);
    alpha_channel.setTo(0);

    if(!img_cur.empty())
    {
        on_pushLBrowButton_clicked();
        img_cur.copyTo(img_pre);
        displayMat(img_cur);

        prSetDlg->setStartFrame(QString("%1").arg(frameIdx));

        mask.create(img_cur.size(),CV_8UC1);

        //read relative part of face
        QString path;

        // [old_v] path.sprintf(imgOutputDir.toStdString().c_str(),frameIdx,no_index);
        path.sprintf(imgOutputDir.toStdString().c_str(),frameIdx);

        QDir dir(path);
        if(!dir.exists())
            dir.mkdir(path);
        QFile fi;

        imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"lbrow");
        //QMessageBox::information(NULL,"Save Error",imgOutputPath,QMessageBox::Ok);
        fi.setFileName(imgOutputPath);
        if(fi.exists())
            img_lbrow = imread(imgOutputPath.toStdString());

        else
            img_lbrow.setTo(0);


        imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"rbrow");
        fi.setFileName(imgOutputPath);
        if(fi.exists())
            img_rbrow = imread(imgOutputPath.toStdString());

        else
            img_rbrow.setTo(0);

        imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"leye");
        fi.setFileName(imgOutputPath);
        if(fi.exists())
            img_leye = imread(imgOutputPath.toStdString());

        else
            img_leye.setTo(0);

        imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"reye");
        fi.setFileName(imgOutputPath);
        if(fi.exists())
            img_reye = imread(imgOutputPath.toStdString());

        else
            img_reye.setTo(0);

        imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"nose");
        fi.setFileName(imgOutputPath);
        if(fi.exists())
            img_nose = imread(imgOutputPath.toStdString());

        else
            img_nose.setTo(0);

        imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"mouth");
        fi.setFileName(imgOutputPath);
        if(fi.exists())
            img_mouth = imread(imgOutputPath.toStdString());

        else
            img_mouth.setTo(0);

        imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"lear");
        fi.setFileName(imgOutputPath);
        if(fi.exists())
            img_lear = imread(imgOutputPath.toStdString());

        else
            img_lear.setTo(0);

        imgOutputPath.sprintf((path+outputPath).toStdString().c_str(),"rear");
        fi.setFileName(imgOutputPath);
        if(fi.exists())
            img_rear = imread(imgOutputPath.toStdString());

        else
            img_rear.setTo(0);
        return true;
    }
    else
    {
        QMessageBox::information(NULL,"Read Failure","Failed To Read "+imgInputPath,QMessageBox::Ok,QMessageBox::Ok);
        return false;
    }

}

void MainWindow::nextImage()
{

}

void MainWindow::drawConnects()
{
    //img_pre.copyTo(img_cur);

    for(int i=0;i<contour.size();i++)
    {
        circle(img_cur_copy,contour.at(i),0,Scalar(0,0,255));
    }

    for(int i=1;i<contour.size();i++) // i=0;i<int(contour.size())-1;i++ ; Note Int ype
    {
        line(img_cur_copy,contour.at(i-1),contour.at(i),Scalar(0,0,255));
    }

    displayMat(img_cur_copy);
}


void MainWindow::contourFill()
{
    if(!contour.empty())
    {
        vector<vector<Point>> contours;
        if(!useHull)
        {
            approxPolyDP(contour,contour,0,true);
        }
        else
        {
            convexHull(Mat(contour),contour);
        }
        contours.push_back(contour);

        //img_pre.copyTo(img_cur);
        Mat temp;
        img_cur.copyTo(temp);
        img_cur.copyTo(img_cur_copy);
        temp.setTo(0);
        drawContours(temp, contours, -1, Scalar(1,1,1), CV_FILLED);

        img_cur_copy.setTo(0);
        img_cur.copyTo(img_cur_copy,temp);
        Mat temp_show;
        addWeighted(img_cur,0.5,img_cur_copy,0.5,0,temp_show);
        displayMat(temp_show);

        switch(STEP){
        case LBROW:
            img_cur_copy.copyTo(img_lbrow);
            break;
        case RBROW:
            img_cur_copy.copyTo(img_rbrow);
            break;
        case LEYE:
            img_cur_copy.copyTo(img_leye);
            break;
        case REYE:
            img_cur_copy.copyTo(img_reye);
            break;
        case NOSE:
            img_cur_copy.copyTo(img_nose);
            break;
        case MOUTH:
            img_cur_copy.copyTo(img_mouth);
            break;
        case LEAR:
            img_cur_copy.copyTo(img_lear);
            break;
        case REAR:
            img_cur_copy.copyTo(img_rear);
            break;
        }\

        contour.clear();
    }
}

void MainWindow::getBinMask(const Mat& comMask, Mat& binMask)
{
    if (comMask.empty() || comMask.type() != CV_8UC1)
        CV_Error(CV_StsBadArg, "ComMask Is Empty Or Has Incorrect Type (Not CV_8UC1)");
    if (binMask.empty() || binMask.rows != comMask.rows || binMask.cols != comMask.cols)
        binMask.create(comMask.size(), CV_8UC1);
    binMask = comMask & 1;
}

void MainWindow::resetAMParameters()
{
    if (!mask.empty())
        mask.setTo(Scalar::all(GC_BGD));
    bgdPxls.clear(); fgdPxls.clear();
    prBgdPxls.clear();  prFgdPxls.clear();
    contour.clear();

    isInitialized = false;
    rectState = NOT_SET;
    lblsState = NOT_SET;
    prLblsState = NOT_SET;
}

void MainWindow::restrictPoint(Point & _point)
{
    _point.x-=validRegion.x;
    _point.y-=validRegion.y;

    _point.x=_point.x>0?_point.x:0;
    _point.y=_point.y>0?_point.y:0;

    _point.x=_point.x<validRegion.width?_point.x:validRegion.width;
    _point.y=_point.y<validRegion.height?_point.y:validRegion.height;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    float xscale=ui->label->frameGeometry().width()/float(validRegion.width);
    float yscale=ui->label->frameGeometry().height()/float(validRegion.height);

    if(!contour.empty())
    {
        for(int i=0;i<contour.size();i++)
        {
            contour.at(i).x*=xscale;
            contour.at(i).y*=yscale;
        }
    }

    if(rectState==SET)
    {
        rect.x*=xscale;
        rect.y*=yscale;
        rect.width*=xscale;
        rect.height*=yscale;
    }

    vector<Point>::iterator it;
    for(it=fgdPxls.begin();it!=fgdPxls.end();++it)
    {
        (*it).x*=xscale;
        (*it).y*=yscale;
    }
    for(it=bgdPxls.begin();it!=bgdPxls.end();++it)
    {
        (*it).x*=xscale;
        (*it).y*=yscale;
    }
    for(it=prFgdPxls.begin();it!=prFgdPxls.end();++it)
    {
        (*it).x*=xscale;
        (*it).y*=yscale;
    }
    for(it=prBgdPxls.begin();it!=prBgdPxls.end();++it)
    {
        (*it).x*=xscale;
        (*it).y*=yscale;
    }

    validRegion.x=ui->label->frameGeometry().x();
    validRegion.y=ui->label->frameGeometry().y()+10;
    validRegion.height=ui->label->frameGeometry().height();
    validRegion.width=ui->label->frameGeometry().width();

    if(!img_cur.empty())
    {
        cv::Size sz=cv::Size(validRegion.width,validRegion.height);
        //cv::resize(img_pre,img_pre,sz);
        cv::resize(img_cur,img_cur,sz);
    }

    if(!mask.empty()&&!img_cur_copy.empty())
    {
        cv::Size sz=cv::Size(validRegion.width,validRegion.height);
        cv::resize(mask,mask,sz);
        cv::resize(img_cur_copy,img_cur_copy,sz);
    }

}

void MainWindow::timerEvent(QTimerEvent *event)
{
    curTime=QDateTime::currentDateTime();
    qint64 elapsedSec=startTime.msecsTo(curTime)/1000;
    ui->frameshowLabel->setText(QString("%1  %2  %3:%4:%5").arg(frameIdx).arg(frameIdx-startIdx).arg(elapsedSec/3600).arg((elapsedSec%3600)/60).arg(elapsedSec%60));
}

void MainWindow::on_pushLBrowButton_clicked()
{
    STEP = LBROW;
    ui->pushLBrowButton->setEnabled(false);
    ui->pushRBrowButton->setEnabled(true);
    ui->pushLEyeButton->setEnabled(true);
    ui->pushREyeButton->setEnabled(true);
    ui->pushNoseButton->setEnabled(true);
    ui->pushMouthButton->setEnabled(true);
    ui->pushLEarButton->setEnabled(true);
    ui->pushREarButton->setEnabled(true);
    if(!img_cur.empty())
        displayMat(img_cur);
    resetAMParameters();
}

void MainWindow::on_pushRBrowButton_clicked()
{
    STEP = RBROW;
    ui->pushLBrowButton->setEnabled(true);
    ui->pushRBrowButton->setEnabled(false);
    ui->pushLEyeButton->setEnabled(true);
    ui->pushREyeButton->setEnabled(true);
    ui->pushNoseButton->setEnabled(true);
    ui->pushMouthButton->setEnabled(true);
    ui->pushLEarButton->setEnabled(true);
    ui->pushREarButton->setEnabled(true);
    if(!img_cur.empty())
        displayMat(img_cur);
    resetAMParameters();
}

void MainWindow::on_pushLEyeButton_clicked()
{
    STEP = LEYE;
    ui->pushLBrowButton->setEnabled(true);
    ui->pushRBrowButton->setEnabled(true);
    ui->pushLEyeButton->setEnabled(false);
    ui->pushREyeButton->setEnabled(true);
    ui->pushNoseButton->setEnabled(true);
    ui->pushMouthButton->setEnabled(true);
    ui->pushLEarButton->setEnabled(true);
    ui->pushREarButton->setEnabled(true);
    if(!img_cur.empty())
        displayMat(img_cur);
    resetAMParameters();
}

void MainWindow::on_pushREyeButton_clicked()
{
    STEP = REYE;
    ui->pushLBrowButton->setEnabled(true);
    ui->pushRBrowButton->setEnabled(true);
    ui->pushLEyeButton->setEnabled(true);
    ui->pushREyeButton->setEnabled(false);
    ui->pushNoseButton->setEnabled(true);
    ui->pushMouthButton->setEnabled(true);
    ui->pushLEarButton->setEnabled(true);
    ui->pushREarButton->setEnabled(true);
    if(!img_cur.empty())
        displayMat(img_cur);
    resetAMParameters();
}

void MainWindow::on_pushNoseButton_clicked()
{
    STEP = NOSE;
    ui->pushLBrowButton->setEnabled(true);
    ui->pushRBrowButton->setEnabled(true);
    ui->pushLEyeButton->setEnabled(true);
    ui->pushREyeButton->setEnabled(true);
    ui->pushNoseButton->setEnabled(false);
    ui->pushMouthButton->setEnabled(true);
    ui->pushLEarButton->setEnabled(true);
    ui->pushREarButton->setEnabled(true);
    if(!img_cur.empty())
        displayMat(img_cur);
    resetAMParameters();
}

void MainWindow::on_pushMouthButton_clicked()
{
    STEP = MOUTH;
    ui->pushLBrowButton->setEnabled(true);
    ui->pushRBrowButton->setEnabled(true);
    ui->pushLEyeButton->setEnabled(true);
    ui->pushREyeButton->setEnabled(true);
    ui->pushNoseButton->setEnabled(true);
    ui->pushMouthButton->setEnabled(false);
    ui->pushLEarButton->setEnabled(true);
    ui->pushREarButton->setEnabled(true);
    if(!img_cur.empty())
        displayMat(img_cur);
    resetAMParameters();
}

void MainWindow::on_pushLEarButton_clicked()
{
    STEP = LEAR;
    ui->pushLBrowButton->setEnabled(true);
    ui->pushRBrowButton->setEnabled(true);
    ui->pushLEyeButton->setEnabled(true);
    ui->pushREyeButton->setEnabled(true);
    ui->pushNoseButton->setEnabled(true);
    ui->pushMouthButton->setEnabled(true);
    ui->pushLEarButton->setEnabled(false);
    ui->pushREarButton->setEnabled(true);
    if(!img_cur.empty())
        displayMat(img_cur);
    resetAMParameters();
}

void MainWindow::on_pushREarButton_clicked()
{
    STEP = REAR;
    ui->pushLBrowButton->setEnabled(true);
    ui->pushRBrowButton->setEnabled(true);
    ui->pushLEyeButton->setEnabled(true);
    ui->pushREyeButton->setEnabled(true);
    ui->pushNoseButton->setEnabled(true);
    ui->pushMouthButton->setEnabled(true);
    ui->pushLEarButton->setEnabled(true);
    ui->pushREarButton->setEnabled(false);
    if(!img_cur.empty())
        displayMat(img_cur);
    resetAMParameters();
}

void MainWindow::on_pushShowMaskButton_clicked()
{
    switch(STEP){
    case LBROW:
        if(!img_lbrow.empty())
            displayMat(img_lbrow);
        break;
    case RBROW:
        if(!img_rbrow.empty())
            displayMat(img_rbrow);
        break;
    case LEYE:
        if(!img_leye.empty())
            displayMat(img_leye);
        break;
    case REYE:
        if(!img_reye.empty())
            displayMat(img_reye);
        break;
    case NOSE:
        if(!img_nose.empty())
            displayMat(img_nose);
        break;
    case MOUTH:
        if(!img_mouth.empty())
            displayMat(img_mouth);
        break;
    case LEAR:
        if(!img_lear.empty())
            displayMat(img_lear);
        break;
    case REAR:
        if(!img_rear.empty())
            displayMat(img_rear);
        break;
    }\
}

void MainWindow::on_pushShowOriginButton_clicked()
{
    if(!img_cur.empty())
        displayMat(img_cur);
}

void MainWindow::on_pushSkinButton_clicked()
{
    Mat skin;
    skin = img_lbrow + img_rbrow + img_leye + img_reye + img_nose + img_mouth + img_lear + img_rear;
    Mat gray;
    Mat temp_mask;


    temp_mask.create(skin.size(), CV_8UC1);
    cvtColor(skin,gray,CV_BGR2GRAY);
    getBinMask(gray,temp_mask);


    //QMessageBox::information(NULL,"skin",q,QMessageBox::Ok);
    //skin.copyTo(temp_mask);


    //debug lines
    //str1 = std::to_string(temp_mask.cols);
    //str2 = std::to_string(temp_mask.rows);
    //str1.append(str2);
    //q = QString::fromStdString( str1);

    //QMessageBox::information(NULL,"skin",q,QMessageBox::Ok);
    img_cur.copyTo(skin,temp_mask);

    displayMat(skin);
}

int MainWindow::heightForWidth(const int w){
    return w;
}

void MainWindow::on_pushMixButton_clicked()
{
    //12 different part
    //#1 background #2 up_body #3 face #4 hair #5 left brow # 6 right brow
    //#7 left eye #8 right eye #9 nose #10 mouth #11 left ear #12 right ear
    Mat temp_mask(HEIGHT,WIDTH,CV_8UC1,Scalar(0,0,0)); //used as mask

    vector<Mat> channels;

    mix.setTo(0);

    Mat FG(HEIGHT,WIDTH,CV_8UC3,Scalar(0,0,0));
    Mat Face(HEIGHT,WIDTH,CV_8UC3,Scalar(0,0,0));
    Mat Hair(HEIGHT,WIDTH,CV_8UC3,Scalar(0,0,0));

    /* [old_v]
    imgInputPath.sprintf(inputPath.toStdString().c_str(),frameIdx,no_index);
    Face = imread(imgInputPath.append("//").append(real_prefix).append("Face.jpg").toStdString().c_str());
    imgInputPath.sprintf(inputPath.toStdString().c_str(),frameIdx,no_index);
    FG = imread(imgInputPath.append("//").append(real_prefix).append("FG.jpg").toStdString().c_str());
    imgInputPath.sprintf(inputPath.toStdString().c_str(),frameIdx,no_index);
    Hair = imread(imgInputPath.append("//").append(real_prefix).append("Hair.jpg").toStdString().c_str());
    */

    imgInputPath.sprintf(inputPath.toStdString().c_str(),frameIdx);
    Face = imread(imgInputPath.append("_Face.jpg").toStdString().c_str());
    imgInputPath.sprintf(inputPath.toStdString().c_str(),frameIdx);
    FG = imread(imgInputPath.append("_FG.jpg").toStdString().c_str());
    imgInputPath.sprintf(inputPath.toStdString().c_str(),frameIdx);
    Hair = imread(imgInputPath.append("_Hair.jpg").toStdString().c_str());




    //read three other part of the image,deprecated after one day
    Mat face(HEIGHT,WIDTH,CV_8UC3,Scalar(0,0,0));
    Mat hair(HEIGHT,WIDTH,CV_8UC3,Scalar(0,0,0));
    Mat body(HEIGHT,WIDTH,CV_8UC3,Scalar(0,0,0));

    split(Face,channels);
    channels.at(0).setTo(0);
    channels.at(1).setTo(0);
    cv::threshold(channels.at(2),channels.at(2),face_thresh,255,CV_THRESH_BINARY);
    merge(channels,Face);

    split(FG,channels);
    channels.at(1).setTo(0);
    channels.at(2).setTo(0);
    cv::threshold(channels.at(0),channels.at(0),200,255,CV_THRESH_BINARY);
    merge(channels,FG);

    //QMessageBox::information(NULL,"Save Error",QString::fromStdString(std::to_string(Face.cols).append(std::to_string(Face.rows))),QMessageBox::Ok);
    //#1&2 add the body and the face
    turn_to_mask(Face,temp_mask,0);
    Face.copyTo(FG,temp_mask);
    FG.copyTo(mix);

    //#3 add the lbrow
    cut_the_glass(Face,img_lbrow);  // cut the glass out
    turn_to_mask(img_lbrow,temp_mask,0);
    cut_pure_color(LBROW_COLOR ,face,temp_mask);
    face.copyTo(mix,temp_mask);

    //#4 add the rbrow
    cut_the_glass(Face,img_rbrow);  // cut the glass out
    turn_to_mask(img_rbrow,temp_mask,0);
    cut_pure_color(RBROW_COLOR ,face,temp_mask);
    face.copyTo(mix,temp_mask);
    //cv::namedWindow("d");
    //cv::imshow("d", img_leye);

    //#5 add the leye
    cut_the_glass(Face,img_leye);   // cut the glass out
    turn_to_mask(img_leye,temp_mask,0);
    cut_pure_color(LEYE_COLOR ,face,temp_mask);
    face.copyTo(mix,temp_mask);

    //#6 add the reye
    cut_the_glass(Face,img_reye);   // cut the glass out
    turn_to_mask(img_reye,temp_mask,0);
    cut_pure_color(REYE_COLOR ,face,temp_mask);
    face.copyTo(mix,temp_mask);

    //#7 add the nose
    cut_the_glass(Face,img_nose);       // cut the glass out
    turn_to_mask(img_nose,temp_mask,0);
    cut_pure_color(NOSE_COLOR ,face,temp_mask);
    face.copyTo(mix,temp_mask);

    //#8 add the mouth
    turn_to_mask(img_mouth,temp_mask,0);
    cut_pure_color(MOUTH_COLOR ,face,temp_mask);
    face.copyTo(mix,temp_mask);

    //#9 add the lear
    turn_to_mask(img_lear,temp_mask,0);
    cut_pure_color(LEAR_COLOR ,face,temp_mask);
    face.copyTo(mix,temp_mask);

    //#10 add the rear
    turn_to_mask(img_rear,temp_mask,0);
    cut_pure_color(REAR_COLOR ,face,temp_mask);
    face.copyTo(mix,temp_mask);

    //#11 add the hair
    turn_to_mask(Hair,temp_mask,hair_thresh);

        //turn one channel to max ,that is 255 if pixel larger than 0
    split(Hair,channels);
    channels.at(0).setTo(0);
    channels.at(2).setTo(0);

            //deal with the alpha channel
            alpha_channel.setTo(255);
            channels.at(1).copyTo(alpha_channel,temp_mask);
            //namedWindow("d",1);
            //imshow("d",alpha_channel);

    cv::threshold(channels.at(1),channels.at(1),0,255,CV_THRESH_BINARY);
    merge(channels,Hair);
    Hair.copyTo(mix,temp_mask);

    cv::addWeighted(mix,0.5,img_cur,0.5,0,face);
    displayMat(face);

    ui->savePushButton->setEnabled(true);
    return;

        //imgInputPath.sprintf(inputPath.toStdString().c_str(),frameIdx,no_index);
        //face = imread(imgInputPath.append("//face_alpha.jpg").toStdString().c_str());
        //imgInputPath.sprintf(inputPath.toStdString().c_str(),frameIdx,no_index);
        //hair = imread(imgInputPath.append("//hair_alpha.jpg").toStdString().c_str());
        //imgInputPath.sprintf(inputPath.toStdString().c_str(),frameIdx,no_index);
        //body = imread(imgInputPath.append("//body_alpha.jpg").toStdString().c_str());

    /*merge method one  , based on cur and then merge , it is deprecated now*/
    /*
    //#1 add the body
    turn_to_mask(Face,temp_mask,0);
    FG.copyTo(mix,temp_mask^1);

    //#2 add the face
    turn_to_mask(Hair,temp_mask,0);
    body.setTo(0);
    Face.copyTo(body,temp_mask^1);
    turn_to_mask(body,temp_mask,25);
    body.copyTo(mix,temp_mask);

    //#3 add the hair
    turn_to_mask(Hair,temp_mask,0);
    hair.copyTo(mix,temp_mask);

    displayMat(mix);
    */

    //deal with alpha channel
    //alpha_channel.setTo(255);
    //channels.at(0).copyTo(alpha_channel,temp_mask);


    //hair have the highest priority
    //so do some special thing
    //Mat temp_temp_mask(480,640,CV_8UC3,Scalar(0,0,0));
    //turn_to_mask(mix , temp_mask,0);
    //face.setTo(0);
    //hair.copyTo(face,temp_mask);
}

//select the mask depend on the threadhold
void MainWindow::turn_to_mask(const Mat &com,Mat &to,double x=0)
{
    Mat temp(HEIGHT,WIDTH,CV_8UC1,Scalar(0,0,0));
    cvtColor(com,temp,CV_BGR2GRAY);
    cv::threshold(temp,to,x,1,CV_THRESH_BINARY);
}
void MainWindow::cut_pure_color(Scalar rgb,Mat & src,Mat & mask)
{
    src.setTo(0);
    Mat pure(HEIGHT,WIDTH,CV_8UC3,rgb);
    pure.copyTo(src,mask);
}
void MainWindow::cut_the_glass(const Mat &Face,Mat &src)
{
    Mat temp_mask(HEIGHT,WIDTH,CV_8UC1,Scalar(0,0,0));
    Mat temp(HEIGHT,WIDTH,CV_8UC3,Scalar(0,0,0));
    turn_to_mask(Face,temp_mask,0);
    src.copyTo(temp);
    src.setTo(0);
    temp.copyTo(src,temp_mask);
}

void MainWindow::on_horizontalSlider_rangeChanged(int min, int max)
{

}

//change the thresh_hold of the hair
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    hair_thresh = value;
}

void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    face_thresh = value;
}
