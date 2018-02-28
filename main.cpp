#include <iostream>
#include <fstream>
#include <locale>
#include <cstring>
#include <windows.h>
const int size_of_disk=360000;
int size_of_all=0;
using namespace std;
struct disk {
    string name;
 int size_of_sector=0;
 int size_of_file=0;
 bool Empty=1;
 disk *next;
};
void read_file(disk **tail){
ifstream in("dbase.txt");
string type;
string answer="b";
disk *temp=(*tail);
if (!in) {cout<<"�� ��������� ���� dbase.txt"<<endl; return;}
cout<<"�������� ������ �� �����."<<endl;
while(!in.eof())
    {
        (*tail)->next=new disk;
        (*tail)=(*tail)->next;
        in>>(*tail)->name>>(*tail)->size_of_file>>type;
        if(type!=answer) (*tail)->size_of_file=(*tail)->size_of_file*1000;
            if(((*tail)->size_of_file>=18)&&((*tail)->size_of_file<=32000))
            { size_of_all=size_of_all+(*tail)->size_of_file;
            (*tail)->Empty=0;
            (*tail)->next=NULL;
            (*tail)->size_of_sector=(*tail)->size_of_file;
            temp=(*tail);
                if(size_of_all>size_of_disk)
                    {cout<<"����������� ����� �� �����.���������� ������."<<endl;
                    size_of_all=size_of_all-(*tail)->size_of_file;
                    (*tail)=temp;
                    (*tail)->next=NULL;
                    return;}
            }
            else {cout<<"���� <"<<(*tail)->name<<"> �� ����������� �������. ������� �����."<<endl;
                size_of_all=size_of_all-(*tail)->size_of_file;
                (*tail)=temp;
                (*tail)->next=NULL;
                }
    }
    cout<<"������ �� ����� ���������."<<endl;

}
void delete_file(disk **head)
{   string temp_name;
    int temp_size;
    cout<<"������� ����, ������� ����� �������. ��������:\n<��� �����> <����� � ������>"<<endl;
    cin>>temp_name>>temp_size;
    disk* p=(*head)->next;
        while(p)
        {
            if(strcmp(temp_name.c_str(),p->name.c_str())==0) {
                if(temp_size==p->size_of_file)
                {
                    p->Empty=1;
                    p->size_of_file=0;
                    p->name.clear();
                    cout<<"DEL"<<endl;
                }
            }
            p=p->next;
        }
}
void add_file(disk **head, disk **tail)
{   string temp_name;
    int temp_size;
cout<<"������� ����, ������� ����� ��������. ��������:\n<��� �����> <����� � ������>"<<endl;
cin>>temp_name>>temp_size;
disk *temp=(*head)->next;
    while(temp)
    {
        if(temp->Empty==1)
            if(temp->size_of_sector>=temp_size)
            {
                temp->name=temp_name;
                temp->size_of_file=temp_size;
                temp->Empty=0; cout<<"���� ������� � ��������� ������"<<endl; return;
            }
            temp=temp->next;
    }
    if((size_of_disk-size_of_all)>temp_size) {cout<<"��������� �������� ����������� ������� �� �������.\n�������� �������� ���� � �����"<<endl;
                                                 if((size_of_all+temp_size)<size_of_disk) {
                                                (*tail)->next=new disk;
                                                (*tail)=(*tail)->next;
                                                (*tail)->Empty=0;
                                                (*tail)->name=temp_name;
                                                (*tail)->size_of_file=temp_size;
                                                (*tail)->size_of_sector=temp_size;
                                                (*tail)->next=NULL;
                                                cout<<"���� ������� � �����."<<endl;} else{cout<<"�� �������."<<endl;return;}}
    else cout<<"��������� �������� ����������� ������� �� �������.\n� ����� ����� ������������ ������������"<<endl;
}
int main()
{ setlocale(LC_ALL,"");
        disk *head=new disk;
        head->next=NULL;
        disk *tail=head;
read_file(&tail);
delete_file(&head);
add_file(&head,&tail);
    system("pause");
    return 0;
}
