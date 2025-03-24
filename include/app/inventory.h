#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "list/XArrayList.h"
#include "list/DLinkedList.h"
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// -------------------- List1D --------------------
template <typename T>
class List1D
{
private:
    IList<T> *pList;

public:
    List1D();
    List1D(int num_elements);
    List1D(const T *array, int num_elements);
    List1D(const List1D<T> &other);
    virtual ~List1D();

    int size() const;
    T get(int index) const;
    void set(int index, T value);
    void add(const T &value);
    string toString() const;

    friend ostream &operator<<(ostream &os, const List1D<T> &list);
};

// -------------------- List2D --------------------
template <typename T>
class List2D
{
private:
    IList<IList<T> *> *pMatrix;

public:
    List2D();
    List2D(List1D<T> *array, int num_rows);
    List2D(const List2D<T> &other);
    virtual ~List2D();

    int rows() const;
    void setRow(int rowIndex, const List1D<T> &row);
    T get(int rowIndex, int colIndex) const;
    List1D<T> getRow(int rowIndex) const;
    string toString() const;

    friend ostream &operator<<(ostream &os, const List2D<T> &matrix);
};

struct InventoryAttribute
{
    string name;
    double value;
    InventoryAttribute(const string &name, double value) : name(name), value(value) {}
    string toString() const { return name + ": " + to_string(value); }
};

// -------------------- InventoryManager --------------------
class InventoryManager
{
private:
    List2D<InventoryAttribute> attributesMatrix;
    List1D<string> productNames;
    List1D<int> quantities;

public:
    InventoryManager();
    InventoryManager(const List2D<InventoryAttribute> &matrix,
                     const List1D<string> &names,
                     const List1D<int> &quantities);
    InventoryManager(const InventoryManager &other);

    int size() const;
    List1D<InventoryAttribute> getProductAttributes(int index) const;
    string getProductName(int index) const;
    int getProductQuantity(int index) const;
    void updateQuantity(int index, int newQuantity);
    void addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity);
    void removeProduct(int index);

    List1D<string> query(string attributeName, const double &minValue,
                         const double &maxValue, int minQuantity, bool ascending) const;

    void removeDuplicates();

    static InventoryManager merge(const InventoryManager &inv1,
                                  const InventoryManager &inv2);

    void split(InventoryManager &section1,
               InventoryManager &section2,
               double ratio) const;

    List2D<InventoryAttribute> getAttributesMatrix() const;
    List1D<string> getProductNames() const;
    List1D<int> getQuantities() const;
    string toString() const;
};

// -------------------- List1D Method Definitions --------------------
template <typename T>
List1D<T>::List1D()
{
    // TODO
    pList = new XArrayList<T>();
}

template <typename T>
List1D<T>::List1D(int num_elements)
{
    // TODO
    pList = new XArrayList<T>();
    for (int i = 0; i < num_elements; i++)
    {
        pList->add(T()); // Add default value
    }
}

template <typename T>
List1D<T>::List1D(const T *array, int num_elements)
{
    // TODO
    pList = new XArrayList<T>();
    // Copy all elements from the array
    for (int i = 0; i < num_elements; i++)
    {
        pList->add(array[i]);
    }
}

template <typename T>
List1D<T>::List1D(const List1D<T> &other)
{
    // TODO
    pList = new XArrayList<T>();
    // Copy all elements from the other list
    for (int i = 0; i < other.size(); i++)
    {
        pList->add(other.get(i));
    }
}

template <typename T>
List1D<T>::~List1D()
{
    // TODO
    if (pList != nullptr)
    {
        delete pList;
        pList = nullptr;
    }
}

template <typename T>
int List1D<T>::size() const
{
    // TODO
    return pList->size();
}

template <typename T>
T List1D<T>::get(int index) const
{
    // TODO
    return pList->get(index);
}

template <typename T>
void List1D<T>::set(int index, T value)
{
    // TODO
    if (index < 0 || index > pList->size())
    {
        throw std::out_of_range("Index is out of range! in set(int index, T value)");
    }
    if (index == pList->size())
    {
        pList->add(value);
        return;
    }
    pList->get(index) = value;
}

template <typename T>
void List1D<T>::add(const T &value)
{
    // TODO
    pList->add(value);
}

template <typename T>
string List1D<T>::toString() const
{
    // TODO
    stringstream ss;
    ss << "[";
    for (int i = 0; i < pList->size(); i++)
    {
        if (i > 0)
            ss << ", ";
        ss << pList->get(i);
    }
    ss << "]";
    return ss.str();
}

template <typename T>
ostream &operator<<(ostream &os, const List1D<T> &list)
{
    // TODO
    os << list.toString();
    return os;
}

// -------------------- List2D Method Definitions --------------------
template <typename T>
List2D<T>::List2D()
{
    // TODO
    pMatrix = new XArrayList<IList<T> *>();
}

template <typename T>
List2D<T>::List2D(List1D<T> *array, int num_rows)
{
    // TODO
    pMatrix = new XArrayList<IList<T> *>();

    // Add each row from the provided array
    for (int i = 0; i < num_rows; i++)
    {
        // Create a new list for each row
        IList<T> *newRow = new XArrayList<T>();

        // Copy elements from the corresponding array row
        for (int j = 0; j < array[i].size(); j++)
        {
            newRow->add(array[i].get(j));
        }

        // Add the new row to the matrix
        pMatrix->add(newRow);
    }
}

template <typename T>
List2D<T>::List2D(const List2D<T> &other)
{
    // TODO
    pMatrix = new XArrayList<IList<T> *>();

    // Copy each row from the other matrix
    for (int i = 0; i < other.rows(); i++)
    {
        IList<T> *newRow = new XArrayList<T>();
        List1D<T> sourceRow = other.getRow(i);

        // Copy all elements from the source row
        for (int j = 0; j < sourceRow.size(); j++)
        {
            newRow->add(sourceRow.get(j));
        }

        // Add the new row to the matrix
        pMatrix->add(newRow);
    }
}

template <typename T>
List2D<T>::~List2D()
{
    // TODO
    if (pMatrix != nullptr)
    {
        // First, delete each row
        for (int i = 0; i < pMatrix->size(); i++)
        {
            delete pMatrix->get(i);
        }

        // Then, delete the matrix itself
        delete pMatrix;
        pMatrix = nullptr;
    }
}

template <typename T>
int List2D<T>::rows() const
{
    // TODO
    return pMatrix->size();
}

template <typename T>
void List2D<T>::setRow(int rowIndex, const List1D<T> &row)
{
    // TODO
    //  Check row index bounds
    if (rowIndex < 0 || rowIndex > pMatrix->size())
    {
        throw std::out_of_range("Index is out of range!");
    }

    // Tạo hàng mới
    IList<T> *newRow = new XArrayList<T>();
    for (int i = 0; i < row.size(); i++)
    {
        newRow->add(row.get(i));
    }

    // TH1: Nếu `pMatrix` đang rỗng và `rowIndex == 0`, thêm hàng đầu tiên
    if (pMatrix->size() == 0 && rowIndex == 0)
    {
        pMatrix->add(newRow);
    }
    // TH2: Nếu `rowIndex == pMatrix->size()`, thêm vào cuối
    else if (rowIndex == pMatrix->size())
    {
        pMatrix->add(newRow);
    }
    // TH3: Nếu `rowIndex` nằm trong phạm vi, thay thế hàng cũ
    else
    {
        // Tạo danh sách mới để lưu dữ liệu cập nhật
        IList<IList<T> *> *newMatrix = new XArrayList<IList<T> *>();

        for (int i = 0; i < pMatrix->size(); i++)
        {
            if (i == rowIndex)
            {
                // Thêm hàng mới vào vị trí `rowIndex`
                newMatrix->add(newRow);
                delete pMatrix->get(i); // Giải phóng bộ nhớ của hàng cũ
            }
            else
            {
                // Giữ nguyên các hàng khác
                newMatrix->add(pMatrix->get(i));
            }
        }

        // Giải phóng ma trận cũ
        delete pMatrix;

        // Gán ma trận mới vào `pMatrix`
        pMatrix = newMatrix;
    }
}

template <typename T>
T List2D<T>::get(int rowIndex, int colIndex) const
{
    // TODO
    // Check if rowIndex is valid
    if (rowIndex < 0 || rowIndex >= pMatrix->size())
    {
        throw std::out_of_range("Index is out of range!");
    }

    // Get the row
    IList<T> *row = pMatrix->get(rowIndex);

    // Check if colIndex is valid
    if (colIndex < 0 || colIndex >= row->size())
    {
        throw std::out_of_range("Index is out of range!");
    }

    // Return the element
    return row->get(colIndex);
}

template <typename T>
List1D<T> List2D<T>::getRow(int rowIndex) const
{
    // TODO
    if (rowIndex < 0 || rowIndex >= pMatrix->size())
    {
        throw std::out_of_range("Index is out of range!");
    }

    // Get the row
    IList<T> *row = pMatrix->get(rowIndex);

    // Create a new List1D object
    List1D<T> result;

    // Copy elements from the row
    for (int i = 0; i < row->size(); i++)
    {
        result.add(row->get(i));
    }

    return result;
}

template <typename T>
string List2D<T>::toString() const
{
    // TODO
    stringstream ss;
    ss << "[";

    for (int i = 0; i < pMatrix->size(); i++)
    {
        if (i > 0)
            ss << ", ";

        // Get the row
        IList<T> *row = pMatrix->get(i);

        // Format the row
        ss << "[";
        for (int j = 0; j < row->size(); j++)
        {
            if (j > 0)
                ss << ", ";
            ss << row->get(j);
        }
        ss << "]";
    }

    ss << "]";
    return ss.str();
}

template <typename T>
ostream &operator<<(ostream &os, const List2D<T> &matrix)
{
    // TODO
    os << matrix.toString();
    return os;
}

// -------------------- InventoryManager Method Definitions --------------------
InventoryManager::InventoryManager()
{
    // TODO
}

InventoryManager::InventoryManager(const List2D<InventoryAttribute> &matrix,
                                   const List1D<string> &names,
                                   const List1D<int> &quantities)
{
    // TODO
}

InventoryManager::InventoryManager(const InventoryManager &other)
{
    // TODO
}

int InventoryManager::size() const
{
    // TODO
}

List1D<InventoryAttribute> InventoryManager::getProductAttributes(int index) const
{
    // TODO
}

string InventoryManager::getProductName(int index) const
{
    // TODO
}

int InventoryManager::getProductQuantity(int index) const
{
    // TODO
}

void InventoryManager::updateQuantity(int index, int newQuantity)
{
    // TODO
}

void InventoryManager::addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity)
{
    // TODO
}

void InventoryManager::removeProduct(int index)
{
    // TODO
}

List1D<string> InventoryManager::query(string attributeName, const double &minValue,
                                       const double &maxValue, int minQuantity, bool ascending) const
{
    // TODO
}

void InventoryManager::removeDuplicates()
{
    // TODO
}

InventoryManager InventoryManager::merge(const InventoryManager &inv1,
                                         const InventoryManager &inv2)
{
    // TODO
}

void InventoryManager::split(InventoryManager &section1,
                             InventoryManager &section2,
                             double ratio) const
{
    // TODO
}

List2D<InventoryAttribute> InventoryManager::getAttributesMatrix() const
{
    // TODO
}

List1D<string> InventoryManager::getProductNames() const
{
    // TODO
}

List1D<int> InventoryManager::getQuantities() const
{
    // TODO
}

string InventoryManager::toString() const
{
    // TODO
}

#endif /* INVENTORY_MANAGER_H */
