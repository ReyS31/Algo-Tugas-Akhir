/* localtime example */
#include <stdio.h>
#include <time.h>
#include<malloc.h>

typedef struct data
{
    int hari,bulan,tanggal,jam, tahun;
}data;


void waktu(data *datas){
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  datas->jam = timeinfo->tm_hour;
  datas->hari = timeinfo->tm_wday;
  datas->tanggal = timeinfo->tm_mday;
  datas->bulan = timeinfo->tm_mon;
  datas->tahun = timeinfo->tm_year;
  printf ( "Current local time and date: %s", asctime (timeinfo));
}


int main ()
{
system("cls");
 data *pa;
 waktu(pa);

  return 0;
}       