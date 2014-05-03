#include <QCoreApplication>
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << "lol" << std::endl;
    exit(1);
    return a.exec();
}
