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
            else {cout<<"���� <"<<(*tail)->name<<"> ������������� �������. ������� �����."<<endl;
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
                    cout<<"���� ������."<<endl;return;
                }
            }
            p=p->next;
        }
        cout<<"������� ����� �� ������� � ����."<<endl;
}
void add_file(disk **head, disk **tail)
{   string temp_name;
    int temp_size;
cout<<"������� ����, ������� ����� ��������. ��������:\n<��� �����> <����� � ������>"<<endl;
cin>>temp_name>>temp_size;
if((temp_size<=18)||(temp_size>=32000)) {cout<<"���� ������������� �������."<<endl;return;}
disk *temp=(*head)->next;
disk *temp_for_temp=(*head);
    while(temp)
    {
        if(temp->Empty==1)
            if(temp->size_of_sector>=temp_size)
            {   if(temp->size_of_sector!=temp_size){disk *NewNode=new disk;
                NewNode->name=temp_name;
                NewNode->size_of_file=temp_size;
                NewNode->Empty=0;
                NewNode->size_of_sector=NewNode->size_of_file;
                temp->size_of_sector=temp->size_of_sector-temp_size;
                temp_for_temp->next=NewNode;
                NewNode->next=temp;}else {temp->Empty=0;temp->name=temp_name;temp->size_of_file=temp_size;}
                 cout<<"���� ������� � ��������� ������."<<endl; return;
            }
            temp=temp->next;
            temp_for_temp=temp_for_temp->next;
    }
    if((size_of_disk-size_of_all)>temp_size) {cout<<"��������� �������� ����������� ������� �� �������.\n�������� �������� ���� � �����."<<endl;
                                                 if((size_of_all+temp_size)<size_of_disk) {
                                                (*tail)->next=new disk;
                                                (*tail)=(*tail)->next;
                                                (*tail)->Empty=0;
                                                (*tail)->name=temp_name;
                                                (*tail)->size_of_file=temp_size;
                                                (*tail)->size_of_sector=temp_size;
                                                (*tail)->next=NULL;
                                                cout<<"���� ������� � �����."<<endl;} else{cout<<"�� �������."<<endl;return;}}
    else cout<<"��������� �������� ����������� ������� �� �������.\n� ����� ����� ������������ ������������."<<endl;
}
void show_all(disk *head)
{   int i=1;
    head=head->next;
    while(head)
    {
        cout<<"������ "<<i<<":";
        if(head->Empty==1)cout<<"C�������� ������� ������ �������� "<<head->size_of_sector<<" ����"<<endl;
        else {cout<<"<"<<head->name<<"> SIZE:"<<head->size_of_file<<" ����"<<endl;}
        i++;
        head=head->next;
    }
}
int main()
{ setlocale(LC_ALL,"");
        disk *head=new disk;
        head->next=NULL;
        disk *tail=head;
 read_file(&tail);
    int selection;
    do{cout<<"\t�������� ��������:"<<endl<<"\t1)�������� ����\n\t2)������� ����\n\t3)�������� ����������� �����\n\t4)�����\n";
    cin>>selection;
    switch(selection){
        case 2:delete_file(&head);break;
        case 1:add_file(&head,&tail);break;
        case 3:show_all(head);break;}} while(selection!=4);
    system("pause");
    return 0;
}
