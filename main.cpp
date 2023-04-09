#include <cstdio>
#include <math.h>

void Mainmenu()
{
    printf("Menu Function\n");
    printf("----------------------\n");
    printf("1) Mencari Faktorial\n");
    printf("2) Mencari pangkat \n");
    printf("3) Mencari bilangan prima\n");
    printf("4) Mencari bilangan prima dalam sebuah range\n");
    printf("0) Exit\n");
    printf("----------------------\n");

}

int Mencari_Faktorial()
{
    int a;
    printf("Enter number you want to find factorial of: ");
    scanf("%d", &a);
    int number = 1, i;
    for (i = 2; i <= a; i++)
    {
        number = number * i;
    }
    printf("%d", number);
}

int Mencari_pangkat()
{
    int result;
    int base, exponent;
    printf("Enter a base number: ");
    scanf("%d", &base);
    printf("\n Enter an exponent: ");
    scanf("%d", &exponent);
    result = pow(base, exponent);
    printf("the result is: %d", result);
}

//A prime number is a whole number greater than 1 whose only factors are 1 and itself.
int isPrime(int n) {
    int i;
    if (n <= 1) {
        return 0;
    }
    for (i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void printPrimes(int a, int b) {
    int start, end;
    int i;
    printf("Bilangan prima dari %d sampai %d adalah: ", a, b);
    for (i = a; i <= b; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}


int main() {
    int opsi;
    do {
        int opsi_nyari_lagi = 1;
        Mainmenu();
        printf("Pilih Opsi: ");
        scanf("%d", &opsi);
        switch (opsi)
        {
            case 1:
                while (opsi_nyari_lagi == 1) {
                    Mencari_Faktorial();
                    printf("\nApakah mau mencari Faktorial lagi? \n 1)Ya \n 2)Tidak\n");
                    printf("Pilih: ");
                    scanf("%d", &opsi_nyari_lagi);
                    printf("---------------------------\n");
                }
                break;

            case 2:
                while (opsi_nyari_lagi == 1) {
                    Mencari_pangkat();
                    printf("\nApakah mau mencari pangkat lagi? \n 1)Ya \n 2)Tidak\n");
                    printf("Pilih: ");
                    scanf("%d", &opsi_nyari_lagi);
                    printf("---------------------------\n");
                }
                break;

            case 3:
                while (opsi_nyari_lagi == 1){
                    int number;
                    printf("\nEnter Number: ");
                    scanf("%d", &number);
                    isPrime(number);
                    if(isPrime(number)){
                        printf("%d adalah bilangan prima\n", number);
                    }
                    else {
                        printf("%d bukan bilangan prima ", number);
                    }
                    printf("\nApakah mau mencari bilangan prima lagi? \n 1)Ya \n 2)Tidak\n");
                    printf("Pilih: ");
                    scanf("%d", &opsi_nyari_lagi);
                    printf("---------------------------\n");
                }
                break;

            case 4:
                while (opsi_nyari_lagi == 1){
                    int start, end;
                    printf("Enter start of range: ");
                    scanf("%d", &start);
                    printf("Enter end of range: ");
                    scanf("%d", &end);
                    printPrimes(start, end);
                    printf("\nApakah mau mencari bilangan prima dalam sebuah range lagi? \n 1)Ya \n 2)Tidak\n");
                    printf("Pilih: ");
                    scanf("%d", &opsi_nyari_lagi);
                    printf("---------------------------\n");
                }
                break;
        }


        }while(opsi != 0);
    return 0;
    };
