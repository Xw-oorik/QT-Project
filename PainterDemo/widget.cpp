#include "widget.h"
#include "ui_widget.h"
#include <QColorDialog>
#include <QPen>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //形状初始化
    ui->pictureshapecomboBox->addItem("Point",static_cast<int>(Shape::_Point));
    ui->pictureshapecomboBox->addItem("Line",static_cast<int>(Shape::_Line));
    ui->pictureshapecomboBox->addItem("Rectangle", static_cast<int>(Shape::_Rect));
    ui->pictureshapecomboBox->addItem("Rounded Rectangle", static_cast<int>(Shape::_RoundedRect));
    ui->pictureshapecomboBox->addItem("Ellipse", static_cast<int>(Shape::_Ellipse));

    ui->pictureshapecomboBox->addItem("Arc", static_cast<int>(Shape::_Arc));
    ui->pictureshapecomboBox->addItem("Pie", static_cast<int>(Shape::_Pie));
    ui->pictureshapecomboBox->addItem("Chord", static_cast<int>(Shape::_Chord));

    ui->pictureshapecomboBox->addItem("Polyline", static_cast<int>(Shape::_Polyline));
    ui->pictureshapecomboBox->addItem("Polygon", static_cast<int>(Shape::_Polygon));

    ui->pictureshapecomboBox->addItem("Path", static_cast<int>(Shape::_Path));

    ui->pictureshapecomboBox->addItem("Text", static_cast<int>(Shape::_Text));
    ui->pictureshapecomboBox->addItem("Pixmap", static_cast<int>(Shape::_Pixmap));
    //宽度
    ui->widthspinBox->setRange(1,10);
    //画笔样式
    ui->stylecomboBox->addItem("SolidLine",static_cast<int>(Qt::SolidLine));
    ui->stylecomboBox->addItem("DashLine",static_cast<int>(Qt::DashLine));
    ui->stylecomboBox->addItem("DotLine",static_cast<int>(Qt::DotLine));
    ui->stylecomboBox->addItem("DashDotLine",static_cast<int>(Qt::DashDotLine));
    ui->stylecomboBox->addItem("DashDotDotLine",static_cast<int>(Qt::DashDotDotLine));
    ui->stylecomboBox->addItem("None",static_cast<int>(Qt::NoPen));
    //画笔连接

    ui->connectcomboBox->addItem("FlatCap", static_cast<int>(Qt::FlatCap));
    ui->connectcomboBox->addItem("SquareCap", static_cast<int>(Qt::SquareCap));
    ui->connectcomboBox->addItem("RoundCap", static_cast<int>(Qt::RoundCap));

    //画笔末端,两根线的连接处的样式
    ui->extremitycomboBox->addItem("MiterJoin", static_cast<int>(Qt::MiterJoin));
    ui->extremitycomboBox->addItem("BevelJoin", static_cast<int>(Qt::BevelJoin));
    ui->extremitycomboBox->addItem("RoundJoin", static_cast<int>(Qt::RoundJoin));
    //画刷样式
    ui->stylebrushcomboBox->addItem(tr("Linear Gradient"), static_cast<int>(Qt::LinearGradientPattern));
    ui->stylebrushcomboBox->addItem(tr("Radial Gradient"), static_cast<int>(Qt::RadialGradientPattern));
    ui->stylebrushcomboBox->addItem(tr("Conical Gradient"), static_cast<int>(Qt::ConicalGradientPattern));
    ui->stylebrushcomboBox->addItem(tr("Texture"), static_cast<int>(Qt::TexturePattern));
    ui->stylebrushcomboBox->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
    ui->stylebrushcomboBox->addItem(tr("Horizontal"), static_cast<int>(Qt::HorPattern));
    ui->stylebrushcomboBox->addItem(tr("Vertical"), static_cast<int>(Qt::VerPattern));
    ui->stylebrushcomboBox->addItem(tr("Cross"), static_cast<int>(Qt::CrossPattern));
    ui->stylebrushcomboBox->addItem(tr("Backward Diagonal"), static_cast<int>(Qt::BDiagPattern));
    ui->stylebrushcomboBox->addItem(tr("Forward Diagonal"), static_cast<int>(Qt::FDiagPattern));
    ui->stylebrushcomboBox->addItem(tr("Diagonal Cross"), static_cast<int>(Qt::DiagCrossPattern));
    ui->stylebrushcomboBox->addItem(tr("Dense 1"), static_cast<int>(Qt::Dense1Pattern));
    ui->stylebrushcomboBox->addItem(tr("Dense 2"), static_cast<int>(Qt::Dense2Pattern));
    ui->stylebrushcomboBox->addItem(tr("Dense 3"), static_cast<int>(Qt::Dense3Pattern));
    ui->stylebrushcomboBox->addItem(tr("Dense 4"), static_cast<int>(Qt::Dense4Pattern));
    ui->stylebrushcomboBox->addItem(tr("Dense 5"), static_cast<int>(Qt::Dense5Pattern));
    ui->stylebrushcomboBox->addItem(tr("Dense 6"), static_cast<int>(Qt::Dense6Pattern));
    ui->stylebrushcomboBox->addItem(tr("Dense 7"), static_cast<int>(Qt::Dense7Pattern));

    //绑定槽函数
    //形状
    connect(ui->pictureshapecomboBox,& QComboBox::textActivated,this,&Widget::shapeChanged);
    //画笔
    connect(ui->widthspinBox,QOverload<int>::of(&QSpinBox::valueChanged),this,&Widget::penChanged);
    connect(ui->pushButton,&QPushButton::clicked,this,&Widget::onbtnPenClicked);
    connect(ui->stylecomboBox,& QComboBox::textActivated,this,&Widget::penChanged);
    connect(ui->connectcomboBox,& QComboBox::textActivated,this,&Widget::penChanged);
    connect(ui->extremitycomboBox,& QComboBox::textActivated,this,&Widget::penChanged);
    //画刷
    connect(ui->stylebrushcomboBox,& QComboBox::textActivated,this,&Widget::brushChanged);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&Widget::onbtnBrushClicked);
    //抗锯齿
    connect(ui->antialiasingcheckBox,&QCheckBox::stateChanged,this,&Widget::onantialiasingChanged);
    //移动旋转
    connect(ui->transfromcheckBox,&QCheckBox::stateChanged,this,&Widget::tranfromChanged);
    //初始化
    QPalette pal=ui->pushButton->palette();
    pal.setColor(QPalette::Button,QColor(240,128,64));
    ui->pushButton->setPalette(pal);
    ui->pushButton->setFlat(true);
    ui->pushButton->setAutoFillBackground(true);

    QPalette pals=ui->pushButton_2->palette();
    pals.setColor(QPalette::Button,QColor(64,128,125));
    ui->pushButton_2->setPalette(pals);
    ui->pushButton_2->setAutoFillBackground(true);
    ui->pushButton_2->setFlat(true);

    brushChanged();

    penChanged();

    shapeChanged();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::shapeChanged()
{
    //拿到哪一项
    int idx=ui->pictureshapecomboBox->currentIndex();
    Shape shape=(Shape)ui->pictureshapecomboBox->itemData(idx).toInt();
    //给paintewidget去绘制
    ui->paintwidget->setShape(shape);

}

void Widget::penChanged()
{

    int width=ui->widthspinBox->value();
    //获取画笔颜色
    QPalette pal=ui->pushButton->palette();
    QColor pencolor=pal.color(QPalette::Button);

    int styleidx=ui->stylecomboBox->currentIndex();
    Qt::PenStyle penstyle=(Qt::PenStyle)ui->stylecomboBox->itemData(styleidx).toInt();

    int capidx=ui->connectcomboBox->currentIndex();
    Qt::PenCapStyle capstyle=(Qt::PenCapStyle)ui->connectcomboBox->itemData(capidx).toInt();

    int joinidx=ui->extremitycomboBox->currentIndex();
    Qt::PenJoinStyle joinstyle=(Qt::PenJoinStyle)ui->extremitycomboBox->itemData(joinidx).toInt();


    ui->paintwidget->setPen(QPen(pencolor,width,penstyle,capstyle,joinstyle));

}

void Widget::onbtnPenClicked()
{
    QColor color=QColorDialog::getColor(QColor(255,0,255),this,"画笔颜色");
    if(!color.isValid()){
        return ;
    }
    //回显画笔的颜色到btn上
    QPalette pal=ui->pushButton->palette();
    pal.setColor(QPalette::Button,color);
    ui->pushButton->setPalette(pal);
    ui->pushButton->setAutoFillBackground(true);
    ui->pushButton->setFlat(true);

    //画笔的改变
    penChanged();
}

void Widget::brushChanged()
{
    QPalette pal=ui->pushButton_2->palette();
    QColor color=pal.color(QPalette::Button);

    int idx=ui->stylebrushcomboBox->currentIndex();
    Qt::BrushStyle brushstyle=(Qt::BrushStyle)ui->stylebrushcomboBox->itemData(idx).toInt();
    if(brushstyle==Qt::LinearGradientPattern)
    {
        QLinearGradient lad(0,50,100,50);
        lad.setColorAt(0.0,Qt::white);
        lad.setColorAt(0.2,color);
        lad.setColorAt(1.0,Qt::black);
        ui->paintwidget->setBrush(lad);
    }
    else if(brushstyle==Qt::RadialGradientPattern)
    {
        QRadialGradient radialGradient(50, 50, 50, 70, 70);
        radialGradient.setColorAt(0.0, Qt::white);
        radialGradient.setColorAt(0.2, color);
        radialGradient.setColorAt(1.0, Qt::black);
        ui->paintwidget->setBrush(radialGradient);

    }
    else if(brushstyle==Qt::ConicalGradientPattern)
    {
        QConicalGradient conicalGradient(50, 50, 150);
        conicalGradient.setColorAt(0.0, Qt::white);
        conicalGradient.setColorAt(0.2, color);
        conicalGradient.setColorAt(1.0, Qt::black);
        ui->paintwidget->setBrush(conicalGradient);

    }
    else if(brushstyle==Qt::TexturePattern)
    {
        ui->paintwidget->setBrush(QBrush(QPixmap(":/images/2-1.png")));
    }
    else {
        ui->paintwidget->setBrush(QBrush(color,brushstyle));
    }

}

void Widget::onbtnBrushClicked()
{
    QColor color=QColorDialog::getColor(QColor(64,128,255),this,"画刷颜色");
    if(!color.isValid()){
        return ;
    }
    //回显画刷的颜色到btn上
    QPalette pal=ui->pushButton_2->palette();
    pal.setColor(QPalette::Button,color);
    ui->pushButton_2->setPalette(pal);
    ui->pushButton_2->setAutoFillBackground(true);
    ui->pushButton_2->setFlat(true);
    //画刷改变
    brushChanged();
}

void Widget::onantialiasingChanged()
{
    ui->paintwidget->setAntialias((Qt::CheckState)ui->antialiasingcheckBox->checkState());

}

void Widget::tranfromChanged()
{
    ui->paintwidget->setMove_Tranfrom((Qt::CheckState)ui->transfromcheckBox->checkState());
}

