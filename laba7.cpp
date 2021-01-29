
#include "laba7.h"
#include "ui_laba7.h"
#include <QValidator>
#include "QMessageBox"
#include <cstdlib>
#include <cstring>
#include <iostream>

laba7::laba7(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::laba7)
{
    ui->setupUi(this);
    ui->Number->setValidator(new QRegExpValidator(QRegExp("^[0-9-.]{0,10}$\\d"), this));//задаем то,что можно вводить ^$-ограничивает выражение не забывать про них
}

laba7::~laba7()
{
    delete ui;
}
QString laba7::opisanie(double num,  *s/*сюда мы будем заносить целую часть прописью+ дробуню часть прописью*/) // num — число, s — указатель на строку
{
    size_t position = 0; // позиция в строке ВАЖНАЯ ПЕРЕМЕННАЯ!
    int x[4]; // массив разрядов
    int div = 1000; // делитель на разряды (если нужно будет увеличить то тут 10000 100000 и т.д в зависимости от кол-ва разрядов (смотри for-ы на длину числа!)
    double var;
    if (num<0)//умножаем число на -1 для удобности проверки длины и счета в последующих частях кода
    {
        var = num*(-1); // частное от деления
    }
    else//если число положительное ничего не меняем
    {
        var=num;
    }
    double rest; // остаток от деления
    //size_t count = sizeof(s)/sizeof(s[0]);
    int k;//для определения индекса точки в массиве с символов состоящего из всего числа ВАЖНО!

    for (int i=0;i<4; i++)//<4т.к максимальное число 9999 и содержит оно 4 разряда
    {
        rest = var/div;//путем деления исходного числа на 1000/100/10 находим значения разрядов и вносим их в массив
        x[i] = rest;
        var = var-rest*div;
        div = div/10;
    }
    // Тысячи
    QString line3 =ui->Number->text();
    QByteArray temp3 = line3.toLocal8Bit();//переносим строку в массив char
    char* Str3=temp3.data();
    char s3[11];//массив для всего числа с дробной частью и точкой
    std::copy(Str3,Str3+10,s3);//копируем первую цифру и проверяем на минус или ноль
    QString length_s3=QString(s3);
    int IntLength_s3=length_s3.length();//переменные подобного рода для высчета длины массива
    bool CheckMinusOrNull=true;//очевидно
    bool CheckTo4ka=true;
    for (int i=0;i<10;i++)//на случай 1231. или -1232. пробегаемся по числу
    {
        if ((s3[i]=='.')&&(((s3[i+1]=='\0'))))
        {
            QMessageBox::warning(this,"Предупреждение","Введите корректное число");
            CheckTo4ka=false;
            return nullptr;
        }
        if ((s3[i]=='.')&&(((s3[i+1]!='\0'))))
        {
            break;
        }
    }
    if ((s3[0]=='-')&&(s3[1]=='.'))//или -.
    {
        QMessageBox::warning(this,"Предупреждение","Введите корректное число");
        CheckTo4ka=false;
        return nullptr;
    }
    else if (s3[0]=='.')// или .3 .1323
    {
        QMessageBox::warning(this,"Предупреждение","Введите корректное число");
        CheckTo4ka=false;
        return nullptr;
    }
    else if (Str3==strchr(Str3,'-'))// если во всей строке есть минус
    {
        if ((num*1>-1&&num*1<0)||(num*1==0.0))//минус и ноль или -0.423
        {
            strcpy(s, "минус ноль ");
        }
        else
        {
            strcpy(s, "минус ");
        }
        position = strlen(s);
        CheckMinusOrNull=false;
    }
    else if (num*1>=0&&num*1<1)// для 0.23
    {
        strcpy(s, "ноль ");
        position = strlen(s);
        CheckMinusOrNull=false;
    }
   char* OneTwo[10]={"одна","две","три","четыре","пять","шест","cемь","восемь","девять"};
    if (CheckTo4ka)//если все вышеизложенные проверки пройдены
    {
        if (x[0]==1)
        {
            strcpy(s+position,OneTwo[0]);
            position = strlen(s);
        strcpy(s+position,"тысяча ");
        }
        position = strlen(s);
        switch (x[0])//начинаем првоерять разряды
        {
        //case 1: strcpy(s+position, "одна тысяча "); break;
        case 2: strcpy(s+position, "две тысячи "); break;
        case 3: strcpy(s+position, "три тысячи "); break;
        case 4: strcpy(s+position, "четыре тысячи "); break;
        case 5: strcpy(s+position, "пять тысяч "); break;
        case 6: strcpy(s+position, "шесть тысяч "); break;
        case 7: strcpy(s+position, "семь тысяч "); break;
        case 8: strcpy(s+position, "восемь тысяч "); break;
        case 9: strcpy(s+position, "девять тысяч "); break;
        default: break;
        }
        position = strlen(s);
        // Сотни
        switch (x[1])
        {
        case 1: strcpy(s + position, "сто "); break;
        case 2: strcpy(s + position, "двести "); break;
        case 3: strcpy(s + position, "триста "); break;
        case 4: strcpy(s + position, "четыреста "); break;
        case 5: strcpy(s + position, "пятьсот "); break;
        case 6: strcpy(s + position, "шестьсот "); break;
        case 7: strcpy(s + position, "семьсот "); break;
        case 8: strcpy(s + position, "восемьсот "); break;
        case 9: strcpy(s + position, "девятьсот "); break;
        default: break;
        }
        position = strlen(s);
        // Десятки
        switch (x[2])
        {
        case 1:
            // Числа от 10 до 19
            switch (x[3])
            {
            case 0: strcpy(s + position, "десять "); break;
            case 1: strcpy(s + position, "одиннадцать "); break;
            case 2: strcpy(s + position, "двенадцать "); break;
            case 3: strcpy(s + position, "тринадцать "); break;
            case 4: strcpy(s + position, "четырнадцать "); break;
            case 5: strcpy(s + position, "пятнадцать "); break;
            case 6: strcpy(s + position, "шестнадцать "); break;
            case 7: strcpy(s + position, "семнадцать "); break;
            case 8: strcpy(s + position, "восемнадцать "); break;
            case 9: strcpy(s + position, "девятнадцать "); break;
            }
            x[3] = 0;
            position = strlen(s);
            break;
        case 2: strcpy(s + position, "двадцать "); break;
        case 3: strcpy(s + position, "тридцать "); break;
        case 4: strcpy(s + position, "сорок "); break;
        case 5: strcpy(s + position, "пятьдесят "); break;
        case 6: strcpy(s + position, "шестьдесят "); break;
        case 7: strcpy(s + position, "семьдесят "); break;
        case 8: strcpy(s + position, "восемьдесят "); break;
        case 9: strcpy(s + position, "девяносто "); break;
        default: break;
        }
        position = strlen(s);
        // Единицы
        for (int i=0;i<11;i++)
        {
            if (s3[i]=='.')
            {
                k=i+1;//для копирования числа после точки в массив чар нужен  индекс, следующий за точкой
                QString line =ui->Number->text();
                QByteArray temp = line.toLocal8Bit();//переносим строку в массив char
                char* Str=temp.data();
                if (true)
                {
                    if (s3[0]=='-'&&s3[1]=='1'&&s3[2]=='.')
                    {
                        strcpy(s + position, "одна ");
                    }
                    else if (s3[0]=='-'&&s3[1]=='1')
                    {
                        strcpy(s + position, "один ");
                    }
                    else if (s3[0]=='1'&&s3[1]=='.')
                    {
                        strcpy(s + position, "одна ");
                    }
                    else
                    {
                        switch (x[3])
                        {
                        case 1:switch (position)//если ноль значит нету цифр и число будет ли 1. ... или 2. ...
                            {
                            case 0: strcpy(s + position, "один "); break;
                            default:strcpy(s + position, "одна "); break;
                            }break;
                        case 2:switch (position)
                            {
                            case 0: strcpy(s + position, "два "); break;
                            default: strcpy(s + position, "две "); break;
                            }break;
                        case 3: strcpy(s + position, "три "); break;
                        case 4: strcpy(s + position, "четыре "); break;
                        case 5: strcpy(s + position, "пять "); break;
                        case 6: strcpy(s + position, "шесть "); break;
                        case 7: strcpy(s + position, "семь "); break;
                        case 8: strcpy(s + position, "восемь "); break;
                        case 9: strcpy(s + position, "девять "); break;
                        default: break;
                        }
                    }
                }
                position = strlen(s);
                char s1[160];//массив для чисел после точки
                std::copy(Str+k,Str+(100-k),s1);//копируем ЦИФРЫ после точки
                QString length_s1=QString(s1);
                int IntLength_s1=length_s1.length();//а это кол-во цифр в будующем
                int IntLength_s1Char=length_s1.length();//это кол-во символов
                char s2[160];
                for (int i=0;i<11;i++)//копируем число после точки
                {
                    if (s3[i]=='.')
                    {
                        break;
                    }
                    s2[i]=s3[i];
                }
                QString length_s2=QString(s2);
                int IntLength_s2=length_s2.length();
                if (num>0&&(num>1))// проверяем длину чисел после и до точки не включительно
                {
                    if ((IntLength_s2>4))//почему-то меньше на один с точкой( уже не актуально)
                    {
                        QMessageBox::warning(this,"Предупреждение","Число слишком длинное");
                        return nullptr;
                    }
                }
                else if (num<0&&(num<-1))
                {
                    if ((IntLength_s2>5))
                    {
                        QMessageBox::warning(this,"Предупреждение","Число слишком длинное");
                        return nullptr;
                    }
                }
                if (IntLength_s1>4)
                {
                    QMessageBox::warning(this,"Предупреждение","Число слишком длинное");
                    return nullptr;
                }
                QString tmp=QString(s1);//берем массив с остатком и в qstring
                int tmp1=tmp.toInt();//переводим из qstring в int
                int VarOst=tmp1;// присваиваем для пересчета остатка прописью
                int check1000=1000;// для ситуаций вида 0.1000  (везде 1 десятая)
                int check100=100;//0.100
                int check10=10;//0.10
                bool check=true;// не дает делить число дальше
                if (VarOst%check1000==0&&check)//если делится без остатка на 1000
                {
                    IntLength_s1=1;
                    VarOst=VarOst/1000;
                    check=false;
                }
                else if (VarOst%check100==0&&check)//если делится без остатка на 100
                {
                    if (IntLength_s1Char==4)//именно для количества символов в строке
                    {
                        if ((VarOst/check100)%check10!=0)//ведь например 1200 может поделиться на 100 а вот уже и на 10 без остатка нет
                        {
                            IntLength_s1=2;// а это уже для количества цифр
                        }
                    }
                    if (IntLength_s1Char==3)
                    {
                        IntLength_s1=1;
                    }
                    VarOst=VarOst/100;
                    check=false;
                }
                else if (VarOst%check10==0&&check)//если делится без остатка на 10
                {
                    if (IntLength_s1Char==4)
                    {
                        IntLength_s1=3;
                    }
                    if (IntLength_s1Char==3)
                    {
                        IntLength_s1=2;
                    }
                    if (IntLength_s1Char==2)
                    {
                        IntLength_s1=1;
                    }
                    VarOst=VarOst/10;
                    check=false;
                }
                else
                {
                    IntLength_s1=length_s1.length();
                }
                //считаем остаток
                size_t position1 = 0; // позиция в строке
                int y[4]; // массив разрядов
                int div1 = 1000; // делитель на разряды
                int rest1; // остаток от деления
                char ost[160];//массив для записи дробной части прописью
                strcpy(ost, "целых ");
                position1 = strlen(ost);//позиция в строке с дробной частью ВАЖНО!
                if ((IntLength_s3<4&&IntLength_s3>0)&&(s3[0]=='1'))//проверяем окончание единицы и двойки
                {
                    strcpy(ost, "целая ");
                }
                else if ((s3[0]=='1')&&(s3[1]=='.'))
                {
                    strcpy(ost, "целая ");
                }
                else if ((s3[0]!='1')&&(s3[1]=='1')&&(s3[2]=='.'))
                {
                    strcpy(ost, "целая ");
                }
                else if ((s3[1]!='1')&&(s3[2]=='1')&&(s3[3]=='.'))
                {
                    strcpy(ost, "целая ");
                }
                else if ((s3[3]!='1')&&(s3[4]=='1')&&(s3[5]=='.'))
                {
                    strcpy(ost, "целая ");
                }
                else if ((s3[3]=='1')&&(s3[4]=='.'))
                {
                    strcpy(ost, "целая ");
                }
                else if ((IntLength_s3<4&&IntLength_s3>0)&&(s3[0]=='2'))
                {
                    strcpy(ost, "целые ");
                }
                else if ((s3[0]=='1')&&(s3[1]=='2')&&(s3[2]=='.'))
                {
                    strcpy(ost, "целых ");
                }
                else if ((s3[0]!='1')&&(s3[0]=='2')&&(s3[1]=='.'))
                {
                    strcpy(ost, "целые ");
                }
                else if ((s3[1]=='2')&&(s3[2]=='.'))
                {
                    strcpy(ost, "целые ");
                }
                else if ((s3[2]=='2')&&(s3[3]=='.'))
                {
                    strcpy(ost, "целые ");
                }
                else if ((s3[3]=='2')&&(s3[4]=='.'))
                {
                    strcpy(ost, "целые ");
                }
                else
                {
                    strcpy(ost, "целых ");
                }
                position1 = strlen(ost);//позиция в строке с дробной частью ВАЖНО!

                for (int i=0;i<4; i++)//забиваем массив разрядов значениями разрядов дробной части также деля на 1000 (увеличение диапазона аналогично с целой частью)
                {
                    rest1 = VarOst/div1;
                    y[i] = rest1;
                    VarOst = VarOst-rest1*div1;
                    div1 = div1/10;
                }
                // Тысячи
                switch (y[0])
                {
                case 1: strcpy(ost + position1, "одна тысяча "); break;
                case 2: strcpy(ost + position1, "две тысячи "); break;
                case 3: strcpy(ost + position1, "три тысячи "); break;
                case 4: strcpy(ost + position1, "четыре тысячи "); break;
                case 5: strcpy(ost + position1, "пять тысяч "); break;
                case 6: strcpy(ost + position1, "шесть тысяч "); break;
                case 7: strcpy(ost + position1, "семь тысяч "); break;
                case 8: strcpy(ost + position1, "восемь тысяч "); break;
                case 9: strcpy(ost + position1, "девять тысяч "); break;
                default: break;
                }
                position1 = strlen(ost);
                // Сотни
                switch (y[1])
                {
                case 1: strcpy(ost + position1, "сто "); break;
                case 2: strcpy(ost + position1, "двести "); break;
                case 3: strcpy(ost + position1, "триста "); break;
                case 4: strcpy(ost + position1, "четыреста "); break;
                case 5: strcpy(ost + position1, "пятьсот "); break;
                case 6: strcpy(ost + position1, "шестьсот "); break;
                case 7: strcpy(ost + position1, "семьсот "); break;
                case 8: strcpy(ost + position1, "восемьсот "); break;
                case 9: strcpy(ost + position1, "девятьсот "); break;
                default: break;
                }
                position1 = strlen(ost);
                // Десятки
                switch (y[2])
                {
                case 1:
                    // Числа от 10 до 19
                    switch (y[3])
                    {
                    case 0: strcpy(ost + position1, "десять "); break;
                    case 1: strcpy(ost + position1, "одиннадцать "); break;
                    case 2: strcpy(ost + position1, "двенадцать "); break;
                    case 3: strcpy(ost + position1, "тринадцать "); break;
                    case 4: strcpy(ost + position1, "четырнадцать "); break;
                    case 5: strcpy(ost + position1, "пятнадцать "); break;
                    case 6: strcpy(ost + position1, "шестнадцать "); break;
                    case 7: strcpy(ost + position1, "семнадцать "); break;
                    case 8: strcpy(ost + position1, "восемнадцать "); break;
                    case 9: strcpy(ost + position1, "девятнадцать "); break;
                    }
                    y[3] = 0;
                    position1 = strlen(ost);
                    break;
                case 2: strcpy(ost + position1, "двадцать "); break;
                case 3: strcpy(ost + position1, "тридцать "); break;
                case 4: strcpy(ost + position1, "сорок "); break;
                case 5: strcpy(ost + position1, "пятьдесят "); break;
                case 6: strcpy(ost + position1, "шестьдесят "); break;
                case 7: strcpy(ost + position1, "семьдесят "); break;
                case 8: strcpy(ost + position1, "восемьдесят "); break;
                case 9: strcpy(ost + position1, "девяносто "); break;
                default: break;
                }
                position1 = strlen(ost);
                // Единицы
                switch (y[3])
                {
                case 1: strcpy(ost + position1, "одна "); break;
                case 2: strcpy(ost + position1, "две "); break;
                case 3: strcpy(ost + position1, "три "); break;
                case 4: strcpy(ost + position1, "четыре "); break;
                case 5: strcpy(ost + position1, "пять "); break;
                case 6: strcpy(ost + position1, "шесть "); break;
                case 7: strcpy(ost + position1, "семь "); break;
                case 8: strcpy(ost + position1, "восемь "); break;
                case 9: strcpy(ost + position1, "девять "); break;
                default: break;
                }
                position=strlen(s);
                position1 = strlen(ost);
                //ПРОВЕРКИ ВАРИАТИВНЫХ ОКОНЧАНИЙ s1-цифры псле точки s2-цифры до точки
                if (IntLength_s1==0)
                {
                    strcpy(ost+position1," ");
                    strcpy(s+position,ost);
                }
                if (IntLength_s1==1)
                {
                    if ((s1[0]='1'))
                    {
                        strcpy(ost+position1,"десятая ");
                    }
                    else if ((s1[0]='0'))
                    {
                        strcpy(ost+position1,"ноль десятых ");
                    }
                    else
                    {
                        strcpy(ost+position1,"десятых ");
                    }
                    strcpy(s+position,ost);
                }
                if (IntLength_s1==2)
                {
                    if ((s1[0]=='0' && s1[1]=='1')||(s1[0]!='1' && s1[1]=='1'))
                    {
                        strcpy(ost+position1,"сотая ");
                    }
                    else
                    {
                        strcpy(ost+position1,"сотых ");
                    }
                    strcpy(s+position,ost);
                }
                if (IntLength_s1==3)
                {
                    if ((s1[0]=='0')&&(s1[1]=='1')&&(s1[2]=='0'))
                    {
                        strcpy(ost+position1,"сотая ");
                    }
                    if ((s1[0]=='0')&&(s1[1]!='0')&&(s1[1]!='1'))
                    {
                        strcpy(ost+position1,"сотых ");
                    }
                    else if ((s1[2]=='1')&&(s1[1]!='1'))
                    {
                        strcpy(ost+position1,"тысячная ");
                    }
                    else
                    {
                        strcpy(ost+position1,"тысячных ");
                    }
                    strcpy(s+position,ost);
                }
                if (IntLength_s1==4)
                {
                    if ((s1[0]=='0')&&(s1[1]=='0')&&(s1[2]=='1')&&(s1[3]=='0'))
                    {
                        strcpy(ost+position1,"тысячная ");
                    }
                    else if ((s1[0]=='0')&&(s1[1]=='0')&&(s1[2]=='0')&&(s1[2]!='1')&&(s1[3]=='0'))
                    {
                        strcpy(ost+position1,"тысячных ");
                    }
                    else if ((s1[3]=='1')&&(s1[2]!='1'))
                    {
                        strcpy(ost+position1,"десятитысячная ");
                    }
                    else
                    {
                        strcpy(ost+position1,"десятитысячных ");
                    }

                    strcpy(s+position,ost);
                }
                return s;
            }
        }
        QString length_s3=QString(s3);
        int IntLength_s3=length_s3.length();
        if (IntLength_s3>5&&s3[0]=='-')//проверка длины всего числа с учетом минуса спереди (Учесть при увеличении диапазона)
        {
            QMessageBox::warning(this,"Предупреждение","Число слишком длинное");
            return nullptr;
        }
        else if (IntLength_s3>4&&s3[0]!='-')
        {
            QMessageBox::warning(this,"Предупреждение","Число слишком длинное");
            return nullptr;
        }
        else//подвох с единицей и двойкой и их окончаниями то что снизу для целого числа иначе когда нет точки то выполняется это
        {
            switch (x[3])
            {
            case 1:strcpy(s + position, "один "); break;
            case 2:strcpy(s + position, "два "); break;
            case 3: strcpy(s + position, "три "); break;
            case 4: strcpy(s + position, "четыре "); break;
            case 5: strcpy(s + position, "пять "); break;
            case 6: strcpy(s + position, "шесть "); break;
            case 7: strcpy(s + position, "семь "); break;
            case 8: strcpy(s + position, "восемь "); break;
            case 9: strcpy(s + position, "девять "); break;
            default: break;
            }
            return s;
        }
    }
    else return s;
}


void laba7::on_pushButton_clicked()//если нажата кнопка перевести
{
    bool ok;//проверяем конвертируемость
    double m=ui->Number->text().toDouble(&ok);//считываем и конвертируем в дабл чило с строки
    if (ok)//если все верно конвертировалось
    {
        char s[160];//создаем массив для числа
        char*p=s;//указатель на массив (а нужен ли он?)
        ui->Result->setText(opisanie(m,p));//выставляем результат отработки функции
    }
    else
    {
        QMessageBox::warning(this,"Предупреждение","Введите корректное число");
    }
}

void laba7::on_Number_textEdited(const QString &arg1)//чистка в режиме реального времени
{
    ui->Result->clear();
}
