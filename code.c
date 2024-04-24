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
            //printf("gia tri K = %d\n", k);
            result[i] = (float)(sum / k);
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
                if( ((arr[i] - arr[i-30]) > prominence) && ( (arr[i]-arr[i+30]) > prominence) )
                {
                    index[j] = i;
                    *number_peak = *number_peak + 1;
                    printf("Dinh ơ vị tri = %d\n", i);
                    printf("arr[%d] = %.2f\n", i, arr[i]);
                    printf("arr[%d] = %.2f\n", i-1, arr[i-1]);
                    printf("arr[%d] = %.2f\n", i+1, arr[i+1]);
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
void findTwoLargest(int* arr,int size_arr,int number_peak, int* peak, int* s1, int* s2, int window)
{
    int max1, max2;
    printf("so phan tu cua mang la : %d\n", size_arr);
    // Nếu mảng có ít hơn hai phần tử, không thể tìm được hai giá trị lớn nhất và lớn thứ hai
    if (size_arr < 2) {
        printf("Mang co it hon hai phan tu.\n");
        return;
    }
    // Tìm vị trí của hai giá trị lớn nhất và lớn thứ hai trong mảng
    //int size_peak = (sizeof(peak)/(sizeof(peak[0])));
    for(int i = 0; i < number_peak; ++i)
    {
        printf("peak[%d] = %d\n", i, peak[i]);
        for(int j = peak[i]-window; j < peak[i]+ window; ++j)
        {
            max1 = max2 = arr[j];
            if(arr[j] > max1)
            {
                max2 = max1;
                s2[i] = s1[i];
                max1 = arr[j];
                s1[i] = j;
            }
            else if(arr[j] > max2)
            {
                s2[i] = i;
                max2= arr[j];
            }
        }
    } 
    // In ra vị trí của hai giá trị lớn nhất và lớn thứ hai
    for(int i = 0; i < number_peak; ++i )
    {
        printf("Vi tri cua hai gia tri lon nhat lan luot la: %d va %d\n", s1[i], s2[i]);
    }
}

int main() {
    int size = 1100;
    int ppg_data[size];
    int windowsize = 10;
    FILE *file;
    int number; 
    file = fopen("ppg_sd.txt", "r");// open file to
    // Kiểm tra xem tệp có tồn tại không
    if (file == NULL) {
        printf("Không thể mở tệp.\n");
        return 1; // Trả về 1 để báo lỗi
    }
    // for (int i = 0; i < size; i++) {
    //     fprintf(file, "%d\n", ppg_data[i]);  // Ghi mỗi phần tử trên một dòng
    //     printf("PPG[%d] vừa doc duoc nè = %d\n",i, ppg_data[i]);
    // }
    for(int i = 0; i < size; ++i) 
    {
        fscanf(file, "%d", &ppg_data[i]);
        // printf("Số đọc được từ tệp: %d\n",ppg_data[i]);
        // printf("xin chao nhoc\n");
    }
    // Đóng tệp sau khi hoàn thành
    fclose(file);
    // for (int i = 0; i < size; i++) {
    //     printf("PPG[%d] vừa doc duoc nè = %d\n",i, ppg_data[i]);  // Ghi mỗi phần tử trên một dòng
    // }
    float mean_data[size];// khai bao mang mean_data voi kich thuoc size
    moving_mean(ppg_data, size, windowsize, mean_data);

    /*@brief ghi mean_data vao file mean_data
    *
    */
    FILE *file1 = fopen("mean_data.txt", "w");
    if (file1 == NULL) {
        printf("Không thể mở tệp để ghi.\n");
        return 1;
    }
    int size1 = (sizeof(mean_data)/4);
    // Lưu mảng vào tệp văn bản
    for (int i = 0; i < size; i++) {
        fprintf(file, "%.2f\n", mean_data[i]);  // Ghi mỗi phần tử trên một dòng
    }
    // Đóng tệp
    fclose(file);
    ////////////////////////////////////////////////////////////////////////////////////////
    int arr[size];
    // Mở tệp để ghi
    int pcg_data[size];
    file = fopen("pcg_sd.txt", "r");
    // Kiểm tra xem tệp có tồn tại không
    if (file == NULL) {
        printf("Không thể mở tệp.\n");
        return 1; // Trả về 1 để báo lỗi
    }
    // Đọc và in giá trị từng số nguyên trong tệp
    int i =0;
    // for (int i = 0; i < size; i++) {
    //     fprintf(file, "%d\n", pcg_data[i]);  // Ghi mỗi phần tử trên một dòng
    //     // printf("ppg_data lưu file[%d] = %d\n", i, ppg_data[i]);
    // }
    for(int i = 0; i < size; ++i) 
    {
        fscanf(file, "%d\n", &pcg_data[i]);
        //printf("Số đọc được từ tệp: %d\n",pcg_data[i]);
    }
    // Đóng tệp sau khi hoàn thành
    fclose(file);
    int index_peaks[5];
    int number_peaks = 2;
    int prominence = 10000;
    findpeaks(mean_data, index_peaks, &number_peaks, prominence);
    for(int i = 0; i < number_peaks; ++i)
    {
        printf("dinh thu [%d] la %d\n", i, index_peaks[i]);
    }
    printf("number_peaks = %d\n", number_peaks);
    int s1[20];
    int s2[20];
    findTwoLargest(pcg_data,size, number_peaks, index_peaks,s1,s2,150);
    return 0;
}
