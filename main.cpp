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
if (!in) {cout<<"Не обнаружен файл dbase.txt"<<endl; return;}
cout<<"Начинаем чтение из файла."<<endl;
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
                    {cout<<"Закончилось место на диске.Прекращаем чтение."<<endl;
                    size_of_all=size_of_all-(*tail)->size_of_file;
                    (*tail)=temp;
                    (*tail)->next=NULL;
                    return;}
            }
            else {cout<<"Файл <"<<(*tail)->name<<"> недопустимого размера. Пропуск файла."<<endl;
                size_of_all=size_of_all-(*tail)->size_of_file;
                (*tail)=temp;
                (*tail)->next=NULL;
                }
    }
    cout<<"Данные из файла прочитаны."<<endl;

}
void delete_file(disk **head)
{   string temp_name;
    int temp_size;
    cout<<"Укажите файл, который нужно удалить. Прототип:\n<Имя файла> <Длина в байтах>"<<endl;
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
                    cout<<"Файл удален."<<endl;return;
                }
            }
            p=p->next;
        }
        cout<<"Данного файла не найдено в базе."<<endl;
}
void add_file(disk **head, disk **tail)
{   string temp_name;
    int temp_size;
cout<<"Укажите файл, который нужно добавить. Прототип:\n<Имя файла> <Длина в байтах>"<<endl;
cin>>temp_name>>temp_size;
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
                 cout<<"Файл записан в свободный сектор."<<endl; return;
            }
            temp=temp->next;
            temp_for_temp=temp_for_temp->next;
    }
    if((size_of_disk-size_of_all)>temp_size) {cout<<"Свободных секторов подходящего размера не найдено.\nПытаемся записать файл в конец."<<endl;
                                                 if((size_of_all+temp_size)<size_of_disk) {
                                                (*tail)->next=new disk;
                                                (*tail)=(*tail)->next;
                                                (*tail)->Empty=0;
                                                (*tail)->name=temp_name;
                                                (*tail)->size_of_file=temp_size;
                                                (*tail)->size_of_sector=temp_size;
                                                (*tail)->next=NULL;
                                                cout<<"Файл записан в конец."<<endl;} else{cout<<"Не удалось."<<endl;return;}}
    else cout<<"Свободных секторов подходящего размера не найдено.\nВ конце диска пространства недостаточно."<<endl;
}
void show_all(disk *head)
{   int i=1;
    head=head->next;
    while(head)
    {
        cout<<"Сектор "<<i<<":";
        if(head->Empty==1)cout<<"Cвободный участок памяти размером "<<head->size_of_sector<<" байт"<<endl;
        else {cout<<"<"<<head->name<<"> SIZE:"<<head->size_of_file<<" байт"<<endl;}
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
    do{cout<<"\tВыберите действие:"<<endl<<"\t1)Добавить файл\n\t2)Удалить файл\n\t3)Просмотр содержимого диска\n\t4)Выход\n";
    cin>>selection;
    switch(selection){
        case 2:delete_file(&head);break;
        case 1:add_file(&head,&tail);break;
        case 3:show_all(head);break;}} while(selection!=4);
    system("pause");
    return 0;
}
