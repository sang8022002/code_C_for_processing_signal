#include <stdio.h>

void moving_mean(const int *arr, int arr_len, int k, float *result) {
    for (int i = 0; i <= arr_len - 1; ++i) 
    {
        // int window = k;
        if(i < arr_len -k + 1)
        {
            float sum = 0;
            for (int j = i; j < i + k; ++j) {
                sum += arr[j];
            }
            // printf("gia tri K = %d\n", k);
            result[i] = (float)(sum / k);
            // printf("mean data trong ham moving_mean[%d] = %.2f\n",i, result[i]);
        }
        else 
        {
            float sum = 0;
            for(int j = i; j <= arr_len -1; ++j )
            {
                sum += arr[j];
                printf("arr[%d] = %.2f", j, arr[j]);
                
            }
            result[i] = (float)(sum)/(arr_len-i); 
            // printf("sum data trong ham k cua so ham sum[%d] = %.2f\n",i, sum);
            // printf("mean data trong ham k cua so ham mean[%d] = %.2f\n",i, result[i]);
            // printf("arr_len = [%d] va i =[%d] \n",arr_len, i);
        }
    }
}

void moving_median(const float *arr, int arr_len, int k, float *result) {
    for (int i = 0; i <= arr_len - k; ++i) {
        float temp[k];
        for (int j = 0; j < k; ++j) {
            temp[j] = arr[i + j];
        }
        // Sắp xếp mảng tạm thời
        for (int m = 0; m < k - 1; ++m) {
            for (int n = m + 1; n < k; ++n) {
                if (temp[m] > temp[n]) {
                    float temp_val = temp[m];
                    temp[m] = temp[n];
                    temp[n] = temp_val;
                }
            }
        }
        // Tìm giá trị trung vị
        if (k % 2 == 0) {
            result[i] = (temp[k / 2 - 1] + temp[k / 2]) / 2.0;
        } else {
            result[i] = temp[k / 2];
        }
    }
}
/*Tim cac dinh trong mang data*/
void findpeaks(float *arr, int *index, int *number_peak, int prominence )
{
    *number_peak = 0;
    int j = 0;
    for(int i = 1; i < 1000 ; ++i )
    {
        if( i > 30-1 && i < 1000-30-1)
        {
            if(arr[i] > arr[i-1] && arr[i] > arr[i+1])
            {
                if( (arr[i] - arr[i-30]) > prominence && ( (arr[i]-arr[i+30]> prominence ) ))
                {
                    index[j] = i;
                    *number_peak = *number_peak + 1;
                    printf("Dinh ơ vị tri = %d\n", i);
                }
            }
        }
        else if(i < 30)
        {
            if(arr[i] > arr[i-1] && arr[i] > arr[i+1])
            {
                if( (arr[i] - arr[0]) > prominence && ( (arr[i]-arr[i+30]> prominence) ))
                {
                    index[j] = i;
                    *number_peak = *number_peak + 1;
                    printf("Dinh ơ vị tri = %d\n", i);
                }
            }
        }
        else if(i > 1000-30)
        {
            if(arr[i] > arr[i-1] && arr[i] > arr[i+1])
            {
                if( (arr[i] - arr[i - 30]) > prominence && ( (arr[i]-arr[1000]> prominence ) ))
                {
                    index[j] = i;
                    *number_peak = *number_peak + 1;
                    printf("Dinh ơ vị tri = %d\n", i);
                }
            }
        }
    }
}
int main() {
    int ppg_data[1200];
    int size = (sizeof(ppg_data)/4);
    FILE *file;
    int number;
    
    // Mở tệp để đọc
    file = fopen("ppg_sd.txt", "r");
    
    // Kiểm tra xem tệp có tồn tại không
    if (file == NULL) {
        printf("Không thể mở tệp.\n");
        return 1; // Trả về 1 để báo lỗi
    }

    // Đọc và in giá trị từng số nguyên trong tệp
    int i =0;
    while (fscanf(file, "%d\n", &ppg_data[i]) != EOF) {
        i++;
    }
    for (int i = 0; i < 1200; i++) {
        fprintf(file, "%d\n", ppg_data[i]);  // Ghi mỗi phần tử trên một dòng
        // printf("ppg_data lưu file[%d] = %d\n", i, ppg_data[i]);
    }

    // Đóng tệp sau khi hoàn thành
    fclose(file);
    printf("size of ppg1 %d\n", sizeof(ppg_data));
    // printf("size int1 = %d\n", sizeof(int));
    int ppg_len = 1100;
    int windowsize = 10;
    float mean_data[1100] = {1};
    // mean_data[ppg_len - windowsize + 2] = {0.0};
    float median_data[ppg_len - windowsize + 2];
    // for (int i = 0; i < (sizeof(mean_data)/4); i++) {
    //     // fprintf(file, "%d\n", mean_data[i]);  // Ghi mỗi phần tử trên một dòng
    //     printf("mean_data 1[%d] = %.2f\n", i, mean_data[i]);
    // }
    printf("sizeof(mean_data) lan 1 = %d\n", sizeof(mean_data));
    // Tính toán moving mean
    moving_mean(ppg_data, ppg_len, windowsize, mean_data);
    int arr[sizeof(mean_data)];
    // Giả sử mảng đã được điều chỉnh ở đây
    printf("sizeof(mean_data) = %d\n", sizeof(mean_data));
    // Mở tệp để ghi
    FILE *file1 = fopen("mean_data.txt", "w");
    if (file1 == NULL) {
        printf("Không thể mở tệp để ghi.\n");
        return 1;
    }
    int size1 = (sizeof(mean_data)/4);
    // Lưu mảng vào tệp văn bản
    for (int i = 0; i < size1; i++) {
        fprintf(file, "%.2f\n", mean_data[i]);  // Ghi mỗi phần tử trên một dòng
    }
    // Đóng tệp
    fclose(file);
    int index_peaks[1000];
    int number_peaks = 1;
    int prominence = 10000;
    findpeaks(mean_data, index_peaks, &number_peaks, prominence);
    for(int i = 0; i < number_peaks; ++i)
    {
        printf("dinh thu [%d] la %d", i, index_peaks[i]);
    }
    printf("number_peaks = %d", number_peaks);
    return 0;
}
