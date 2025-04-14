#include <iostream>
#include <string>

using namespace std;

// Структура ученика
struct Student {
    string surname;      // Фамилия
    int grades[4];       // Оценки
    Student* next;       // Следующий ученик
};

// Создаёт нового ученика и возвращает указатель на него
Student* createStudent() {
    Student* s = new Student;
    cout << "Введите фамилию: ";
    cin >> s->surname;

    cout << "Введите 4 оценки: ";
    for (int i = 0; i < 4; i++) {
        cin >> s->grades[i];
    }

    s->next = nullptr;
    return s;
}

// Добавляет ученика в начало списка
void addToStart(Student*& head, Student* newStudent) {
    newStudent->next = head;  // Новый указывает на текущую голову
    head = newStudent;        // Новый становится головой списка
}

// Проверяет, есть ли оценка меньше 3
bool hasBadGrade(Student* s) {
    for (int i = 0; i < 4; i++) {
        if (s->grades[i] < 3) return true;
    }
    return false;
}

// Печатает список учеников
void printList(Student* head) {
    Student* current = head;
    while (current != nullptr) {
        cout << current->surname<< ": ";
        for (int i = 0; i < 4; i++) {
            cout << current->grades[i] << " ";
        }
        cout << endl;
        current = current->next;
    }
}

// Удаляет неуспевающих учеников
void removeBadStudents(Student*& head) {
    // Удаляем плохих учеников в начале списка
    while (hasBadGrade(head)) {
        Student* temp = head;
        head = head->next;
        delete temp;
    }

    // Удаляем остальных
    Student* current = head;
    while (current->next != nullptr) {
        if (hasBadGrade(current->next)) {
            Student* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
        else {
            current = current->next;
        }
    }
}

// Очищает память
void clearList(Student* head) {
    while (head != nullptr) {
        Student* temp = head;
        head = head->next;
        delete temp;
    }
}

// Главная функция
int main() {
    setlocale(LC_ALL, "ru");
    int count;// Создам счетчик
    int i;
    int grades;
    cout << "Сколько учеников? ";
    cin >> count;

    Student* head = nullptr;  // Начало списка

    for (int i = 0; i < count; i++) {
        Student* s = createStudent();   // Создаём ученика
        addToStart(head, s);            // Добавляем в начало списка
    }

    cout << "\nВсе ученики:\n";
    printList(head);                    // Показываем всех

    removeBadStudents(head);            // Удаляем неуспевающих

    cout << "\nПосле удаления неуспевающих:\n";
    printList(head);                    // Показываем оставшихся

    clearList(head);                    // Очищаем память
    return 0;
}