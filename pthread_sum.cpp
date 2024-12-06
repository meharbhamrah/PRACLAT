#include <iostream>
#include <vector>
#include <pthread.h>

struct ThreadData {
    std::vector<int> *array;
    int start;
    int end;
    int sum;
};

void *partial_sum(void *param) {
    ThreadData *data = (ThreadData *)param;
    data->sum = 0;
    for (int i = data->start; i < data->end; i++) {
        data->sum += (*data->array)[i];
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <n> <num1> <num2> ... <numN>" << std::endl;
        return 1;
    }

    int n = std::stoi(argv[1]);
    if (n <= 0 || argc != n + 2) {
        std::cerr << "Invalid input. Provide n followed by n numbers." << std::endl;
        return 1;
    }

    std::vector<int> array;
    for (int i = 0; i < n; i++) {
        array.push_back(std::stoi(argv[i + 2]));
    }

    pthread_t tid1, tid2;
    ThreadData data1 = {&array, 0, n / 2, 0};
    ThreadData data2 = {&array, n / 2, n, 0};

    pthread_create(&tid1, NULL, partial_sum, &data1);
    pthread_create(&tid2, NULL, partial_sum, &data2);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    int total_sum = data1.sum + data2.sum;
    std::cout << "SUM: " << total_sum << std::endl;

    return 0;
}

