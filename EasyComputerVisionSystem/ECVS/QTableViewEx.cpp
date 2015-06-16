#include "QTableViewEx.h"
#include <Qevent>
#include <QMouseEvent>
#include <windows.h>
#include <QStandardItemModel>
QTableViewEx::QTableViewEx(QWidget *parent)
: QTableView(parent)
{
	m_nMouseDownIndex = -1;
	m_nMouseUpIndex = -1;
	m_nPreIndex = -1;
}

QTableViewEx::~QTableViewEx()
{

}

void	QTableViewEx::mouseMoveEvent(QMouseEvent * event)
{
	__super::mouseMoveEvent(event);
	if (event->buttons() & Qt::LeftButton)
	{
		QModelIndex curIndex = currentIndex();
		if (curIndex.row() != m_nPreIndex)
		{
			QStandardItemModel * pModel = (QStandardItemModel *)model();
			QString strPre = pModel->item(m_nPreIndex)->text();
			QString strCur = pModel->item(curIndex.row())->text();
			pModel->item(curIndex.row())->setText(strPre);



			int nAdd = (m_nPreIndex - curIndex.row()) > 0 ? 1 : -1;
			int i = curIndex.row();
			do 
			{
				i += nAdd;
				strPre = pModel->item(i)->text();
				pModel->item(i)->setText(strCur);
				strCur = strPre;
				
			} while (i != m_nPreIndex);

		//	pModel->item(m_nPreIndex)->setText(strCur);
		


			m_nPreIndex = curIndex.row();
		}
	}


}
void	QTableViewEx::mousePressEvent(QMouseEvent * event)
{
	__super::mousePressEvent(event);
	
	QModelIndex selectedIndex = this->currentIndex();
	m_nMouseDownIndex = selectedIndex.row();
	m_nPreIndex = m_nMouseDownIndex;

}
void	QTableViewEx::mouseReleaseEvent(QMouseEvent * event)
{
	__super::mouseReleaseEvent(event);
	QModelIndex selectedIndex = this->currentIndex();
	m_nMouseUpIndex = selectedIndex.row();
	if (m_nMouseUpIndex != m_nMouseDownIndex)
	{
	//	::SendMessage(,,WPARAM(m_nMouseDownIndex),LPARAM(m_nMouseUpIndex));
		emit moveIndex(m_nMouseDownIndex, m_nMouseUpIndex);
	}
}

void QTableViewEx::setModel(QAbstractItemModel *model)
{
	__super::setModel(model);



}

// void QTableViewExPrivate::_q_selectRow(int row)
// {
//	selectRow(row, false);
/*}*/