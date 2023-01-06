//Курсова работа по ООП-задача 4
//Хюсеин Хюсеин 21621363 3а група КСТ II курс
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

class CCellDescr {
private:
	double m_double_val;
	string m_str_val;
	int m_row;
	int m_col;
	char m_cCellType; // 'N' 'S'

public:
	// конструктор
	explicit CCellDescr(char cCellType, int iColumnNum, int iRowNum, const string& strValue): m_cCellType(cCellType), m_row(iRowNum), m_col(iColumnNum), m_str_val(strValue)
	{
		// ако е N превръщане в double
		if (m_cCellType == 'N') {
			m_double_val = stod(m_str_val);
		}
	}

	CCellDescr(const CCellDescr& obj): m_double_val(obj.m_double_val), m_str_val(obj.m_str_val), m_row(obj.m_row), m_col(obj.m_col), m_cCellType(obj.m_cCellType)
	{
	}

	double getDoubleValue() const { return m_double_val; }
	string getStringValue() const { return m_str_val; }
	int getRow() const { return m_row; }
	int getColumn() const { return m_col; }
	char getCellType() const { return m_cCellType; }

	void setDoubleValue(double val) { m_double_val = val; }
	void setStringValue(const string& val) { m_str_val = val; }
	void setRow(int val) { m_row = val; }
	void setColumn(int val) { m_col = val; }
	void setCellType(char val) { m_cCellType = val; }

	CCellDescr& operator=(const CCellDescr& rhs)
	{
		if (this != &rhs) {
			m_double_val = rhs.m_double_val;
			m_str_val = rhs.m_str_val;
			m_row = rhs.m_row;
			m_col = rhs.m_col;
			m_cCellType = rhs.m_cCellType;
		}
		return *this;
	}
	// изходен оператор
	friend ostream& operator<<(ostream& os, const CCellDescr& cell)
	{
		if (cell.m_cCellType == 'N') {
			os << cell.m_double_val;
		}
		else {
			os << cell.m_str_val;
		}
		return os;
	}
};

class CData {
private:
	list<CCellDescr*> m_Data; // table contents (cell pointers)
	int m_iColumns;
	int m_iRows;

public:
	// конструктор
	CData(int iColumns, int iRows)
		: m_iColumns(iColumns), m_iRows(iRows)
	{
	}

	// деструктор
	~CData()
	{
		// Delete all the cells in the table
		for (CCellDescr* pCell : m_Data) {
			delete pCell;
		}
	}

	int getNumColumns() const { return m_iColumns; }
	int getNumRows() const { return m_iRows; }
	list<CCellDescr*> getData() const { return m_Data; }

	// създаване на нова клетка
	void setCell(const CCellDescr& cellData)
	{
		CCellDescr* pCell = new CCellDescr(cellData);
		m_Data.push_back(pCell);
	}

	// функция за премахване на редове и колони
	void removeInvalidRowsAndColumns()
	{
		// премахване на редове
		m_Data.remove_if([&](CCellDescr* pCell) {
			return pCell->getRow() < 0 || pCell->getRow() >= m_iRows;
			});

		// премахване на колони
		m_Data.remove_if([&](CCellDescr* pCell) {
			return pCell->getColumn() < 0 || pCell->getColumn() >= m_iColumns;
			});
	}
};

int main()
{
	// таблица с 5 колони 4 реда
	CData table(5, 4);

	//таблица
	table.setCell(CCellDescr('N', 1, 1, "123.45"));
	table.setCell(CCellDescr('S', 2, 1, "Hello"));
	table.setCell(CCellDescr('N', 3, 1, "67.89"));
	table.setCell(CCellDescr('S', 4, 1, "World"));
	table.setCell(CCellDescr('N', 5, 1, "1.23"));
	table.setCell(CCellDescr('S', 1, 2, "Foo"));
	table.setCell(CCellDescr('N', 2, 2, "456.78"));
	table.setCell(CCellDescr('S', 3, 2, "Bar"));
	table.setCell(CCellDescr('N', 4, 2, "9.87"));
	table.setCell(CCellDescr('S', 5, 2, "Baz"));

	// премахване на ненужни колони и редове
	table.removeInvalidRowsAndColumns();

	for (CCellDescr* pCell : table.getData()) {
		cout << *pCell << " ";
	}
	cout << endl;

	return 0;
}