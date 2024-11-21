#include <iostream>
#include <fstream>
#include <cstdlib> // Для rand() и srand()
#include <ctime>   // Для time
#include <limits>  // Для std::numeric_limits
#include <string>  // Для std::string
#include <algorithm> // Для std::find_if и std::isspace

class FileProcessor {
public:
    // Метод для заполнения файла случайными числами (по одному числу на строку)
    static void FillFileWithRandomNumbersColumn(const std::string& filePath, int count) {
        std::ofstream outFile(filePath);
        if (outFile.is_open()) {
            for (int i = 0; i < count; ++i) {
                int randomNumber = rand() % 101; // Генерируем случайное число от 0 до 100
                outFile << randomNumber << std::endl; // Записываем число в новый столбец
            }
            outFile.close();
        } else {
            std::cerr << "Не удалось открыть файл для записи" << std::endl;
        }
    }

    // Метод для заполнения файла случайными числами (несколько чисел в строке)
    static void FillFileWithRandomNumbersLine(const std::string& filePath, int count, int numbersPerLine) {
        std::ofstream outFile(filePath);
        if (outFile.is_open()) {
            for (int i = 0; i < count; ++i) {
                int randomNumber = rand() % 101; // Генерируем случайное число от 0 до 100
                outFile << randomNumber;
                if ((i + 1) % numbersPerLine == 0) {
                    outFile << std::endl; // Переводим на новую строку
                } else {
                    outFile << " "; // Разделяем числа пробелом
                }
            }
            outFile.close();
        } else {
            std::cerr << "Не удалось открыть файл для записи" << std::endl;
        }
    }

    // Метод для проверки, содержит ли файл ноль
    static bool ContainsZero(const std::string& filePath) {
        std::ifstream inFile(filePath);
        if (inFile.is_open()) {
            int number;
            while (inFile >> number) {
                if (number == 0) { // Проверяем на наличие нуля
                    inFile.close();
                    return true;
                }
            }
            inFile.close();
        } else {
            std::cerr << "Не удалось открыть файл для чтения" << std::endl;
        }
        return false;
    }

    // Метод для нахождения максимального элемента в файле
    static int FindMaxElement(const std::string& filePath) {
        std::ifstream inFile(filePath);
        if (!inFile.is_open()) {
            std::cerr << "Не удалось открыть файл для чтения" << std::endl;
            return std::numeric_limits<int>::min(); // Возвращаем минимально возможное значение в случае ошибки открытия файла
        }

        int number;
        int maxElement = std::numeric_limits<int>::min(); // Используем минимально возможное значение для int
        while (inFile >> number) {
            if (number > maxElement) {
                maxElement = number; // Обновляем максимальный элемент
            }
        }

        inFile.close();
        return maxElement;
    }

    // Метод для переписывания строк, оканчивающихся на заданный символ, в другой файл
    static void CopyLinesEndingWithChar(const std::string& inputFilePath, const std::string& outputFilePath, char endingChar) {
        std::ifstream inFile(inputFilePath);
        std::ofstream outFile(outputFilePath);

        if (!inFile.is_open() || !outFile.is_open()) {
            std::cerr << "Не удалось открыть файл для чтения или записи" << std::endl;
            return;
        }

        std::string line;
        while (std::getline(inFile, line)) {
            // Удаляем пробелы в конце строки и проверяем
            line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(), line.end()); // Удалить пробелы в конце строки

            if (!line.empty() && line.back() == endingChar) { // Проверяем, заканчивается ли строка на заданный символ
                outFile << line << std::endl; // Записываем строку в другой файл
            }
        }

        inFile.close();
        outFile.close();
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    // Для первого задания
    std::string file1Path = "file1_numbers.txt"; // Файл с числами в столбец
    int numbersToGenerate1 = 100; // Количество чисел для первого задания

    // Заполнение файла случайными данными для первого задания
    FileProcessor::FillFileWithRandomNumbersColumn(file1Path, numbersToGenerate1);

    // Проверяем, содержит ли файл нуль
    bool hasZero1 = FileProcessor::ContainsZero(file1Path);
    std::cout << "Файл " << file1Path << " содержит ноль: " << (hasZero1 ? "Да" : "Нет") << std::endl;

    // Находим максимальный элемент
    int maxElement1 = FileProcessor::FindMaxElement(file1Path);
    std::cout << "Максимальный элемент в файле " << file1Path << ": " << maxElement1 << std::endl;

    // Для второго задания
    std::string file2Path = "file2_numbers.txt"; // Файл с числами в строку
    int numbersToGenerate2 = 100; // Общее количество чисел для второго задания
    int numbersPerLine = 10; // Количество чисел в одной строке

    // Заполнение файла случайными данными для второго задания
    FileProcessor::FillFileWithRandomNumbersLine(file2Path, numbersToGenerate2, numbersPerLine);

    // Находим максимальный элемент во втором файле
    int maxElement2 = FileProcessor::FindMaxElement(file2Path);
    std::cout << "Максимальный элемент в файле " << file2Path << ": " << maxElement2 << std::endl;

    // Для третьего задания
    std::string textInputFilePath = "input_text.txt"; // Файл с текстом
    std::string textOutputFilePath = "output_text.txt"; // Файл для записи строк
    char endingChar = 'e'; // Задайте символ, на который должны оканчиваться строки

    // Запись тестового текста в файл (например, это исходный текст)
    std::ofstream testTextFile(textInputFilePath);
    if (testTextFile.is_open()) {
        testTextFile << "Tyger Tyger, burning bright" << std::endl;
        testTextFile << "In the forests of the night" << std::endl;
        testTextFile << "What immortal hand or eye" << std::endl;
        testTextFile << "Could frame thy fearful symmetry" << std::endl;
        testTextFile << "In what distant deeps or skies" << std::endl;
        testTextFile << "Burnt the fire of thine eyes" << std::endl;
        testTextFile << "On what wings dare he aspire" << std::endl;
        testTextFile << "What the hand, dare seize the fire" << std::endl;
        testTextFile << "And what shoulder, & what art" << std::endl;
        testTextFile << "Could twist the sinews of thy heart" << std::endl;
        testTextFile << "And when thy heart began to beat" << std::endl;
        testTextFile << "What dread hand? & what dread feet" << std::endl;
        testTextFile.close();
    }

    // Копирование строк, оканчивающихся на заданный символ
    FileProcessor::CopyLinesEndingWithChar(textInputFilePath, textOutputFilePath, endingChar);
    std::cout << "Строки, оканчивающиеся на '" << endingChar << "', были записаны в файл " << textOutputFilePath << std::endl;

    return 0;
}





