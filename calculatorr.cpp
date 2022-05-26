// calculatorr.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

const double Pi = acos(-1); //Объявляем значение числа Пи

struct Leksema //Структура, описывающая любое число или операцию
{
    char type; // 0 для чисел, "+" для операции сложения и т.д.
    double value; //Значение (только для чисел). У операций значение всегда "0"
};


//Математическая функция, которая производит расчеты
bool Maths(stack <Leksema>& Stack_n, stack <Leksema>& Stack_o, Leksema& item) { 
    //Функция имеет тип bool, чтобы при возникновении какой-либо ошибки возвращать "false"
    double a, b, c;
    a = Stack_n.top().value; //Берется верхнее число из стека с числами
    Stack_n.pop(); //Удаляется верхнее число из стека с числами
    switch (Stack_o.top().type) {  //Проверяется тип верхней операции из стека с операциями
    case '+': //Если тип верхней операции из стека с операциями сложение
        b = Stack_n.top().value;
        Stack_n.pop();
        c = a + b;
        item.type = '0';
        item.value = c;
        Stack_n.push(item); //Результат операции кладется обратно в стек с числами
        Stack_o.pop();
        break;

    case '-':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = b - a;
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;

    case '^':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = pow(b, a);
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;

    case '*':
        b = Stack_n.top().value;
        Stack_n.pop();
        c = a * b;
        item.type = '0';
        item.value = c;
        Stack_n.push(item);
        Stack_o.pop();
        break;

    case '/':
        b = Stack_n.top().value;
        if (a == 0) {
            cerr << "\n Ошибка \n";
            return false;
        }
        else {
            Stack_n.pop();
            c = (b / a);
            item.type = '0';
            item.value = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;
        }

     

    default:
        cerr << "\n Ошибка \n";
        return false;
        break;
    }
    return true;
}

int getRang(char Ch) { //функция приоритета
    
    if (Ch == '^')return 3;
    if (Ch == '+' || Ch == '-')return 1;
    if (Ch == '*' || Ch == '/')return 2;
    else return 0;
}

int main()
{


    setlocale(LC_ALL, "ru");
    while (true) {
        system("cls");
        
        cout << "   ТЕМА:СТРОКОВЫЙ КАЛЬКУЛЯТОР \t"
            << "\n АВТОР: ИВАНОВА ПОЛИНА \t"
            << "\n УСЛОВИЯ: СОЗДАТЬ СТРОКОВЫЙ КАЛЬКУЛЯТОР " << endl;
           cout << "   Для испрользования числа Пи введите 'p' \n";
           cout << "   Введите расчеты: ";
       
        std::string str;
        getline(cin, str);
        stringstream sstr{ str };

        char Ch; //Переменная, в которую будет записываться текущий обрабатываемый символ
        double value;
        bool flag = true; //Нужен для того, чтобы программа смогла отличить унарный минус (-5) от вычитания (2-5)
        stack<Leksema> Stack_n; //Стек с числами
        stack<Leksema> Stack_o; //Стек с операциями
        Leksema item; //Объект типа Leksema
        while (true) {
            Ch = sstr.peek(); //Смотрим на первый символ
            if (Ch == '\377')break; //Если достигнут конец строки, выходим из цикла
            if (Ch == ' ') { //Игнорирование пробелов
                sstr.ignore();
                continue;
            }
             if (Ch == 'p') { //Если прочитано число Пи
                item.type = '0';
                item.value = Pi;
                Stack_n.push(item); //Число кладется в стек с числами
                flag = 0;
                sstr.ignore();
                continue;                      
                } 
                 if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1) { //Если прочитано число
                sstr >> value;
                item.type = '0';
                item.value = value;
                Stack_n.push(item); //Число кладется в стек с числами
                flag = 0;
                continue;
           }        
                 
            
            if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/' || Ch == '^') { //Если прочитана операция
                if (Stack_o.size() == 0) { //Если стек с операциями пуст
                    item.type = Ch;
                    item.value = 0;
                    Stack_o.push(item); //Операция кладется в стек с операциями
                    sstr.ignore();
                    continue;
                }
             if (Stack_o.size() != 0 && getRang(Ch) >
                  //если не стек не пуст,но приоритет текущей операции выше верхней в стеке с операциями
                    getRang(Stack_o.top().type)) { 
                    item.type = Ch;
                    item.value = 0;
                    Stack_o.push(item); //Операция кладется в стек с операциями
                    sstr.ignore();
                    continue;
                }
              if (Stack_o.size() != 0 && getRang(Ch) <=
                    getRang(Stack_o.top().type)) {  //приоритет текущей операции ниже либо равен верхней в стеке с операциями
                    if (Maths(Stack_n, Stack_o, item) == false) { //Если функция вернет "false", то прекращаем работу
                        system("pause");
                        return 0;
                    }
                    continue;
                }
            }
              if (Ch == '(') { //Если прочитана открывающаяся скобка
                item.type = Ch;
                item.value = 0;
                Stack_o.push(item); //Операция кладется в стек с операциями
                sstr.ignore();
                continue;
            }  
              if (Ch == ')') { //Если прочитана закрывающаяся скобка
                while (Stack_o.top().type != '(') {
                    if (Maths(Stack_n, Stack_o, item) == false) { //Если функция вернет "false", то прекращаем работу
                        system("pause");
                        return 0;
                    }
                    else continue; 
                }
                Stack_o.pop();
                sstr.ignore();
                continue;
            }
           
            else { 
                cout << "\n Неверный ввод \n"; 
                system("pause");
                return 0;
            }
            
        }
        while (Stack_o.size() != 0)
             { 
            if (Maths(Stack_n, Stack_o, item) == false) { //Если функция вернет "false", то прекращаем работу
                system("pause");
                return 0;
            }
            else continue; 
        }
        cout << "   Ответ: " << Stack_n.top().value << endl; 
        system("pause");
    }
    return 0;
}