#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QTimer>
#include "codehighlighter.h"
#include "json_highlighter.h"
#include "devicehighlighter.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    //代码高亮
    QTextEdit * codeEditor;

    QButtonGroup * codeRadioGroup;
    QCheckBox * chkCode;
    QRadioButton * btnCodeBrowse;
    QRadioButton * radioKeyboard;
    CodeHighlighter *codeHighlight;
    //模拟键盘输入要用
    QString codeString;
    int codeCharIndex;
    QTimer * codetimer;

    //json
    QTextEdit* jsonEditor;
    JsonHighlighter* jsonHighlighter;
    QButtonGroup* jsonRadioGroup;
    QCheckBox * jsonCode;
    QRadioButton* btnJsonBrowse;
    QRadioButton* radioJsonKeyboard;
    QString jsonString;
    int jsonCharIndex;
    QTimer * jsontimer;

    // 下位机数据高亮
    QTextEdit* deviceEditor;
    QCheckBox * devicechkbox;
    QPushButton * startaccept;
    QPushButton * cleardata;
    QTimer * deviceTimer;
    DeviceHighlighter* deviceHighlighter;
    static QString codeFilePath;  // 用于保存代码文件路径
    static QString jsonFilePath;  // 用于保存 JSON 文件路径
private:
    void loadFile(QTextEdit * textEdit,const QString &filename);
    void connection();
private slots:
    void codetimeout();
    void jsontimeout();
    void onDeviceTimeout();
};
#endif // WIDGET_H
