#include "widget.h"

#include <QApplication>

/*
 * @brief : Manually write code to implement event-related interfaces
 * @author: potba
 *
 * */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
