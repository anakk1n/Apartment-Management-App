#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ApartmentManagement.h"
#include <QtCore/QObject>

class ApartmentManagement : public QMainWindow
{
    Q_OBJECT

public:
    ApartmentManagement(QWidget *parent = Q_NULLPTR);

private:
    Ui::ApartmentManagementClass ui;
};
