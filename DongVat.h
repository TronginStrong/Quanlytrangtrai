#ifndef DONGVAT_H
#define DONGVAT_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

// ================= TIEN ICH =================
void Clear(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Pause(){
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
}

void TieuDe(const string &s){
    Clear();
    cout << "=============================\n";
    cout << s << "\n";
    cout << "=============================\n\n";
}

// ========== HÀM XUẤT BẢNG CÓ PHÂN TRANG ==========
template <typename T>
void XuatBangDanhSach(const vector<T*> &ds){
    if(ds.empty()){
        cout << "Danh sach rong!";
        Pause();
        return;
    }

    const int pageSize = 10;
    int total = ds.size();
    int page = 0;

    while(true){
        Clear();
        cout << "----- DANH SACH (Trang " << page+1 << "/" << (total+pageSize-1)/pageSize << ") -----\n\n";

        cout << left
             << setw(10) << "Ma"
             << setw(15) << "Ten"
             << setw(10) << "Loai"
             << setw(6)  << "Tuoi"
             << setw(10) << "Kg"
             << setw(8)  << "Ban?"
             << setw(10) << "Gia" << "\n";

        cout << string(69, '-') << "\n";

        int start = page * pageSize;
        int end = min(start + pageSize, total);

        for(int i = start; i < end; i++)
            ds[i]->XuatBang();

        if(end >= total){ Pause(); return; }

        cout << "\nNhan Enter xem trang tiep...";
        cin.ignore();
        cin.get();
        page++;
    }
}

// ================= CLASS CThuNuoi (DUY NHAT) =================
class CThuNuoi {
protected:
    string MaSo;
    string Ten;
    string Loai;
    int Tuoi;
    float TrongLuong;
    float GiaBanThucTe;
    bool DaBan;

public:
    CThuNuoi() : Tuoi(0), TrongLuong(0), GiaBanThucTe(0), DaBan(false) {}
    virtual ~CThuNuoi() {}

    // Nhap: cho phep nhap MaSo = "0" de huy (thoat)
    virtual void Nhap() {
        TieuDe("Nhap thong tin thu nuoi (nhap 0 de huy)");

        cout << "Nhap ma so: ";
        cin >> MaSo;
        if (MaSo == "0") { cin.ignore(); return; }
        cin.ignore();

        cout << "Nhap ten thu nuoi (nhap 0 de huy): ";
        getline(cin, Ten);
        if (Ten == "0") { return; }

        cout << "Nhap tuoi: ";
        cin >> Tuoi;
        cout << "Nhap trong luong (kg): ";
        cin >> TrongLuong;
        cin.ignore();

        DaBan = false;
        GiaBanThucTe = 0;
    }

    virtual void Xuat() {
        cout << "Ma: " << MaSo
             << " | Ten: " << Ten
             << " | Loai: " << Loai
             << " | Tuoi: " << Tuoi
             << " | Trong luong: " << TrongLuong
             << " | Da ban: " << (DaBan ? "Roi" : "Chua")
             << " | Gia ban: " << fixed << setprecision(0) << GiaBanThucTe << endl;
    }

    bool KiemTraDaBan() const { return DaBan; }

    void BanThu(float giaBan) {
        if (DaBan) {
            cout << "Thu nay da duoc ban roi!\n";
            return;
        }
        GiaBanThucTe = giaBan;
        DaBan = true;
        cout << "Ban thanh cong voi gia: " << fixed << setprecision(0) << GiaBanThucTe << " VND\n";
    }

    // ====== THEM – HAM XUAT THEO BANG ======
    virtual void XuatBang() const {
        cout << left
            << setw(10) << MaSo
            << setw(15) << Ten
            << setw(10) << Loai
            << setw(6)  << Tuoi
            << setw(10) << TrongLuong
            << setw(8)  << (DaBan ? "X" : "")
            << setw(10) << fixed << setprecision(0) << GiaBanThucTe
            << "\n";
    }

    // Getter / Setter
    string GetMaSo() const { return MaSo; }
    string GetLoai() const { return Loai; }
    float GetGiaBan() const { return GiaBanThucTe; }
    int GetTuoi() const { return Tuoi; }
    float GetTrongLuong() const { return TrongLuong; }

    void setMaSo(string s) { MaSo = s; }
    void setTen(string s) { Ten = s; }
    void setLoai(string s) { Loai = s; }
    void setTuoi(int t) { Tuoi = t; }
    void setTrongLuong(float w) { TrongLuong = w; }
    void setGiaBan(float g) { GiaBanThucTe = g; }
    void setDaBan(bool b) { DaBan = b; }

    virtual void LuuFile(ofstream &fout) {
        fout << MaSo << "|" << Ten << "|" << Loai << "|" << Tuoi << "|"
             << TrongLuong << "|" << GiaBanThucTe << "|" << DaBan << endl;
    }
};

/*---------------------------------------------------------
    LỚP CON: CBo
---------------------------------------------------------*/
class CBo : public CThuNuoi {
    float LuongSua;
    int SoNgayChoSua;

public:
    CBo() : LuongSua(0), SoNgayChoSua(0) {}
    void Nhap() override {
        TieuDe("Quan ly Bo -> Them Bo (nhap 0 de huy)");
        CThuNuoi::Nhap(); if (MaSo == "0" || Ten == "0") { return; }
        Loai = "Bo";
        cout << "Nhap luong sua (lit/ngay): ";
        cin >> LuongSua;
        cout << "Nhap so ngay cho sua: ";
        cin >> SoNgayChoSua;
        cin.ignore();
    }
    void Xuat() override {
        CThuNuoi::Xuat();
        cout << "Luong sua: " << LuongSua
             << " | So ngay cho sua: " << SoNgayChoSua << endl;
    }

    // Getter/Setter rieng
    float GetLuongSua() const { return LuongSua; }
    int GetSoNgayChoSua() const { return SoNgayChoSua; }
    void setLuongSua(float x) { LuongSua = x; }
    void setSoNgayChoSua(int x) { SoNgayChoSua = x; }
};

/*---------------------------------------------------------
    LỚP CON: CHeo
---------------------------------------------------------*/
class CHeo : public CThuNuoi {
    float TyLeMo;
    float SanLuongThit;

public:
    CHeo() : TyLeMo(0), SanLuongThit(0) {}
    void Nhap() override {
        TieuDe("Quan ly Heo -> Them Heo (nhap 0 de huy)");
        CThuNuoi::Nhap(); if (MaSo == "0" || Ten == "0") { return; }
        Loai = "Heo";
        cout << "Nhap ty le mo (%): ";
        cin >> TyLeMo;
        cout << "Nhap san luong thit (kg): ";
        cin >> SanLuongThit;
        cin.ignore();
    }
    void Xuat() override {
        CThuNuoi::Xuat();
        cout << "Ty le mo: " << TyLeMo
             << "% | San luong thit: " << SanLuongThit << " kg\n";
    }

    float GetTyLeMo() const { return TyLeMo; }
    float GetSanLuongThit() const { return SanLuongThit; }
    void setTyLeMo(float x) { TyLeMo = x; }
    void setSanLuongThit(float x) { SanLuongThit = x; }
};

/*---------------------------------------------------------
    LỚP CON: CGa
---------------------------------------------------------*/
class CGa : public CThuNuoi {
    int SoTrungNgay;
    float GiaTrung;

public:
    CGa() : SoTrungNgay(0), GiaTrung(0) {}
    void Nhap() override {
        TieuDe("Quan ly Ga -> Them Ga (nhap 0 de huy)");
        CThuNuoi::Nhap(); if (MaSo == "0" || Ten == "0") { return; }
        Loai = "Ga";
        cout << "Nhap so trung de/ngay: ";
        cin >> SoTrungNgay;
        cout << "Nhap gia trung (VND): ";
        cin >> GiaTrung;
        cin.ignore();
    }
    void Xuat() override {
        CThuNuoi::Xuat();
        cout << "So trung/ngay: " << SoTrungNgay
             << " | Gia trung: " << GiaTrung << " VND\n";
    }

    int GetSoTrungNgay() const { return SoTrungNgay; }
    float GetGiaTrung() const { return GiaTrung; }
    void setSoTrungNgay(int x) { SoTrungNgay = x; }
    void setGiaTrung(float x) { GiaTrung = x; }
};

/*---------------------------------------------------------
    NODE & DANH SÁCH LIÊN KẾT
---------------------------------------------------------*/
struct Node {
    CThuNuoi *data;
    Node *next;
    Node(CThuNuoi *x) : data(x), next(nullptr) {}
};

class CDanhSachThuNuoi {
    Node *head;

public:
    CDanhSachThuNuoi() : head(nullptr) {}

    void Them(CThuNuoi *x) {
        if (!x) return;
        Node *p = new Node(x);
        if (!head) head = p;
        else {
            Node *t = head;
            while (t->next) t = t->next;
            t->next = p;
        }
    }

    // Chuyen sang vector de dung XuatBangDanhSach
    vector<CThuNuoi*> ToVector() {
        vector<CThuNuoi*> v;
        Node *p = head;
        while (p) {
            v.push_back(p->data);
            p = p->next;
        }
        return v;
    }

    // Giữ lại XuatDanhSach theo nhóm (khong thay)
    void XuatDanhSach() {
        bool coBo=false, coHeo=false, coGa=false;
        Node *p = head;

        cout << "\n=== DANH SACH BO ===\n";
        p = head;
        while (p) {
            if (p->data->GetLoai() == "Bo") {
                p->data->Xuat();
                coBo = true;
            }
            p = p->next;
        }
        if (!coBo) cout << "(Khong co Bo)\n";

        cout << "\n=== DANH SACH HEO ===\n";
        p = head;
        while (p) {
            if (p->data->GetLoai() == "Heo") {
                p->data->Xuat();
                coHeo = true;
            }
            p = p->next;
        }
        if (!coHeo) cout << "(Khong co Heo)\n";

        cout << "\n=== DANH SACH GA ===\n";
        p = head;
        while (p) {
            if (p->data->GetLoai() == "Ga") {
                p->data->Xuat();
                coGa = true;
            }
            p = p->next;
        }
        if (!coGa) cout << "(Khong co Ga)\n";
    }

    // Xuat theo bang phan trang (giup UI gọn)
    void XuatDanhSachBang() {
        vector<CThuNuoi*> v = ToVector();
        XuatBangDanhSach(v);
    }

    void BanThuNuoi(string ma, float giaBan) {
        Node *p = head;
        while (p) {
            if (p->data->GetMaSo() == ma) {
                p->data->BanThu(giaBan);
                return;
            }
            p = p->next;
        }
        cout << "Khong tim thay ma thu nuoi.\n";
    }

    float TongDoanhThu() {
        float tong = 0;
        Node *p = head;
        while (p) {
            if (p->data->KiemTraDaBan())
                tong += p->data->GetGiaBan();
            p = p->next;
        }
        return tong;
    }
    
    bool XoaThuNuoi(string ma) {
        if (!head) return false;

        // Trường hợp xóa đầu danh sách
        if (head->data->GetMaSo() == ma) {
            Node *temp = head;
            head = head->next;
            delete temp->data;
            delete temp;
            return true;
        }

        Node *p = head;
        while (p->next) {
            if (p->next->data->GetMaSo() == ma) {
                Node *temp = p->next;
                p->next = temp->next;
                delete temp->data;
                delete temp;
                return true;
            }
            p = p->next;
        }
        return false;
    }

    /*-----------------------------------------------------
        LƯU VÀ ĐỌC FILE RIÊNG CHO TỪNG LOẠI
    -----------------------------------------------------*/
    void LuuFile() {
        ofstream fBo("danhsach_bo.txt"), fHeo("danhsach_heo.txt"), fGa("danhsach_ga.txt");
        if (!fBo || !fHeo || !fGa) {
            cout << "Khong the mo file de luu!\n";
            return;
        }

        Node *p = head;
        while (p) {
            string loai = p->data->GetLoai();
            if (loai == "Bo") {
                CBo *bo = dynamic_cast<CBo*>(p->data);
                if (bo) fBo << bo->GetMaSo() << "|" << bo->GetLoai() << "|" 
                            << bo->GetGiaBan() << "|" << (bo->KiemTraDaBan() ? 1 : 0) << "|"
                            << bo->GetTuoi() << "|" << bo->GetTrongLuong() << "|"
                            << bo->GetLuongSua() << "|" << bo->GetSoNgayChoSua() << "\n";
            }
            else if (loai == "Heo") {
                CHeo *heo = dynamic_cast<CHeo*>(p->data);
                if (heo) fHeo << heo->GetMaSo() << "|" << heo->GetLoai() << "|" 
                              << heo->GetGiaBan() << "|" << (heo->KiemTraDaBan() ? 1 : 0) << "|"
                              << heo->GetTuoi() << "|" << heo->GetTrongLuong() << "|"
                              << heo->GetTyLeMo() << "|" << heo->GetSanLuongThit() << "\n";
            }
            else if (loai == "Ga") {
                CGa *ga = dynamic_cast<CGa*>(p->data);
                if (ga) fGa << ga->GetMaSo() << "|" << ga->GetLoai() << "|" 
                            << ga->GetGiaBan() << "|" << (ga->KiemTraDaBan() ? 1 : 0) << "|"
                            << ga->GetTuoi() << "|" << ga->GetTrongLuong() << "|"
                            << ga->GetSoTrungNgay() << "|" << ga->GetGiaTrung() << "\n";
            }
            p = p->next;
        }

        cout << "Da luu danh sach vao 3 file!\n";
    }

    void DocFile() {
        auto safe_stof = [](string s) -> float {
            try { return stof(s); } catch (...) { return 0; }
        };
        auto safe_stoi = [](string s) -> int {
            try { return stoi(s); } catch (...) { return 0; }
        };

        string line;

        // Bo
        ifstream fBo("danhsach_bo.txt");
        while (fBo && getline(fBo, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string ma, loai, gia, daban, tuoi, tl, sua, ngay;
            getline(ss, ma, '|'); getline(ss, loai, '|');
            getline(ss, gia, '|'); getline(ss, daban, '|');
            getline(ss, tuoi, '|'); getline(ss, tl, '|');
            getline(ss, sua, '|'); getline(ss, ngay, '|');
            CBo *bo = new CBo();
            bo->setMaSo(ma); bo->setLoai(loai);
            bo->setGiaBan(safe_stof(gia)); bo->setDaBan(daban == "1");
            bo->setTuoi(safe_stoi(tuoi)); bo->setTrongLuong(safe_stof(tl));
            bo->setLuongSua(safe_stof(sua)); bo->setSoNgayChoSua(safe_stoi(ngay));
            Them(bo);
        }
        // Heo
        ifstream fHeo("danhsach_heo.txt");
        while (fHeo && getline(fHeo, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string ma, loai, gia, daban, tuoi, tl, tyle, thit;
            getline(ss, ma, '|'); getline(ss, loai, '|');
            getline(ss, gia, '|'); getline(ss, daban, '|');
            getline(ss, tuoi, '|'); getline(ss, tl, '|');
            getline(ss, tyle, '|'); getline(ss, thit, '|');
            CHeo *heo = new CHeo();
            heo->setMaSo(ma); heo->setLoai(loai);
            heo->setGiaBan(safe_stof(gia)); heo->setDaBan(daban == "1");
            heo->setTuoi(safe_stoi(tuoi)); heo->setTrongLuong(safe_stof(tl));
            heo->setTyLeMo(safe_stof(tyle)); heo->setSanLuongThit(safe_stof(thit));
            Them(heo);
        }

        // Ga
        ifstream fGa("danhsach_ga.txt");
        while (fGa && getline(fGa, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string ma, loai, gia, daban, tuoi, tl, trung, gt;
            getline(ss, ma, '|'); getline(ss, loai, '|');
            getline(ss, gia, '|'); getline(ss, daban, '|');
            getline(ss, tuoi, '|'); getline(ss, tl, '|');
            getline(ss, trung, '|'); getline(ss, gt, '|');
            CGa *ga = new CGa();
            ga->setMaSo(ma); ga->setLoai(loai);
            ga->setGiaBan(safe_stof(gia)); ga->setDaBan(daban == "1");
            ga->setTuoi(safe_stoi(tuoi)); ga->setTrongLuong(safe_stof(tl));
            ga->setSoTrungNgay(safe_stoi(trung)); ga->setGiaTrung(safe_stof(gt));
            Them(ga);
        }

        cout << "Da doc danh sach tu cac file (neu co).\n";
    }
};

/*---------------------------------------------------------
    MENU CHÍNH
---------------------------------------------------------*/
class CTrangTrai {
    CDanhSachThuNuoi ds;

public:
    CTrangTrai() { ds.DocFile(); }

    void MenuChinh() {
        int chon;
        do {
            TieuDe("MENU QUAN LY TRANG TRAI");
            cout << "1. Them Bo\n2. Them Heo\n3. Them Ga\n4. Hien thi danh sach (bang)\n5. Ban thu nuoi\n6. Xem tong doanh thu\n7. Luu danh sach ra file\n8. Xoa thu nuoi\n0. Thoat\nChon: ";
            cin >> chon;
            cin.ignore();

            if (chon == 1) {
                CThuNuoi *x = new CBo();
                x->Nhap();
                // Neu NSH nhap huy (MaSo==\"0\" hoac Ten==\"0\") thi khong them
                if (x->GetMaSo() != "0" && x->GetMaSo() != "") ds.Them(x);
                else delete x;
            }
            else if (chon == 2) {
                CThuNuoi *x = new CHeo();
                x->Nhap();
                if (x->GetMaSo() != "0" && x->GetMaSo() != "") ds.Them(x);
                else delete x;
            }
            else if (chon == 3) {
                CThuNuoi *x = new CGa();
                x->Nhap();
                if (x->GetMaSo() != "0" && x->GetMaSo() != "") ds.Them(x);
                else delete x;
            }
            else if (chon == 4) {
                // Goi ham bang phan trang
                ds.XuatDanhSachBang();
            }
            else if (chon == 5) {
                string ma; float gia;
                cout << "Nhap ma thu can ban: "; cin >> ma;
                cout << "Nhap gia ban: "; cin >> gia;
                ds.BanThuNuoi(ma, gia);
                Pause();
            }
            else if (chon == 6) {
                cout << "Tong doanh thu: " << fixed << setprecision(0) << ds.TongDoanhThu() << " VND\n";
                Pause();
            }
            else if (chon == 7) {
                ds.LuuFile();
                Pause();
            }
            else if (chon == 8) {
                string ma;
                cout << "Nhap ma thu muon xoa: ";
                cin >> ma;
                if (ds.XoaThuNuoi(ma))
                    cout << "Da xoa thanh cong!\n";
                else
                    cout << "Khong tim thay ma thu nuoi!\n";
                Pause();
            }

        } while (chon != 0);

        ds.LuuFile();
    }
};

#endif
