#include <iostream>
#include <iomanip>
#include "list/XArrayList.h"
#include "util/Point.h"
using namespace std;

void xlistDemo1()
{
    XArrayList<int> iList;
    for (int i = 0; i < 10; i++)
        iList.add(i, i * i);

    // iList.dump();
    for (XArrayList<int>::Iterator it = iList.begin(); it != iList.end(); it++)
        cout << *it << ", found at: " << iList.indexOf(*it) << endl;
    cout << endl;
    int item = 120;
    int foundIdx = iList.indexOf(item);
    cout << "lookup for " << item << " found at: " << foundIdx << endl;
}

void xlistDemo2()
{
    XArrayList<Point> alist;
    alist.add(Point(23.2f, 25.4f));
    alist.add(Point(24.6f, 23.1f));
    alist.println();
}

void xlistDemo3()
{
    XArrayList<Point> alist;
    alist.add(Point(23.2f, 25.4f));
    alist.add(Point(24.6f, 23.1f));

    int idx1 = alist.indexOf(Point(24.6f, 23.1f));
    int idx2 = alist.indexOf(Point(24.61f, 23.1f));

    cout << "result 1 : " << idx1 << endl;
    cout << "result 2 : " << idx2 << endl;
}

void xlistDemo4()
{
    XArrayList<Point *> list1(&XArrayList<Point *>::free, &Point::pointEQ);
    list1.add(new Point(23.2f, 25.4f));
    list1.add(new Point(24.6f, 23.1f));
    list1.add(new Point(12.5f, 22.3f));

    for (XArrayList<Point *>::Iterator it = list1.begin(); it != list1.end(); it++)
        cout << **it << endl;

    Point *p1 = new Point(24.6f, 23.1f);  // found in list
    Point *p2 = new Point(124.6f, 23.1f); // not found
    cout << *p1 << "=> " << (list1.contains(p1) ? "found; " : "not found; ")
         << " indexOf returns: " << list1.indexOf(p1) << endl;
    cout << *p2 << "=> " << (list1.contains(p2) ? "found; " : "not found; ")
         << " indexOf returns: " << list1.indexOf(p2) << endl;

    /// Different results if not pass &Point::equals
    cout << endl
         << endl;
    //XArrayList<Point *> list2(&XArrayList<Point *>::free);
    XArrayList<Point *> list2(nullptr, &Point::pointEQ, 0);

    list2.add(new Point(23.2f, 25.4f));
    list2.add(new Point(24.6f, 23.1f));
    list2.add(new Point(12.5f, 22.3f));

    for (XArrayList<Point *>::Iterator it = list2.begin(); it != list2.end(); it++)
        cout << **it << endl;

    cout << *p1 << "=> " << (list2.contains(p1) ? "found; " : "not found; ")
         << " indexOf returns: " << list2.indexOf(p1) << endl;
    cout << *p2 << "=> " << (list2.contains(p2) ? "found; " : "not found; ")
         << " indexOf returns: " << list2.indexOf(p2) << endl;

    delete p1;
    delete p2;
}

void xlistDemo5()
{
    XArrayList<Point *> list(&XArrayList<Point *>::free, &Point::pointEQ, 0);

    // Thêm 12 phần tử vào danh sách
    list.add(new Point(23.2f, 25.4f));
    list.add(new Point(24.6f, 23.1f));
    list.add(new Point(12.5f, 22.3f));
    list.add(new Point(23.2f, 25.4f));
    list.add(new Point(24.6f, 23.1f));
    list.add(new Point(12.5f, 22.3f));
    list.add(new Point(23.2f, 25.4f));
    list.add(new Point(24.6f, 23.1f));
    list.add(new Point(12.5f, 22.3f));
    list.add(new Point(23.2f, 25.4f));
    list.add(new Point(24.6f, 23.1f));
    list.add(new Point(12.5f, 22.3f));

    // In danh sách bằng Iterator
    cout << "Danh sách các điểm trong XArrayList:" << endl;
    for (XArrayList<Point *>::Iterator it = list.begin(); it != list.end(); it++)
    {
        cout << **it << endl;
    }

    // Kiểm tra indexOf() với phần tử có trong danh sách
    Point *p1 = new Point(24.6f, 23.1f);
    int idx1 = list.indexOf(p1);
    cout << *p1 << " => " << (idx1 != -1 ? "found" : "not found") << "; indexOf returns: " << idx1 << endl;

    // Kiểm tra indexOf() với phần tử không có trong danh sách
    Point *p2 = new Point(100.0f, 200.0f);
    int idx2 = list.indexOf(p2);
    cout << *p2 << " => " << (idx2 != -1 ? "found" : "not found") << "; indexOf returns: " << idx2 << endl;

    // Giải phóng bộ nhớ của p1 và p2
    delete p1;
    delete p2;
}
