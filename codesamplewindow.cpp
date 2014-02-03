#include "codesamplewindow.h"
#include "ui_codesamplewindow.h"
#include "wallmodel.h"
#include	 <QObject>
#include <QMovie>
#include <string>
#include <QTimer>
using namespace std;

CodeSampleWindow::CodeSampleWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::CodeSampleWindow)
{
	model = new WallModel();
	ui->setupUi(this);
	connect((QObject *)model,SIGNAL(treeState()),this,SLOT(updateTreeStatus()));
	connect((QObject *)model,SIGNAL(comparisonState()),this,SLOT(updateComparisonStatus()));
	connect((QObject *)model,SIGNAL(resultState()),this,SLOT(updateResults()));
}

CodeSampleWindow::~CodeSampleWindow()
{
	delete ui;
}

void CodeSampleWindow::on_execButton_clicked()
{
	ui->widthBox->setEnabled(false);
	model->setWallWidth(ui->widthBox->text().toFloat());

	ui->heightBox->setEnabled(false);
	model->setWallHeight(ui->heightBox->text().toInt());

	ui->execButton->setEnabled(false);
	model->build();
}

void CodeSampleWindow::updateTreeStatus()
{

	QMovie *movie = new QMovie(":/icons/treegrow.gif");
	ui->treeAnimationLabel->setMovie(movie);
	movie->start();
	ui->treeStatusLabel->setText("Calculating the possible block combinations for a single layer");
}

void CodeSampleWindow::animationDelay(int length)
{
	QEventLoop loop;
	QTimer::singleShot(length, &loop, SLOT(quit()));
	loop.exec();
}

void CodeSampleWindow::updateComparisonStatus()
{
	animationDelay(ui->heightBox->text().toInt()*1000);

	ui->treeAnimationLabel->setPixmap(QPixmap(":/icons/complete.gif"));
	ui->treeStatusLabel->setText("Calculation complete");

	animationDelay(1000);

	QMovie *movie = new QMovie(":/icons/scales.gif");
	ui->comparisonAnimationLabel->setMovie(movie);
	movie->start();
	ui->comparisonStatusLabel->setText("Comparing Layers for Compatiblity");

}

void CodeSampleWindow::updateResults()
{

	ui->comparisonAnimationLabel->setPixmap(QPixmap(":/icons/complete.gif"));

	ui->comparisonStatusLabel->setText("Comparisons complete");
	ui->layerNumberLabel->setText(QString::number(model->getLayerCount()));
	ui->comboNumberLabel->setText(QString::number(model->getCombinationCount()));
	ui->heightBox->setEnabled(true);
	ui->widthBox->setEnabled(true);
	ui->execButton->setEnabled(true);
}
