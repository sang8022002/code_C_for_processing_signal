#include <stdio.h>

void moving_mean(const int *arr, int arr_len, int k, int *result) {
    for (int i = 0; i <= arr_len - 1; ++i) 
    {
        // int window = k;
        if(i < arr_len -k + 1)
        {
            float sum = 0;
            for (int j = i; j < i + k; ++j) {
                sum += arr[j];
            }
            //printf("gia tri K = %d\n", k);
            result[i] = (int)(sum / k);
            //printf("mean data trong ham moving_mean[%d] = %.2f\n",i, result[i]);
        }
        else 
        {
            float sum = 0;
            for(int j = i; j <= arr_len -1; ++j )
            {
                sum += arr[j];
                //printf("arr[%d] = %d\n", j, arr[j]);
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
void findpeaks(int *arr,int size, int *index, int *number_peak, int prominence )
{
    *number_peak = 0;
    int j = 0;
    for(int i = 1; i < size ; ++i )
    {
        if( i > 30-1 && i < size-30-1)
        {
            if(arr[i] > arr[i-1] && arr[i] > arr[i+1])
            {
                
                if( ((arr[i] - arr[i-30]) > prominence) && ( (arr[i]-arr[i+30]) > prominence) )
                {
                    index[j] = i;
                    *number_peak = *number_peak + 1;
                    printf("Dinh ơ vị tri = %d\n", index[j]);
                    printf("arr[%d] = %d\n", i, arr[i]);
                    printf("arr[%d] = %d\n", i-1, arr[i-1]);
                    printf("arr[%d] = %d\n", i+1, arr[i+1]);
                    j++;
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
        else if(i > size-30)
        {
            if(arr[i] > arr[i-1] && arr[i] > arr[i+1])
            {
                printf("có chạy vao doạn cuối\n");
                if( (arr[i] - arr[i - 30]) > prominence && ( (arr[i]-arr[size- 1]> prominence ) ))
                {
                    index[j] = i;
                    *number_peak = *number_peak + 1;
                    printf("Dinh ơ vị tri = %d\n", i);
                }
            }
        }
    }
}
void findTwoLargest(int* arr,int size_arr,int* peak_pcg, int number_peak_pcg, int number_peak_ppg, int* peak_ppg, int* s1, int* s2, int window)
{
    int max1, max2;
    printf("so phan tu cua mang la : %d\n", size_arr);
    for(int i = 0; i < number_peak_ppg; ++i)
    {
        printf("Tai dinh ppg thu %d\n", i+1);
        max1 = 0;
        max2 = 0;
        for(int j = 0; j < number_peak_pcg; ++j)
        {
            if( (peak_pcg[j] > peak_ppg[i]- window) && (peak_pcg[j] < peak_ppg[i] + window))
            {
                printf(" kiem tra cua so tai dinh ppg[%d] cua so chay den co pcg[%d] = %d\n", peak_ppg[i], peak_pcg[j], arr[peak_pcg[j]]);
                if(arr[peak_pcg[j]] > max1)
                {
                    max2 = max1;
                    max1 = arr[peak_pcg[j]];
                    s2[i] = s1[i];
                    s1[i] = peak_pcg[j];
                    //printf("co chayj vaof ddaay khoong\n");
                }
                else if(arr[peak_pcg[j]] > max2)
                {
                    s2[i] = peak_pcg[j];
                    max2= arr[peak_pcg[j]];
                }   
            }
        }
    } 
    // In ra vị trí của hai giá trị lớn nhất và lớn thứ hai
    for(int i = 0; i < number_peak_ppg; ++i )
    {
        printf("Vi tri cua hai gia tri lon nhat gan PPG thu %d lan luot la: %d va %d\n", i, s1[i], s2[i]);
    }
}

int main() {
    int size = 1100;
    int windowsize = 10;

    int ppg_data[size];
    int pcg_data[size];

    // int arr[size];
    int index_peaks_ppg[5];
    int index_peaks_pcg[200];

    int number_peaks_ppg = 2;
    int number_peaks_pcg = 2;

    int prominence = 10000;
 
    int s1[20];
    int s2[20];

    int mean_data[size];// khai bao mang mean_data voi kich thuoc size
    //int number; 

    /*To open file ppg to load data  to ppg_data[i]*/
    FILE *file;
    file = fopen("ppg_sd.txt", "r");// open file to
    // Kiểm tra xem tệp có tồn tại không
    if (file == NULL) {
        printf("Không thể mở tệp.\n");
        return 1; // Trả về 1 để báo lỗi
    }
    for(int i = 0; i < size; ++i) 
    {
        fscanf(file, "%d", &ppg_data[i]);
    }
    fclose(file);    // Đóng tệp sau khi hoàn thành

    /*To average the ppg data with sliding window*/
    moving_mean(ppg_data, size, windowsize, mean_data);

    FILE *file1 = fopen("mean_data.txt", "w");
    if (file1 == NULL) {
        printf("Không thể mở tệp để ghi.\n");
        return 1;
    }
    int size1 = (sizeof(mean_data)/4);
    // Lưu mảng vào tệp văn bản
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", mean_data[i]);  // Ghi mỗi phần tử trên một dòng
    }
    fclose(file);    // Đóng tệp
    
    /*Open file pcg to load data into pcg_data[i]*/
    file = fopen("pcg_sd.txt", "r");

    if (file == NULL) {                         // Kiểm tra xem tệp có tồn tại không
        printf("Không thể mở tệp.\n");
        return 1; // Trả về 1 để báo lỗi
    }
    // Đọc và in giá trị từng số nguyên trong tệp
    int i =0;
    for(int i = 0; i < size; ++i) 
    {
        fscanf(file, "%d\n", &pcg_data[i]);
        //printf("Số đọc được từ tệp: %d\n",pcg_data[i]);
    }
    fclose(file);// Đóng tệp sau khi hoàn thành

    /*find peaks with mean_data(data after push ppg_data through mean_data function)*/
    findpeaks(mean_data, size, index_peaks_ppg, &number_peaks_ppg, prominence);
    for(int i = 0; i < number_peaks_ppg; ++i)
    {
        printf("dinh thu [%d] la %d\n", i, index_peaks_ppg[i]);
    }
    
    /*find peaks into pcg_data*/
    findpeaks(pcg_data, size, index_peaks_pcg, &number_peaks_pcg, 0);

    printf("number pcg peaks = %d\n", number_peaks_pcg); //
    printf("number ppg peaks = %d\n", number_peaks_ppg);
    
    findTwoLargest(pcg_data, size, index_peaks_pcg, number_peaks_pcg, number_peaks_ppg, index_peaks_ppg, s1, s2, 150);
    return 0;
}
