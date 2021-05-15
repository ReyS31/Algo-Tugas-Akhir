#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include <limits.h>
#include <stdbool.h>

#define V 10 

//Menentukan jarak
int jarak[V][V] = {
                        {0, 6, 5, 0, 0, 0, 0, 0, 0, 0}, 
                        {6, 0, 7, 0, 0, 16, 0, 0, 0, 0}, 
                        {5, 7, 0, 11, 12, 0, 0, 0, 0, 0}, 
                        {0, 0, 11, 0, 8, 0, 0, 10, 0, 0}, 
                        {0, 0, 12, 8, 0, 0, 13, 9, 0, 0}, 
                        {0, 16, 0, 0, 0, 0, 5, 0, 0, 6}, 
                        {0, 0, 0, 0, 13, 5, 0, 19, 16, 12}, 
                        {0, 0, 0, 10, 9, 0, 19, 0, 8, 0}, 
                        {0, 0, 0, 0, 0, 0, 16, 8, 0, 6},
                        {0, 0, 0, 0, 0, 6, 12, 0, 6, 0} 
                     };
//Definisi kota
char kota[V][20] = {"Kutabumi","Ciledug","Cikupa","Ceger","BaleKota","Serpong","BSD","Karawaci","Bintaro","Alsut"};                     

//struct riwayat
typedef struct history
{
    char nama[40],namabarang[30],detail[30],nohp[15];
    int kota_asal,kota_tujuan,harga,berat,jarak;
    struct history *next,*prev;
}HISTORY;

//struct kontak
struct contact
{
    char user[50], nohp[100];
};
struct contact k_list[100];

int counter_kontak=0;

// Mencari jarak minimum 
int cariJarakMin(int min_jarak[], bool status[]) 
{ 
   // Menetapkan jarak minimum 
   int min = INT_MAX, min_index; 
   
   for (int v = 0; v < V; v++) 
     if (status[v] == 0 && min_jarak[v] <= min) 
         min = min_jarak[v], min_index = v; 
   
   //return jarak minimum
   return min_index; 
} 
   
// Menampilkan jarak
int showJarak(int min_jarak[], int *harga, char kota[V][20], int tujuan, int berat, int *jauh) 
{  
   for (int i = 0; i < V; i++){
    if(i==tujuan-1){
            // Menentukan dan menjumlahkan harga
            *jauh = min_jarak[i];
            if(berat<=10){
                *harga = min_jarak[i] * 7000;
            }else if(berat > 10 && berat <= 20){
                *harga = min_jarak[i] * 10000;
            }else{
                *harga = 0;
            }
        }   
   }
} 

// Algoritma Dijkstra untuk mencari jarak terdekat
void dijkstraAlgorithm(int jarak[V][V], int src, char kota[V][20], int tujuan,int *harga, int berat, int *jauh) 
{ 
     int min_jarak[V];     // Untuk menyimpan jarak minimum

     bool status[V];   // Menyimpan status 0 atau 1, 0 jika false/salah dan 1 jika true/benar

     // Menetapkan semua jarak dengan INT_MAX dan set status menjadi tidak/false 
     for (int i = 0; i < V; i++) 
        min_jarak[i] = INT_MAX, status[i] = 0; 
   
     // Jarak dari asal wajib 0
     min_jarak[src] = 0; 
   
     // Mencari jarak terpendek untuk smua kota
     for (int count = 0; count < V-1; count++) 
     { 
       // Mencari jarak minimum 
       int u = cariJarakMin(min_jarak, status); 
   
       // Jika sudah diproses maka status = 1 
       status[u] = 1; 
   
       // Update min_jarak dari masing-masing kota 
       for (int v = 0; v < V; v++) 
   
         // Update min_jarak[v] hanya jika status = 0/false 
         if (!status[v] && jarak[u][v] && min_jarak[u] != INT_MAX  
                                       && min_jarak[u]+jarak[u][v] < min_jarak[v]) 
            min_jarak[v] = min_jarak[u] + jarak[u][v]; 
     } 
   
     // Menampilkan jarak 
     showJarak(min_jarak, harga, kota, tujuan, berat, jauh); 
} 

//header menu
void headMenu(){
    system("cls");
    printf("|");
    for (int i = 0; i < 32; i++)
    {
        if(i>=13 && i<= 18){
            switch (i)
            {
            case 13:
                printf("G");
                break;
            case 14:
                printf("O");
                break;
            case 15:
                printf("S");
                break;
            case 16:
                printf("E");
                break;
            case 17:
                printf("N");
                break;
            case 18:
                printf("D");
                break;
            }
        }else{
            printf("=");
        }
    }
    printf("|\n");
    printf("| %-30s | \n", "\0");
}

//footer menu
void footerMenu(){
    printf("| %-30s | \n", "\0");
    printf("|");
    for (int i = 0; i < 32; i++)
    {
            printf("=");
    }
    printf("|\n");
}

//menu utama
void menuScreen(){
    headMenu();
    char menu[4][15] = {"Kirim", "Kontak", "History","Keluar"};
    for (int i = 0; i < 4; i++)
    {
        printf("| %d. %-27s | \n",i+1, menu[i]);
    }
    footerMenu();
}

//list kota
void listKota(char kota[V][20]){
    headMenu();
    for (int i = 0; i < V; i++)
    {
        printf("| %2d. %-26s |\n",i+1,kota[i]);
    }
    
    printf("| %-30s | \n", "\0");
    printf("| Input dengan nomor kota.       |\n");
    footerMenu();
}


void kontak();

//Search By Name
void searchByName(char key[20]){
    system("cls");
    int y;
    bool check = false;
    for(y=0; y<counter_kontak; y++){
        /*if(strcmpi(list[y].nama,key)==0){
            check=true;
            break;*/
          if(strstr(k_list[y].user,key) != 0){
            check=true;
            break;
          }
        }

    if(check==true){
        printf("Kontak Ketemu\n");
        headMenu();
        for(y=0; y<counter_kontak; y++){
            if(strstr(k_list[y].user,key) != 0){
                printf("| %-15s%-15s |\n", k_list[y].user, k_list[y].nohp);
          }
        }
        footerMenu();
    }
    else{
        printf("Kontak Tidak Ketemu\n");
    }
    
    system("pause");
    kontak();
}

//Search By Phone
void searchByPhone(char key[20]){
    system("cls");
    int y;
    bool check = false;
    for(y=0; y<counter_kontak; y++){
        if(strstr(k_list[y].nohp,key)==0){
            check=true;
            break;
        }
    }
    if(check==true){
        printf("Kontak Ketemu\n");
        headMenu();
        for(y=0; y<counter_kontak; y++){
            if(strstr(k_list[y].nohp,key) != 0){
                printf("| %-15s%-15s |\n", k_list[y].user, k_list[y].nohp);
          }
        }
        footerMenu();
    }
    else{
        printf("Kontak Tidak Ketemu");
    }
    system("pause");
    kontak();
}

//insert kontak
void insertKontak(char nama[50], char nohp[15],int text){
    char name[30],notelp[30];
    int status=0;
    FILE *fp;
    fp = fopen ("kontak.text","a+");
    while (!feof(fp))
    {
        fscanf(fp,"%[^#]#%[^\n]\n",&name,&notelp);
        if(text!=1){
            if(strcmpi(nama,name)!=0){
                status = 0;
            }else{
                status = 1;
                break;
            }
        }
    }
    if(status==0){
        strcpy(k_list[counter_kontak].user,nama);
        strcpy(k_list[counter_kontak].nohp,nohp);
        counter_kontak++;
        if(text!=1){
            fprintf(fp,"%s#%s \n",nama,nohp);
            kontak();
        }
    }
    fclose (fp);
}

void listKontak(){
    headMenu();
    for (int i = 0; i < counter_kontak; i++)
    {
        printf("| %-2d. %-13s%-13s |\n",i+1,k_list[i].user,k_list[i].nohp);
    }
    footerMenu();
    system("pause");
    kontak();
}

void kontak(){
    system("cls");
    int pilih;
    char nama[30],nohp[15],key[20];
    
    printf("1. Lihat Kontak \n2. Insert Kontak Baru \n3. Cari Kontak \n4. Keluar \nInput: ");
    scanf("%d", &pilih);
    if (pilih==1)
    {
        listKontak();
    }else if(pilih==2){
        system("cls");
        printf("Nama: ");scanf(" %[^\n]", &nama);
        printf("No. Handphone: ");scanf(" %[^\n]", &nohp);
        getchar();
        insertKontak(nama,nohp,0);
    }else if(pilih==3){
        system("cls");
        printf("Masukkan keyword: "); scanf(" %[^\n]",&key);
        printf("1. Search by name\n");
        printf("2. Search by phone number\nInput: ");
        scanf("%d", &pilih);
        switch (pilih)
        {
        case 1:
            searchByName(key);
            break;
        case 2:
            searchByPhone(key);
            break;
        default:
            break;
        }
    }else if(pilih==4){

    }else{
        kontak();
    }
}

void initializeKontak(struct contact **head, struct contact **curr){
    char nama[30],notelp[15];
    FILE * fp;
    fp = fopen("kontak.text","r");
    if (!fp)
    {

    }else{
        while (!feof(fp))
        {
            fscanf(fp,"%[^#]#%[^\n]\n", &nama, &notelp);fflush(stdin);
            if(strlen(nama)>0){
                insertKontak(nama,notelp,1);
            }
        }
        fclose(fp);
    }
}

//insert riwayat
void insertHistory(HISTORY *awal, HISTORY *akhir,char nama[40],char nohp[15],char namabarang[30], int berat, char detail[30], int kota_asal, int kota_tujuan,int jauh,int harga){
    FILE * fp;
    fp = fopen ("riwayat.text","a+");
    HISTORY *titik = (HISTORY*)malloc(sizeof(HISTORY));
    strcpy(titik->nama,nama);
    strcpy(titik->nohp,nohp);
    strcpy(titik->namabarang,namabarang);
    titik->berat = berat;
    strcpy(titik->detail,detail);
    titik->kota_asal = kota_asal;
    titik->kota_tujuan = kota_tujuan;
    titik->jarak = jauh;
    titik->harga = harga;
    titik->next = NULL;
    titik->prev = NULL;
    if(awal==NULL){
        awal = akhir = titik;    
        // printf("Dari %s ke %s \nDengan jarak: %dkm \nTotal harga: Rp.%d \n",kota[awal->kota_asal],kota[awal->kota_tujuan],titik->jarak, titik->harga);
    }else{
        akhir->next = titik;
        titik->prev = akhir;
        akhir = titik;
    }
    fprintf(fp,"%s#%s#%s#%dkg#%s#%s#%s#%dkm#Rp.%d \n",titik->nama,titik->nohp,titik->namabarang,titik->berat,titik->detail,kota[titik->kota_asal],kota[titik->kota_tujuan],titik->jarak,titik->harga);
    fclose (fp);
}

//kirim barang
void kirimBarang(HISTORY *awal, HISTORY *akhir){
    int asal,tujuan,berat,harga,jauh,i;
    bool user_stat = false;
    char detail[30],namabarang[30],username[40];

    system("cls");
    printf("Silahkan Masukkan User\n");
    printf("Username: ");scanf(" %[^\n]",username);
    for (i = 0; i < counter_kontak; i++)
    {
        if(strcmpi(k_list[i].user,username)==0){
            user_stat = true;
            break;
        }
    }
    
    if(user_stat==true){
        listKota(kota);

        printf("Input Kota asal: ");scanf("%d", &asal);
        printf("Input Nama barang: ");scanf(" %[^\n]", &namabarang);
        printf("Input Berat: ");scanf("%d", &berat);
        printf("Input Detail barang: ");scanf(" %[^\n]", &detail);
        printf("Input Kota tujuan: ");scanf("%d", &tujuan);
        asal = asal-1;

        dijkstraAlgorithm(jarak,asal,kota,tujuan,&harga, berat, &jauh);
        
        tujuan = tujuan-1;
        if(harga>0){
            insertHistory(awal,akhir,k_list[i].user,k_list[i].nohp,namabarang,berat,detail,asal,tujuan,jauh,harga);
        }else{
            printf("Invalid \n");
        }
    }else{
        printf("User tidak ditemukan\n");
    }   
    system("pause");
}

//menampikan riwayat
void riwayat(HISTORY *awal){
    char nama[40],nohp[15],namabarang[30],detail[30],kota_asal[40],kota_tujuan[40],harga[40],berat[40],jauh[40];
    char list[V][V] = {"nama","nohp","barang","berat","detail","asal","tujuan","jarak","harga"};
    FILE * fp;
    fp = fopen ("riwayat.text","a+");

    headMenu();
    
    while(fscanf(fp,"%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^\n]\n", &nama,&nohp,&namabarang,&berat,&detail,&kota_asal,&kota_tujuan,&jauh,&harga)!=EOF){

        printf("| %-6s: %-22s |\n| %-6s: %-22s |\n| %-6s: %-22s |\n| %-6s: %-22s |\n| %-6s: %-22s |\n| %-6s: %-22s |\n| %-6s: %-22s |\n| %-6s: %-22s |\n| %-6s: %-22s |\n",list[0],nama,list[1],nohp,list[2],namabarang,list[3],berat,list[4],detail,list[5],kota_asal,list[6],kota_tujuan,list[7],jauh,list[8],harga);
        footerMenu();
    }
    fclose(fp);
    system("pause");
}   

int main()
{
    int jmlhdata = 0,pilihan;
    HISTORY *awal,*akhir;
    struct contact *head, *curr;
    awal = akhir = NULL;
    head = curr = NULL;

    initializeKontak(&head,&curr);

    menu:menuScreen();
    printf("Input: ");
    scanf("%d", &pilihan);
    switch (pilihan)
    {
    case 1:
        kirimBarang(awal,akhir);
        goto menu;
        break;
    case 2:
        kontak();
        goto menu;
        break;
    case 3:
        riwayat(awal);
        goto menu;
        break;
    case 4:
        exit(0);
        break;    
    default:
        goto menu;
        break;
    }
    return 0;
}