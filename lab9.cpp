
#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>
using namespace std;

const int MAX = 100;

struct BenhNhan {
    int ma;
    char ten[40];
    int tuoi;
    int time;
    int uuTien;
};

struct Node {
    BenhNhan data;
    Node* next;
};

struct Queue {
    Node* front;
    Node* rear;
    int soLuong;
};

bool trungMa(BenhNhan ds[], int n, int ma) {
    for (int i = 0; i < n; i++) {
        if (ds[i].ma == ma)
            return true;
    }
    return false;
}

void inBenhNhan(BenhNhan bn) {
    cout << left
         << setw(10) << bn.ma
         << setw(18) << bn.ten
         << setw(10) << bn.tuoi
         << setw(10) << bn.time
         << setw(12) << bn.uuTien << '\n';
}

void hienThiDanhSach(BenhNhan ds[], int n) {
    if (n == 0) {
        cout << "Danh sach rong!\n";
        return;
    }

    cout << left
         << setw(10) << "Ma"
         << setw(18) << "Ten"
         << setw(10) << "Tuoi"
         << setw(10) << "Time"
         << setw(12) << "Uu tien" << '\n';

    for (int i = 0; i < n; i++)
        inBenhNhan(ds[i]);
}

void themBenhNhan(BenhNhan ds[], int &n) {
    if (n >= MAX) {
        cout << "Danh sach da day!\n";
        return;
    }

    BenhNhan bn;

    cout << "Nhap ma benh nhan: ";
    if (!(cin >> bn.ma)) {
        cout << "Ma khong hop le!\n";
        cin.clear();
        cin.ignore();
        return;
    }

    if (trungMa(ds, n, bn.ma)) {
        cout << "Ma benh nhan da ton tai!\n";
        return;
    }

    cout << "Nhap ten (khong dau cach): ";
    cin >> setw(40) >> bn.ten;

    cout << "Nhap tuoi: ";
    if (!(cin >> bn.tuoi) || bn.tuoi <= 0) {
        cout << "Tuoi khong hop le!\n";
        cin.clear();
        cin.ignore();
        return;
    }

    cout << "Nhap gio den (0-23): ";
    if (!(cin >> bn.time) || bn.time < 0 || bn.time > 23) {
        cout << "Gio den khong hop le!\n";
        cin.clear();
        cin.ignore();
        return;
    }

    cout << "Nhap muc do uu tien (so nho hon = uu tien cao hon): ";
    if (!(cin >> bn.uuTien) || bn.uuTien <= 0) {
        cout << "Muc uu tien phai lon hon 0!\n";
        cin.clear();
        cin.ignore();
        return;
    }

    ds[n++] = bn;
    cout << "Them benh nhan thanh cong!\n";
}

void nhapDuLieuMau(BenhNhan ds[], int &n) {
    BenhNhan mau[5];

    mau[0].ma = 105;
    strcpy(mau[0].ten, "An");
    mau[0].tuoi = 25;
    mau[0].time = 9;
    mau[0].uuTien = 2;

    mau[1].ma = 102;
    strcpy(mau[1].ten, "Binh");
    mau[1].tuoi = 65;
    mau[1].time = 8;
    mau[1].uuTien = 1;

    mau[2].ma = 108;
    strcpy(mau[2].ten, "Chi");
    mau[2].tuoi = 40;
    mau[2].time = 10;
    mau[2].uuTien = 3;

    mau[3].ma = 101;
    strcpy(mau[3].ten, "Dung");
    mau[3].tuoi = 70;
    mau[3].time = 8;
    mau[3].uuTien = 1;

    mau[4].ma = 106;
    strcpy(mau[4].ten, "Ha");
    mau[4].tuoi = 30;
    mau[4].time = 9;
    mau[4].uuTien = 2;

    int them = 0;

    for (int i = 0; i < 5; i++) {
        if (trungMa(ds, n, mau[i].ma)) {
            cout << "Bo qua ma " << mau[i].ma
                 << " vi da ton tai.\n";
            continue;
        }

        if (n >= MAX) {
            cout << "Danh sach da day!\n";
            break;
        }

        ds[n++] = mau[i];
        them++;
    }

    cout << "Da them " << them << " benh nhan mau.\n";
    hienThiDanhSach(ds, n);
}

// Kieu 1: uu tien tang dan -> time tang dan -> tuoi giam dan
// Kieu 2: time tang dan -> uu tien tang dan -> tuoi giam dan

bool dungTruoc(BenhNhan a, BenhNhan b, int kieu) {
    if (kieu == 1) {
        if (a.uuTien != b.uuTien)
            return a.uuTien < b.uuTien;

        if (a.time != b.time)
            return a.time < b.time;

        return a.tuoi > b.tuoi;
    }

    if (a.time != b.time)
        return a.time < b.time;

    if (a.uuTien != b.uuTien)
        return a.uuTien < b.uuTien;

    return a.tuoi > b.tuoi;
}

// Insertion Sort dung chung cho ca hai kieu
void insertionSort(BenhNhan ds[], int n, int kieu) {
    for (int i = 1; i < n; i++) {
        BenhNhan x = ds[i];
        int j = i - 1;

        while (j >= 0 && dungTruoc(x, ds[j], kieu)) {
            ds[j + 1] = ds[j];
            j--;
        }

        ds[j + 1] = x;
    }
}

// Sap xep theo ma de Binary Search
void sapXepTheoMa(BenhNhan ds[], int n) {
    for (int i = 1; i < n; i++) {
        BenhNhan x = ds[i];
        int j = i - 1;

        while (j >= 0 && ds[j].ma > x.ma) {
            ds[j + 1] = ds[j];
            j--;
        }

        ds[j + 1] = x;
    }
}

// Binary Search theo ma benh nhan
int binarySearch(BenhNhan ds[], int n, int ma) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (ds[mid].ma == ma)
            return mid;

        if (ds[mid].ma < ma)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

void timBenhNhan(BenhNhan ds[], int n) {
    if (n == 0) {
        cout << "Danh sach rong!\n";
        return;
    }

    BenhNhan tam[MAX];

    for (int i = 0; i < n; i++)
        tam[i] = ds[i];

    sapXepTheoMa(tam, n);

    int ma;
    cout << "Nhap ma benh nhan can tim: ";

    if (!(cin >> ma)) {
        cout << "Ma khong hop le!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int vt = binarySearch(tam, n, ma);

    if (vt != -1) {
        cout << "Tim thay benh nhan:\n";
        cout << left
             << setw(10) << "Ma"
             << setw(18) << "Ten"
             << setw(10) << "Tuoi"
             << setw(10) << "Time"
             << setw(12) << "Uu tien" << '\n';

        inBenhNhan(tam[vt]);
    } else {
        cout << "KHONG TIM THAY BENH NHAN!\n";
    }
}

// ================= QUEUE LIEN KET =================

void khoiTaoQueue(Queue &q) {
    q.front = NULL;
    q.rear = NULL;
    q.soLuong = 0;
}

bool queueRong(Queue &q) {
    return q.front == NULL;
}

void xoaQueue(Queue &q) {
    while (q.front != NULL) {
        Node* p = q.front;
        q.front = q.front->next;
        delete p;
    }

    q.rear = NULL;
    q.soLuong = 0;
}

// Them benh nhan vao cuoi Queue
bool enqueue(Queue &q, BenhNhan bn) {
    Node* p = new Node;

    if (p == NULL)
        return false;

    p->data = bn;
    p->next = NULL;

    if (queueRong(q))
        q.front = q.rear = p;
    else {
        q.rear->next = p;
        q.rear = p;
    }

    q.soLuong++;
    return true;
}

// Lay benh nhan o dau Queue
bool dequeue(Queue &q, BenhNhan &bn) {
    if (queueRong(q))
        return false;

    Node* p = q.front;
    bn = p->data;
    q.front = q.front->next;

    if (q.front == NULL)
        q.rear = NULL;

    delete p;
    q.soLuong--;
    return true;
}

bool taoQueueUuTien(BenhNhan ds[], int n, Queue &q, int kieu) {
    xoaQueue(q);

    if (n == 0) {
        cout << "Danh sach rong, khong the tao Queue!\n";
        return false;
    }

    BenhNhan tam[MAX];

    for (int i = 0; i < n; i++)
        tam[i] = ds[i];

    insertionSort(tam, n, kieu);

    for (int i = 0; i < n; i++) {
        if (!enqueue(q, tam[i])) {
            cout << "Khong du bo nho de tao Queue!\n";
            xoaQueue(q);
            return false;
        }
    }

    cout << "Da tao Queue thanh cong!\n";

    if (kieu == 1)
        cout << "Thu tu: uu tien -> time -> tuoi giam dan.\n";
    else
        cout << "Thu tu: time -> uu tien -> tuoi giam dan.\n";

    return true;
}

void tiepNhanBenhNhan(Queue &q) {
    BenhNhan bn;

    if (dequeue(q, bn)) {
        cout << "Benh nhan duoc tiep nhan:\n";
        cout << left
             << setw(10) << "Ma"
             << setw(18) << "Ten"
             << setw(10) << "Tuoi"
             << setw(10) << "Time"
             << setw(12) << "Uu tien" << '\n';

        inBenhNhan(bn);
        cout << "So benh nhan con cho: " << q.soLuong << '\n';
    } else {
        cout << "Queue rong, khong con benh nhan!\n";
    }
}

void hienThiQueue(Queue &q) {
    if (queueRong(q)) {
        cout << "Queue rong!\n";
        return;
    }

    cout << left
         << setw(10) << "Ma"
         << setw(18) << "Ten"
         << setw(10) << "Tuoi"
         << setw(10) << "Time"
         << setw(12) << "Uu tien" << '\n';

    Node* p = q.front;

    while (p != NULL) {
        inBenhNhan(p->data);
        p = p->next;
    }
}

// ================= MENU =================

void menu() {
    cout << "\n========== QUAN LY BENH NHAN ==========\n";
    cout << "1. Them benh nhan\n";
    cout << "2. Hien thi danh sach\n";
    cout << "3. Nhap du lieu mau\n";
    cout << "4. Tim benh nhan theo ma (Binary Search)\n";
    cout << "5. Tao Queue uu tien\n";
    cout << "6. Tiep nhan benh nhan tiep theo\n";
    cout << "7. Hien thi Queue con lai\n";
    cout << "0. Thoat chuong trinh\n";
    cout << "=======================================\n";
    cout << "Nhap lua chon: ";
}

int main() {
    BenhNhan ds[MAX];
    int n = 0;

    Queue q;
    khoiTaoQueue(q);

    bool daTaoQueue = false;
    int chon;

    do {
        menu();

        if (!(cin >> chon)) {
            cout << "Vui long nhap lua chon bang so!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (chon) {
        case 1:
            themBenhNhan(ds, n);
            xoaQueue(q);
            daTaoQueue = false;
            break;

        case 2:
            hienThiDanhSach(ds, n);
            break;

        case 3:
            nhapDuLieuMau(ds, n);
            xoaQueue(q);
            daTaoQueue = false;
            break;

        case 4:
            timBenhNhan(ds, n);
            break;

        case 5: {
            int kieu;

            cout << "1. Uu tien -> time -> tuoi\n";
            cout << "2. Time -> uu tien -> tuoi\n";
            cout << "Chon kieu sap xep: ";

            if (!(cin >> kieu) || (kieu != 1 && kieu != 2)) {
                cout << "Kieu sap xep khong hop le!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            daTaoQueue = taoQueueUuTien(ds, n, q, kieu);
            break;
        }

        case 6:
            if (!daTaoQueue) {
                cout << "Hay tao Queue truoc bang chuc nang 5!\n";
                break;
            }

            tiepNhanBenhNhan(q);
            break;

        case 7:
            if (!daTaoQueue) {
                cout << "Hay tao Queue truoc bang chuc nang 5!\n";
                break;
            }

            cout << "\n--- QUEUE CON LAI THEO FIFO ---\n";
            hienThiQueue(q);
            break;

        case 0:
            cout << "Da thoat chuong trinh.\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (chon != 0);

    xoaQueue(q);
    return 0;
}
