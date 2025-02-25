#include <stdio.h>
#include "miniz.h"

int main()
{
    // Giải nén kernel...
    mz_zip_archive archive;
    const char *zipFilename 
    = "/home/haibeo/haibeo/Linux_Course/B2/kernel_project/kernel.zip";

    memset(&archive, 0, sizeof(archive));
        // Khởi tạo đối tượng mz_zip_archive để đọc tệp ZIP
    if (!mz_zip_reader_init_file(&archive, zipFilename, 0)) {
        // In ra lỗi nếu không mở được tệp
                printf("Lỗi khi mở tệp ZIP: %s\n", zipFilename);
        printf("Mã lỗi: %d\n", mz_zip_reader_init_file(&archive, zipFilename, 0));
        //return -1;
    }
    char username[50];
    char password[50];
    
    size_t file_size = 0;
    char file_username[50], file_password[50]; char access[2];
    // Giải nén file users.txt từ file ZIP
    void *file_data_users = mz_zip_reader_extract_file_to_heap(&archive, "users.txt", &file_size, 0);
    while (1)
    {
        //Yêu cầu nhập tài khoản và mật khẩu
        printf("Nhập tên đăng nhập: ");
        scanf("%s", username);
        printf("Nhập mật khẩu: ");
        scanf("%s", password);
        char *token = strtok(file_data_users, "|");
        if (token) strcpy(file_username, token);

        token = strtok(NULL, "|");
         if (token) strcpy(file_password, token);

        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0)
        {
            snprintf(access, sizeof(access), "1");

            // Update users.txt with the new access rights
            FILE *file = fopen("users.txt", "w");
            if (file == NULL) {
                printf("Error: Unable to open users.txt to update access rights!\n");
                return;
            }
            fprintf(file, "%s|%s|%s\n", username, password, access);
            fclose(file);

            // Update the kernel.zip with the modified users.txt
            system("zip -uj kernel.zip users.txt");
            break;
            }
        printf("Sai tên đăng nhập hoặc mật khẩu!\n");
    }



    const char *file_to_extract = "kernel.c"; // Tên tệp trong ZIP
    void *file_data_src = mz_zip_reader_extract_file_to_heap(&archive, file_to_extract, &file_size, 0);

    if (!file_data_src) {
        mz_zip_reader_end(&archive);
        return -1;
    }
    char* output_filename = "FKernelSrc.c";
    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        free(file_data_src);
        mz_zip_reader_end(&archive);
        return -1;
    }

    fwrite(file_data_src, 1, file_size, output_file);  // Ghi dữ liệu vào tệp
    fclose(output_file);  // Đóng file trước khi biên dịch
    printf("Biên dịch kernel...");
    printf("Chạy kernel...");
    system("gcc -o FKernelSrc FKernelSrc.c");
    system("./FKernelSrc");

    close(output_file);  // Đóng tệp
   // Giải phóng bộ nhớ sau khi sử dụng
    free(file_data_src);

    // Đóng tệp ZIP
    mz_zip_reader_end(&archive);

}