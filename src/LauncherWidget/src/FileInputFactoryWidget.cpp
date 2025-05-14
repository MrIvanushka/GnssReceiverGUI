#include "FileInputFactoryWidget.h"

#include "FileInput.h"
#include "Log.h"
#include <QFormLayout>
#include <QFileDialog>

using namespace Editor::GUI;

FileInputFactoryWidget::FileInputFactoryWidget()
{
	setTitle(QString::fromLocal8Bit("������������ ������ �� �����"));

	auto lay = new QFormLayout;
	setLayout(lay);

	_sigsPath = new QPushButton("");
	QObject::connect(_sigsPath, &QPushButton::clicked, this, &FileInputFactoryWidget::selectSigsFile);
	_absoluteShiftPath = new QPushButton("");
	QObject::connect(_absoluteShiftPath, &QPushButton::clicked, this, &FileInputFactoryWidget::selectAbsoluteShiftFile);
	lay->addRow(QString::fromLocal8Bit("������� ��������"), _sigsPath);
	lay->addRow(QString::fromLocal8Bit("��������� ����� �����"), _absoluteShiftPath);
}

QString FileInputFactoryWidget::name() const
{
	return _name;
}

std::shared_ptr<Editor::IEditorDataInput> FileInputFactoryWidget::makeInput() const
{
	if (_sigsPath->text() == "")
	{
		LOG_ERROR("Input file is not initialized!");
		return nullptr;
	}
	if (_absoluteShiftPath->text() == "")
	{
		LOG_ERROR("Timestamps file is not initialized!");
		return nullptr;
	}
	return std::make_shared<FileInput>(_chosenSigsPath, _chosenAbsoluteShiftPath);
}

void FileInputFactoryWidget::selectSigsFile()
{
	_chosenSigsPath = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("������ ��������"), "c:/", QString::fromLocal8Bit("������ �������� ������� (*.rec)"));

	if (!_chosenSigsPath.isFile())
		return;

	auto pathText = _chosenSigsPath.absoluteFilePath();
	if (pathText.size() > 33)
		_sigsPath->setText(QString("...") + pathText.remove(0, pathText.size() - 30));
	else
		_sigsPath->setText(pathText);
}

void FileInputFactoryWidget::selectAbsoluteShiftFile()
{
	_chosenAbsoluteShiftPath = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("������ ��������� �����"), "c:/", QString::fromLocal8Bit("������ ��������� ����� (*.times)"));

	if (!_chosenAbsoluteShiftPath.isFile())
		return;

	auto pathText = _chosenAbsoluteShiftPath.absoluteFilePath();
	if (pathText.size() > 33)
		_absoluteShiftPath->setText(QString("...") + pathText.remove(0, pathText.size() - 30));
	else
		_absoluteShiftPath->setText(pathText);
}