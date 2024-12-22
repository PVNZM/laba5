#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <cstring>
#include <limits>

using namespace std;

// Определение структуры для багажа
struct Baggage {
    char name[50]; // Название единицы багажа
    float weight;  // Масса багажа
};

class DataProcessor {
public:
    static const int NUM_COUNT = 100; // Количество чисел для бинарного файла
    static const int BAGGAGE_COUNT = 10; // Количество единиц багажа
    static const int TEXTFILE_COUNT = 100; // Количество чисел для текстового файла
    static const int TEXTFILE_MULTIPLE_COUNT = 10; // Числа по несколько в строке для задания 5
    static const string NUMBERS_FILENAME; // Имя бинарного файла для чисел
    static const string BAGGAGE_FILENAME; // Имя бинарного файла для багажа
    static const string TEXT_FILENAME; // Имя текстового файла
    static const string MULTIPLE_TEXT_FILENAME; // Имя файла для задания 5
    static const string SOURCE_TEXT_FILENAME;    // Имя исходного текстового файла
    static const string DESTINATION_TEXT_FILENAME; // Имя конечного текстового файла

    
    // Метод для заполнения бинарного файла случайными числами
    static void fillNumbersFile() {
        ofstream outFile(NUMBERS_FILENAME, ios::binary);
        if (!outFile) {
            cerr << "Не удалось открыть файл для записи!" << endl;
            return;
        }

        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < NUM_COUNT; ++i) {
            int number = rand() % 200 - 100; // Генерируем случайное число от -100 до 99
            outFile.write(reinterpret_cast<const char*>(&number), sizeof(number));
        }

        outFile.close();
    }

    // Метод для подсчета пар противоположных чисел
    static int countOppositePairs() {
        ifstream inFile(NUMBERS_FILENAME, ios::binary);
        if (!inFile) {
            cerr << "Не удалось открыть файл для чтения!" << endl;
            return 0;
        }

        vector<int> numbers;
        int number;

        // Читаем числа из файла
        while (inFile.read(reinterpret_cast<char*>(&number), sizeof(number))) {
            numbers.push_back(number);
        }

        inFile.close();

        int count = 0;

        // Подсчет пар противоположных чисел
        for (size_t i = 0; i < numbers.size(); ++i) {
            for (size_t j = i + 1; j < numbers.size(); ++j) {
                if (numbers[i] + numbers[j] == 0) {
                    count++;
                }
            }
        }

        return count;
    }

    // Метод для копирования элементов в квадратную матрицу и замены элементов на максимальные в столбцах
    static void copyToSquareMatrix(int n) {
        ifstream inFile(NUMBERS_FILENAME, ios::binary);
        if (!inFile) {
            cerr << "Не удалось открыть файл для чтения!" << endl;
            return;
        }

        vector<vector<int>> matrix(n, vector<int>(n, 0));
        int number;
        int index = 0;

        // Заполнение матрицы элементами из файла
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (index < NUM_COUNT && inFile.read(reinterpret_cast<char*>(&number), sizeof(number))) {
                    matrix[i][j] = number;
                }
                index++;
            }
        }

        inFile.close();

        // Замена элементов на максимальные в каждом столбце
        for (int j = 0; j < n; ++j) {
            int maxElement = matrix[0][j];
            for (int i = 1; i < n; ++i) {
                if (matrix[i][j] > maxElement) {
                    maxElement = matrix[i][j];
                }
            }
            for (int i = 0; i < n; ++i) {
                matrix[i][j] = maxElement;
            }
        }

        // Вывод матрицы на экран
        cout << "Полученная матрица:\n";
        for (const auto& row : matrix) {
            for (int val : row) {
                cout << setw(4) << val << " "; // форматированный вывод
            }
            cout << endl;
        }
    }

    // Метод для заполнения бинарного файла с информацией о багаже
    static void fillBaggageFile() {
        ofstream outFile(BAGGAGE_FILENAME, ios::binary);
        if (!outFile) {
            cerr << "Не удалось открыть файл для записи багажа!" << endl;
            return;
        }

        string baggageNames[BAGGAGE_COUNT] = {
            "Чемодан", "Сумка", "Коробка", "Рюкзак", "Дорожная сумка",
            "Пакет", "Кейс", "Ящик", "Сумка для ноутбука", "Термос"
        };

        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < BAGGAGE_COUNT; ++i) {
            Baggage baggage;
            strncpy(baggage.name, baggageNames[i].c_str(), sizeof(baggage.name) - 1);
            baggage.name[sizeof(baggage.name) - 1] = '\0'; // Обеспечим нуль-терминатор
            baggage.weight = (rand() % 200 + 1) / 10.0f; // Генерируем массу от 0.1 до 20.0 кг
            outFile.write(reinterpret_cast<const char*>(&baggage), sizeof(baggage));
        }

        outFile.close();
    }

    // Метод для вычисления разницы между максимальной и минимальной массой багажа
    static float calculateWeightDifference() {
        ifstream inFile(BAGGAGE_FILENAME, ios::binary);
        if (!inFile) {
            cerr << "Не удалось открыть файл для чтения багажа!" << endl;
            return 0.0f;
        }

        Baggage baggage;
        float maxWeight = 0.0f;
        float minWeight = numeric_limits<float>::max(); // Минимальное значение инициализируется максимально возможным

        // Читаем данные о багаже и определяем максимальную и минимальную массу
        while (inFile.read(reinterpret_cast<char*>(&baggage), sizeof(baggage))) {
            if (baggage.weight > maxWeight) {
                maxWeight = baggage.weight;
            }
            if (baggage.weight < minWeight) {
                minWeight = baggage.weight;
            }
        }

        inFile.close();

        return maxWeight - minWeight; // Возвращаем разницу
    }

    // Метод для заполнения текстового файла случайными целыми числами
    static void fillTextFile() {
        ofstream outFile(TEXT_FILENAME);
        if (!outFile) {
            cerr << "Не удалось открыть текстовый файл для записи!" << endl;
            return;
        }

        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < TEXTFILE_COUNT; ++i) {
            int number = rand() % 200 - 100; // Генерируем случайное число от -100 до 99
            outFile << number << endl; // Записываем в файл по одному числу в строке
        }

        outFile.close();
    }

    // Метод для проверки наличия нуля в текстовом файле
    static bool containsZeroInFile() {
        ifstream inFile(TEXT_FILENAME);
        if (!inFile) {
            cerr << "Не удалось открыть текстовый файл для чтения!" << endl;
            return false;
        }

        int number;

        // Читаем числа из файла и проверяем на наличие нуля
        while (inFile >> number) {
            if (number == 0) {
                inFile.close();
                return false; // Файл содержит ноль
            }
        }

        inFile.close();
        return true; // Файл не содержит ноль
    }

    // Метод для заполнения текстового файла случайными целыми числами несколько в строке
    static void fillMultipleTextFile() {
        ofstream outFile(MULTIPLE_TEXT_FILENAME);
        if (!outFile) {

            cerr << "Не удалось открыть текстовый файл для записи!" << endl;
            return;
        }

        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < TEXTFILE_COUNT / TEXTFILE_MULTIPLE_COUNT; ++i) {
            for (int j = 0; j < TEXTFILE_MULTIPLE_COUNT; ++j) {
                int number = rand() % 200 - 100; // Генерируем случайное число от -100 до 99
                if (j > 0) outFile << " "; // Разделитель между числами
                outFile << number; // Записываем число
            }
            outFile << endl; // Переход на новую строку
        }

        outFile.close();
    }

    // Метод для нахождения максимального элемента в текстовом файле
    static int findMaxInMultipleTextFile() {
        ifstream inFile(MULTIPLE_TEXT_FILENAME);
        if (!inFile) {
            cerr << "Не удалось открыть текстовый файл для чтения!" << endl;
            return 0; // Возможно, имеет смысл возвращать какое-то специальное значение, например, INT_MIN
        }

        int number;
        int maxNumber = numeric_limits<int>::min(); // Инициализируем минимальным значением для int

        // Читаем числа из файла и находим максимальное
        while (inFile >> number) {
            if (number > maxNumber) {
                maxNumber = number;
            }
        }

        inFile.close();
        return maxNumber;  // Возвращаем максимальное найденное число
    }

    // Метод для создания исходного текстового файла с заданным текстом
    static void createSourceFile() {
        ofstream outFile(SOURCE_TEXT_FILENAME);
        if (!outFile) {
            cerr << "Не удалось открыть файл для записи!" << endl;
            return;
        }

        // Записываем текст в файл
        outFile << "Tyger Tyger, burning bright\n"
                << "In the forests of the night\n"
                << "What immortal hand or eye\n"
                << "Could frame thy fearful symmetry\n"
                << "In what distant deeps or skies\n"
                << "Burnt the fire of thine eyes\n"
                << "On what wings dare he aspire\n"
                << "What the hand, dare seize the fire\n"
                << "And what shoulder, & what art\n"
                << "Could twist the sinews of thy heart\n"
                << "And when thy heart began to beat\n"
                << "What dread hand? & what dread feet.\n";

        outFile.close();
    }

    // Метод для копирования строк, оканчивающихся на 'k'
    static void copyLinesEndingWithChar(char endingChar) {
        ifstream inFile(SOURCE_TEXT_FILENAME);
        if (!inFile) {
            cerr << "Не удалось открыть исходный текстовый файл для чтения!" << endl;
            return;
        }

        ofstream outFile(DESTINATION_TEXT_FILENAME);
        if (!outFile) {
            cerr << "Не удалось открыть конечный текстовый файл для записи!" << endl;
            inFile.close();
            return;
        }

        string line;
        // Читаем строки из исходного файла
        while (getline(inFile, line)) {
            // Проверяем, оканчивается ли строка на заданный символ
            if (!line.empty() && line.back() == endingChar) {
                outFile << line << endl; // Записываем строку в конечный файл
            }
        }

        inFile.close();
        outFile.close();
    }
};

// Инициализация статических переменных
const string DataProcessor::NUMBERS_FILENAME = "numbers.dat";
const string DataProcessor::BAGGAGE_FILENAME = "baggage.dat";
const string DataProcessor::TEXT_FILENAME = "numbers.txt";
const string DataProcessor::MULTIPLE_TEXT_FILENAME = "multiple_numbers.txt";
const string DataProcessor::SOURCE_TEXT_FILENAME = "source_text.txt"; 
const string DataProcessor::DESTINATION_TEXT_FILENAME = "destination_text.txt"; 

int main() {
    // Заполняем файл случайными числами
    DataProcessor::fillNumbersFile();

    // Задание 1: Подсчёт пар противоположных чисел
    int oppositePairsCount = DataProcessor::countOppositePairs();
    cout << "Количество пар противоположных чисел: " << oppositePairsCount << endl;

    // Задание 2: Ввод размерности квадратной матрицы
    int n;
    cout << "Введите размерность квадратной матрицы (n): ";
    cin >> n;
    DataProcessor::copyToSquareMatrix(n);

    // Задание 3: Заполнение файла с информацией о багаже
    DataProcessor::fillBaggageFile();

    // Задание 3: Разница между массами багажа
    float weightDifference = DataProcessor::calculateWeightDifference();

    cout << "Разница между максимальной и минимальной массой багажа: " << weightDifference << " кг" << endl;

    // Задание 4: Заполнение текстового файла
    DataProcessor::fillTextFile();

    // Задание 4: Проверка на наличие нуля в текстовом файле
    bool result = DataProcessor::containsZeroInFile();
    cout << "Текстовый файл " << (result ? "не содержит нуля." : "содержит ноль.") << endl;

    // Задание 5: Заполнение текстового файла несколькими числами в строке
    DataProcessor::fillMultipleTextFile();

    // Задание 5: Нахождение максимального элемента в файле
    int maxNumber = DataProcessor::findMaxInMultipleTextFile();
    cout << "Максимальный элемент в файле с несколькими числами: " << maxNumber << endl;

    // Задание 6: Копирование строк из одного файла в другой
    // Пример использования функции: копировать строки, оканчивающиеся на 't'
    // Создание исходного текстового файла с заданным текстом
    DataProcessor::createSourceFile();
    
    // Копирование строк, оканчивающихся на 't', в другой файл
    DataProcessor::copyLinesEndingWithChar('t');

    cout << "Строки, оканчивающиеся на 't', переписаны в файл '" << DataProcessor::DESTINATION_TEXT_FILENAME << "'." << endl;
    return 0;
}






