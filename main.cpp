#include <iostream>
#include <fstream>
#include <locale>
const int size_of_disk=360;
int size_of_all=0;
using namespace std;
struct disk {
    string name;
 int size_of_sector=0;
 int size_of_file=0;
 bool Empty;
 disk *next;
};
void read_file(disk **tail){
ifstream in("in.txt");
disk *temp=(*tail);
if (!in) {cout<<"�� ��������� ���� in.txt"<<endl; return;}
cout<<"�������� ������ �� �����."<<endl;
while(!in.eof())
    {
        (*tail)->next=new disk;
        (*tail)=(*tail)->next;
        in>>(*tail)->name>>(*tail)->size_of_file;
            if(((*tail)->size_of_file>=18)&&((*tail)->size_of_file<=36))
            { size_of_all=size_of_all+(*tail)->size_of_file;
            (*tail)->Empty=0;
            (*tail)->next=NULL;
            (*tail)->size_of_sector=(*tail)->size_of_file;
            temp=(*tail);
            cout<<(*tail)->name<<" "<<(*tail)->size_of_file<<endl;
            }
            else {cout<<"����: "<<(*tail)->name<<" �� ����������� �������. ������� �����."<<endl;
                size_of_all=size_of_all-(*tail)->size_of_file;
                (*tail)=temp;
                (*tail)->next=NULL;
                }
        else {cout<<"����������� ����� �� �����.���������� ������."<<endl;
            (*tail)=temp;
            (*tail)->next=NULL;
            return;}
    }
    cout<<"������ �� ����� ���������"<<endl;

}
int main()
{ setlocale(LC_ALL,"");
    disk *beg=new disk;
beg->next=NULL;
disk *tail=beg;
read_file(&tail);
cout<<beg->next->name<<" "<<beg->next->size_of_file;
    return 0;
}
